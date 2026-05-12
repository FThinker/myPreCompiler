#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

/**
 * @brief Private helper function to trim tabs and spaces at the start and end of a line.
 *
 * All changes to the string are made in-place, so no dynamic allocation is required.
 * 
 */
static void trim_inplace(char* str) {
    if (str == NULL) return;

    // skip all initial junk at the start
    char* start = str;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }

    
    if (*start == '\0') {
        str[0] = '\0';
        return;
    }

    // move the useful part of the line at the buffer's start
    // (memmove is safer than strcpy here because memory spaces overlap)
    size_t len = strlen(start);
    memmove(str, start, len + 1);

    // trim spaces and tabs at the end
    char* end = str + len - 1;
    while (end > str && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}


// ----------------------------------------------------------------------------------------- //


LineNode* clean_file(LineNode* head) {
    if(head == NULL){
        fprintf(stderr, "Error: No lines to clean. The file appears to be empty.\n");
        return;
    }

    LineNode* prev = NULL;
    LineNode* current = head;
    LineNode* next = NULL;
    int multi_comment = 0;

    while(current != NULL){
        next = current->next;
        int should_eliminate = 0;

        // temporarily skipping spaces and tabs
        char* start = current->line_content;
        while (*start != '\0' && isspace((unsigned char)*start)) {
            start++;
        }

        if (*start == '\0') {
            should_eliminate = 1;
        }

        // if already inside a multiline comment block...
        if (multi_comment != 0) {
            should_eliminate = 1; // ... eliminate the current line ...
            // ... and search for the multiline end, wherever it is
            if (strstr(current->line_content, "*/") != NULL) {
                multi_comment = 0;
            }
        } 
        // otherwise, check for standard cases:
        else if (strncmp(start, "#define", 7) == 0 || strncmp(start, "#include", 8) == 0) { // preprocessor directives
            should_eliminate = 1;
        } 
        else if (start[0] == '/' && start[1] == '/') { // single-line comment
            should_eliminate = 1;
        } 
        else if (start[0] == '/' && start[1] == '*') { // multi-line comment starts
            should_eliminate = 1;
            multi_comment = 1;
            
            // check if it actually ends in this same line (/*...*/)
            if (strstr(start + 2, "*/") != NULL) {
                multi_comment = 0;
            }
        }

        // node removal and de-allocation logic
        if (should_eliminate != 0) {
            if (prev != NULL) { // node to delete is somewhere down the list
                prev->next = next;
            } else {
                head = next; // node to delete is the head
            }
            free(current->line_content);
            free(current);
        } else {
            trim_inplace(current->line_content); // clean the remaining line further, because we like spoon-feeding the parser
            prev = current;
        }
        current = next;
    }

    return head;
}

