#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handler.h"

LineNode* open_file(const char* filepath) {
    // Check 0: Validate filepath pointer
    if (filepath == NULL) {
        fprintf(stderr, "Error: provided filepath is NULL.\n");
        return NULL;
    }

    // Attempt to open the file
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return NULL;
    }

    // Check 1: Verify if the file is completely empty or corrupted
    // borrow the first character to test the stream...
    int first_char = fgetc(file);
    if (first_char == EOF) {
        if (feof(file)) {
            fprintf(stderr, "Error reading from file: The file is empty.\n");
        } else {
            perror("Error reading from file: Stream corrupted.");
        }
        fclose(file);
        return NULL;
    }
    
    ungetc(first_char, file); // ...and put it back!

    LineNode* head = NULL;
    char buffer[4096]; // Standard max line buffer
    int current_line_number = 1;

    // Read line-by-line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t len = strlen(buffer);

        // remove ending newline (\n) and carriage return (\r) for Windows compatibility
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            if (len > 1 && buffer[len - 2] == '\r') {
                buffer[len - 2] = '\0';
            }
        }

        // create node for the current line
        LineNode* new_node = create_line(buffer, current_line_number);
        if (new_node == NULL) {
            fprintf(stderr, "Error: Heap memory allocation failed at line %d.\n", current_line_number);
            free_lines(head); // clean up already allocated lines to prevent leaks
            fclose(file);
            return NULL;
        }

        add_line(&head, new_node); // at this point, if nothing blew up, the new line is safe to append.
        current_line_number++;
    }

    // Check 2: make sure the loop terminated due to EOF and not a read error
    if (ferror(file)) {
        perror("Error occurred while reading lines from file");
        free_lines(head);
        fclose(file);
        return NULL;
    }

    // Check 3: close file safely
    if (fclose(file) != 0) {
        perror("Error closing input file");
        // at this point the list is complete, no need to throw it away just because we can't close the input file
    }

    return head;
}


// ----------------------------------------------------------------------------------------- //


void write_file(const char* output_filepath, const int valid_name_false, const int is_used_false){
    // Check 0: Validate filepath pointer
    if (output_filepath == NULL) {
        fprintf(stderr, "Error: provided filepath is NULL.\n");
        return NULL;
    }

    // Attempt to open the file
    FILE* file = fopen(output_filepath, "w"); //decidere se vogliamo solo scriverlo o aggiungere contenuti ad un file già pieno "w/a"
    if (file == NULL) {
        perror("Error opening input file");
        return NULL;
    }

}