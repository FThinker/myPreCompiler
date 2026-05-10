#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "../src/file_handler.h"

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //

void test_open_nonexistent_file() {
    printf("Running test_open_nonexistent_file... ");

    // Try opening a file that doesn't exist
    LineNode* head = open_file("i_just_made_this_up.c");
    assert(head == NULL);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}

// ----------------------------------------------------------------------------------------- //

void test_open_empty_file() {
    printf("Running test_open_empty_file... ");

    const char* empty_filepath = "temp_empty_test_file.c";

    FILE* f = fopen(empty_filepath, "w");
    assert(f != NULL);
    fclose(f);

    // based on the function's signature, an empty file is treated as an error.
    LineNode* head = open_file(empty_filepath);
    assert(head == NULL);
    remove(empty_filepath);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}

// ----------------------------------------------------------------------------------------- //

void test_open_valid_file() {
    printf("Running test_open_valid_file... ");

    const char* valid_filepath = "temp_valid_test_file.c";

    // A very simple test file
    // also checking if both linux and windows (\n, \r\n) caveats work as intended.
    FILE* f = fopen(valid_filepath, "w");
    assert(f != NULL);
    fputs("int main() {\n", f);
    fputs("    int number = 42;\r\n", f); // windows carriage return
    fputs("\n", f);                       // empty line
    fputs("    return 0;\n", f);
    fputs("}\n", f);
    fclose(f);

    LineNode* head = open_file(valid_filepath);
    assert(head != NULL);

    LineNode* current = head;

    // line 1:
    assert(current != NULL);
    assert(strcmp(current->line_content, "int main() {") == 0);
    assert(current->line_number == 1);
    current = current->next;

    // line 2: (\r\n should be removed)
    assert(current != NULL);
    assert(strcmp(current->line_content, "    int number = 42;") == 0);
    assert(current->line_number == 2);
    current = current->next;

    // line 3: (empty line, should become and empty string "")
    assert(current != NULL);
    assert(strcmp(current->line_content, "") == 0);
    assert(current->line_number == 3);
    current = current->next;

    // line 4:
    assert(current != NULL);
    assert(strcmp(current->line_content, "    return 0;") == 0);
    assert(current->line_number == 4);
    current = current->next;

    // line 5:
    assert(current != NULL);
    assert(strcmp(current->line_content, "}") == 0);
    assert(current->line_number == 5);
    
    // make sure list ends as expected
    assert(current->next == NULL);

    free_lines(head);   // free memory to avoid making a mess
    remove(valid_filepath); // also remove the temporary file

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}

// ----------------------------------------------------------------------------------------- //

int main() {
    printf(COLOR_GREEN "===== BEGINNING FILE HANDLER TEST =====" COLOR_RESET "\n");

    // !!! temporary disable stderr buffering 
    // to see open_file errors correctly sorted in terminal
    setbuf(stderr, NULL);

    test_open_nonexistent_file();
    test_open_empty_file();
    test_open_valid_file();

    printf(COLOR_GREEN "===== ALL TESTS PASSED SUCCESSFULLY =====" COLOR_RESET "\n");
    return 0;
}