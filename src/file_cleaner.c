#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"

LineNode* clean_file(LineNode* head) {
    LineNode* prev = NULL;
    LineNode* current = head;
    LineNode* next = current->next;
    int multi_comment = 0;

    if(current == NULL){
        fprintf(stderr, "Error: No lines to clean. The file appears to be empty.\n");
        return;
    }

    while(current != NULL){
        next = current->next;
        int size_line = strlen(current->line_content);
        int should_eliminate = 0;
        //Case 1: The line start with #define or #include
        if(size_line >= 7 && (strncmp(current->line_content, "#define", 7) == 0 || strncmp(current->line_content, "#include", 8) == 0)){
            should_eliminate = 1;
        }
        //Case 2: The line is a single-comment
        if(size_line >= 2 && (current->line_content[0] == '/' && current->line_content[1] == '/')){
            should_eliminate = 1;
        }
        //Case 3: The line is a multi-comment
        if(size_line >= 2 && (current->line_content[0] == '/' && current->line_content[1] == '*')){
            multi_comment = 1;
            should_eliminate = 1;
        }
        if(multi_comment != 0){
            should_eliminate = 1;
            if(current->line_content[size_line - 2] == '*' && current->line_content[size_line - 1] == '/'){
                multi_comment = 0;
            }
        }

        if(should_eliminate != 0){
            if(prev != NULL){
                prev->next = next;
            } else {
                head = next;
            }
            free(current->line_content);
            free(current);
        } else {
            prev = current;
        }
        current = next;
    }
    //The return is needed because the head of the linked list might change
    return head;
}

