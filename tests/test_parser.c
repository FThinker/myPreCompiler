#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../src/data_structures.h"
#include "../src/validator.h"
#include "../src/parser.h"

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"


// ----------------------------------------------------------------------------------------- //


void test_parse_empty_list() {
    printf("Running test_parse_empty_list... ");

    VariableNode* var_list = NULL;
    TypedefNode* custom_types = NULL;

    // Passing NULL must terminate safely without blowing stuff up
    parse_file(NULL, &var_list, &custom_types);

    assert(var_list == NULL);
    assert(custom_types == NULL);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}

// ----------------------------------------------------------------------------------------- //

void test_parse_valid_code() {
    printf("Running test_parse_valid_code... ");

    LineNode* clean_lines = NULL;
    VariableNode* var_list = NULL;
    TypedefNode* custom_types = NULL;

    // Simulating clean and trimmed lines
    add_line(&clean_lines, create_line("typedef int my_int;", 1));
    add_line(&clean_lines, create_line("my_int global_var = 100;", 2));
    add_line(&clean_lines, create_line("int main() {", 3));
    add_line(&clean_lines, create_line("int a = 1, b = 2, *ptr;", 4)); // Multiple local declaration
    add_line(&clean_lines, create_line("double standard_var;", 5));
    add_line(&clean_lines, create_line("global_var++;", 6));           // Actual operation: switch to state 2
    add_line(&clean_lines, create_line("a = b + 1;", 7));              // Two variables used at the same time
    add_line(&clean_lines, create_line("return 0;", 8));
    add_line(&clean_lines, create_line("}", 9));

    parse_file(clean_lines, &var_list, &custom_types);

    // VERIFYING RESULTING TYPEDEFS
    assert(custom_types != NULL);
    assert(strcmp(custom_types->name, "my_int") == 0);
    assert(custom_types->next == NULL);

    // VERIFYING EXTRACTED VARIABLES
    // expected order (reading order):
    // 1. global_var | 2. a | 3. b | 4. ptr | 5. standard_var

    VariableNode* curr_var = var_list;

    // 1. global_var (declared on line 2, used on line 6)
    assert(curr_var != NULL);
    assert(strcmp(curr_var->name, "global_var") == 0);
    assert(strcmp(curr_var->type, "my_int") == 0);
    assert(curr_var->line_declared == 2);
    assert(curr_var->is_used == true);
    assert(curr_var->valid_name == true);
    assert(curr_var->valid_type == true); // recognize 'my_int' as valid custom type
    curr_var = curr_var->next;

    // 2. a (declared on line 4, used on line 7)
    assert(curr_var != NULL);
    assert(strcmp(curr_var->name, "a") == 0);
    assert(strcmp(curr_var->type, "int") == 0);
    assert(curr_var->line_declared == 4);
    assert(curr_var->is_used == true);
    assert(curr_var->valid_name == true);
    assert(curr_var->valid_type == true);
    curr_var = curr_var->next;

    // 3. b (declared on line 4, used on line 7)
    assert(curr_var != NULL);
    assert(strcmp(curr_var->name, "b") == 0);
    assert(strcmp(curr_var->type, "int") == 0);
    assert(curr_var->line_declared == 4);
    assert(curr_var->is_used == true);
    assert(curr_var->valid_name == true);
    assert(curr_var->valid_type == true);
    curr_var = curr_var->next;

    // 4. ptr (declared on line 4, UNUSED)
    assert(curr_var != NULL);
    assert(strcmp(curr_var->name, "ptr") == 0); // pointer has been succesfully removed
    assert(strcmp(curr_var->type, "int") == 0);
    assert(curr_var->line_declared == 4);
    assert(curr_var->is_used == false);         // should be unused
    assert(curr_var->valid_name == true);
    assert(curr_var->valid_type == true);
    curr_var = curr_var->next;

    // 5. standard_var (declared on line 5, UNUSED)
    assert(curr_var != NULL);
    assert(strcmp(curr_var->name, "standard_var") == 0);
    assert(strcmp(curr_var->type, "double") == 0);
    assert(curr_var->line_declared == 5);
    assert(curr_var->is_used == false);
    assert(curr_var->valid_name == true);
    assert(curr_var->valid_type == true);
    
    // verify that list actually ends where expected
    assert(curr_var->next == NULL);

    // release all dirty memory
    free_lines(clean_lines);
    free_variables(var_list);
    free_typedefs(custom_types);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}

// ----------------------------------------------------------------------------------------- //

int main() {
    printf(COLOR_GREEN "=== RUNNING PARSER TEST ===" COLOR_RESET "\n");

    test_parse_empty_list();
    test_parse_valid_code();

    printf(COLOR_GREEN "=== ALL TESTS PASSED SUCCESSFULLY ===" COLOR_RESET "\n");
    return 0;
}