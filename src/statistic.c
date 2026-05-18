#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "data_structures.h"
#include "file_handler.h"
#include "statistic.h"


void generate_report(VariableNode* head, const char* output_filepath, bool verbose) {
    //Check if the head is NULL
    if(head == NULL){
        printf("Error: The linked list is null\n");
        return;
    }

    int valid_name_false = 0;
    int is_used_false = 0;
    VariableNode* current = head;

    //Count the valid_name_false and is_used_false for each node
    while(current != NULL){
        if(current->valid_name == false){
            valid_name_false += 1;
        }
        if(current->is_used == false){
            is_used_false += 1;
        }
        current = current->next;
    }

    //Write the output on a file
    if(output_filepath != NULL){
        write_file(output_filepath, valid_name_false, is_used_false);
    } else {
        printf("Error: output_filepath is invalid\n");
    }

    //Print the result on the terminal
    if(verbose){
        printf("valid_name == false : %d \n is_used == false : %d \n", valid_name_false, is_used_false);
    }
}
