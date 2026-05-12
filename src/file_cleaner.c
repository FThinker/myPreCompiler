#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data_structures.h"


// ----------------------------------------------------------------------------------------- //


void clean_line_start(char* line_content) {

    if(line_content == NULL){
        return;
    }

    //Clean the start of the line if it is present blank space
    char* line_content_clean = line_content;
    while(*line_content_clean != '\0' && isspace((unsigned char)*line_content_clean)){
        line_content_clean++;
    }

    int size_line_clean = strlen(line_content_clean);
    if(line_content != line_content_clean){
        memmove(line_content, line_content_clean, size_line_clean + 1);
    }
}


// ----------------------------------------------------------------------------------------- //


void clean_line_end(char* line_content, int size_line){
    //Clean the end of the line if it is present blank space
    while(size_line > 0 && isspace((unsigned char)line_content[size_line - 1])){
        size_line--;
    }
    line_content[size_line] = '\0';
}


// ----------------------------------------------------------------------------------------- //


LineNode* clean_file(LineNode* head) {

    if(head == NULL){
        fprintf(stderr, "Error: No lines to clean. The file appears to be empty.\n");
        return NULL;
    }

    LineNode* prev = NULL;
    LineNode* current = head;
    LineNode* next = NULL;
    int multi_comment = 0;

    while(current != NULL){
        next = current->next;

        clean_line_start(current->line_content);

        int size_line = strlen(current->line_content); //Don't count the \0
        int should_eliminate = 0;

        //Case 1: The line start with #define or #include
        if(size_line >= 7 && (strncmp(current->line_content, "#define", 7) == 0 || strncmp(current->line_content, "#include", 8) == 0)){
            should_eliminate = 1;
        }
        //Case 2: The line is a single-comment
        else if(size_line >= 2 && (current->line_content[0] == '/' && current->line_content[1] == '/')){
            should_eliminate = 1;
        }
        //Case 3: The line is a multi-comment
        else if(size_line >= 2 && (current->line_content[0] == '/' && current->line_content[1] == '*')){
            multi_comment = 1;
            should_eliminate = 1;
            if(strstr(current->line_content + 2, "*/") != NULL){
                multi_comment = 0;
            }
        }
        else if(multi_comment != 0){
            should_eliminate = 1;
            if(strstr(current->line_content, "*/") != NULL){
                multi_comment = 0;
            }
        }
        //Case 4: The line is empty
        else if(current->line_content[0] == '\0'){
            should_eliminate = 1;
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
            clean_line_end(current->line_content, size_line);
            prev = current;
        }
        current = next;
    }
    //The return is needed because the head of the linked list might change
    return head;
}


// ----------------------------------------------------------------------------------------- //
