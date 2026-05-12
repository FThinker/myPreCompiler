#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data_structures.h"
#include "validator.h"
#include "parser.h"


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Checks if a word is a dedicated C control flow keyword.
 */
static bool is_control_keyword(const char* word) {
    const char* controls[] = {"if", "for", "while", "return", "switch", "do", "break", "continue", "goto"};
    int size = sizeof(controls) / sizeof(controls[0]);
    for (int i = 0; i < size; i++) {
        if (strcmp(word, controls[i]) == 0) {
            return true;
        }
    }
    return false;
}


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Consistently determines if a line is intended to be a declaration (a declaration counts even if malformed/invalid).
 */
static bool is_declaration_statement(const char* line, TypedefNode* custom_types) {
    char temp_line[1024]; // input buffer, default size
    strncpy(temp_line, line, sizeof(temp_line) - 1);
    temp_line[sizeof(temp_line) - 1] = '\0';

    // extract the very first word token
    char* first_word = strtok(temp_line, " \t=,;()[{");
    if (first_word == NULL) return false;

    // case 1: declaration starts with a valid known type
    if (is_valid_type(first_word, custom_types)) {
        return true;
    }

    // case 2: declaration has compound standard types ("unsigned int")
    if (strcmp(first_word, "unsigned") == 0 
        || strcmp(first_word, "signed") == 0 
        || strcmp(first_word, "long") == 0 
        || strcmp(first_word, "short") == 0) {
        return true; 
    }

    // case 3: if line contains a control flow keyword, it's definitely an operational instruction, not a declaration
    if (is_control_keyword(first_word)) {
        return false;
    }

    // case 4: there is a second token before assignment/operators.
    // syntax like "Word1 Word2" might indicate a malformed declaration attempt
    char* second_word = strtok(NULL, " \t=,;()[{");
    if (second_word != NULL) {
        // If we found a second word token immediately following an unknown first word, treat as invalid declaration
        return true;
    }

    // if all checks fail, it's quite possibly gibberish
    return false;
}


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Helper function to safely extract a single variable name from a fragment, validate its attributes, and store it in the main list.
 */
static void process_variable_fragment(const char* fragment, const char* base_type, int line_num, VariableNode** var_list, TypedefNode* custom_types) {
    // skip initial spaces and pointers
    const char* ptr = fragment;
    while (*ptr != '\0' && (isspace((unsigned char)*ptr) || *ptr == '*')) {
        ptr++;
    }

    // get the actual identifier name
    char var_name[256] = {0};
    int i = 0;
    while (ptr[i] != '\0' && (isalnum((unsigned char)ptr[i]) || ptr[i] == '_') && i < 255) {
        var_name[i] = ptr[i];
        i++;
    }

    if (strlen(var_name) > 0) {
        VariableNode* new_var = create_variable(var_name, base_type, line_num);
        if (new_var != NULL) {
            // validate fields using the validator module
            new_var->valid_name = is_valid_identifier(var_name);
            new_var->valid_type = is_valid_type(base_type, custom_types);
            add_variable(var_list, new_var);
        }
    }
}


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Parses a full declaration line, extracts the base type, and splits multiple declarations (if there are any).
 */
static void parse_declaration_line(const char* line, int line_num, VariableNode** var_list, TypedefNode** custom_types) {
    char buffer[4096];
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // case 1: global typedef declaration
    if (strncmp(buffer, "typedef ", 8) == 0) {
        // the last identifier before ";" is the new type name
        char* semi = strchr(buffer, ';');
        if (semi != NULL) *semi = '\0';
        
        // find the last space-separated token
        char* last_token = strrchr(buffer, ' ');
        if (last_token != NULL) {
            char* new_type_name = last_token + 1;
            // remove leading "*", if any
            while (*new_type_name == '*') new_type_name++;
            if (strlen(new_type_name) > 0) {
                TypedefNode* new_type = create_typedef(new_type_name);
                if (new_type != NULL) add_typedef(custom_types, new_type);
            }
        }
        return;
    }

    // case 2: standard variable declaration
    char base_type[128] = {0};
    char* first_space = strchr(buffer, ' ');
    if (first_space == NULL) return;

    // handle compound types ("unsigned int","long double")
    if (strncmp(buffer, "unsigned ", 9) == 0 
        || strncmp(buffer, "signed ", 7) == 0 
        || strncmp(buffer, "long double", 11) == 0 
        || strncmp(buffer, "long long", 9) == 0) {
        char* second_space = strchr(first_space + 1, ' ');
        if (second_space != NULL) {
            strncpy(base_type, buffer, second_space - buffer);
            first_space = second_space; // move scan pointer past the compound type
        } else {
            strcpy(base_type, buffer);
        }
    } else {
        strncpy(base_type, buffer, first_space - buffer);
    }

    // isolate the rest of the line containing declarations separated by comma
    char* remainder = first_space + 1;
    char* semicolon = strchr(remainder, ';');
    if (semicolon != NULL) *semicolon = '\0';

    // tokenize multiple declarations iteratively ("*ptr", "a = 1", "b")
    // strtok_r is standard for thread-safe sequential scanning
    char* saveptr;
    char* token = strtok_r(remainder, ",", &saveptr);
    while (token != NULL) {
        // if there's an assignment '=', strip everything to the right (ignore it)
        char* equals = strchr(token, '=');
        if (equals != NULL) *equals = '\0';

        process_variable_fragment(token, base_type, line_num, var_list, *custom_types);
        token = strtok_r(NULL, ",", &saveptr); // proceed to the next token, if there's any
    }
}


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Checks if stored variables are used in operation lines using word boundaries.
 */
static void check_variable_usage(const char* line, VariableNode* var_list) {
    VariableNode* curr = var_list;
    while (curr != NULL) {
        if (!curr->is_used && curr->valid_name) {
            size_t var_len = strlen(curr->name);
            const char* ptr = line;

            // search for occurrences iteratively
            while ((ptr = strstr(ptr, curr->name)) != NULL) {
                // determine left and right boundaries
                bool left_boundary_ok = (ptr == line) || (!isalnum((unsigned char)*(ptr - 1)) && *(ptr - 1) != '_');
                bool right_boundary_ok = (!isalnum((unsigned char)*(ptr + var_len)) && *(ptr + var_len) != '_');

                if (left_boundary_ok && right_boundary_ok) {
                    curr->is_used = true;
                    break; // found a valid usage, no need to keep scanning this line for this variable (use count isn't relevant)
                }
                ptr += var_len;
            }
        }
        curr = curr->next;
    }
}


// ----------------------------------------------------------------------------------------- //


void parse_file(LineNode* clean_lines_head, VariableNode** var_list_head, TypedefNode** custom_types_head) {
    if (clean_lines_head == NULL) return;

    int state = 0;
    LineNode* curr_line = clean_lines_head;

    while (curr_line != NULL) {
        const char* content = curr_line->line_content;
        int line_num = curr_line->line_number;

        // STATE 0: Global Declarations
        if (state == 0) {
            // check if line is the main() function header
            if (strstr(content, "main") != NULL && strchr(content, '(') != NULL) {
                state = 1; // if it is, go to state 1
            } 
            else if (is_declaration_statement(content, *custom_types_head)) {
                parse_declaration_line(content, line_num, var_list_head, custom_types_head);
            }
        }
        // STATE 1: Local Declarations inside main()
        else if (state == 1) {
            // Skip the signature line or sole opening brace if they appear as distinct nodes
            if (strcmp(content, "{") == 0 || strstr(content, "main") != NULL) {
                curr_line = curr_line->next;
                continue;
            }

            // By assumption, local variables are contiguous at the start of main().
            // If the line is a declaration statement, parse it. Otherwise, transition to State 2 immediately.
            if (is_declaration_statement(content, *custom_types_head)) {
                parse_declaration_line(content, line_num, var_list_head, custom_types_head);
            } else {
                state = 2; // Operational body started!
                // Do not skip node, fall through to evaluate current operational instruction for usage
            }
        }

        // --- STATE 2: Operational Body Instructions ---
        if (state == 2) {
            // Check if variables declared so far are used in this instruction line
            check_variable_usage(content, *var_list_head);
        }

        curr_line = curr_line->next;
    }
}