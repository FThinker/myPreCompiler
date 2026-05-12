#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/data_structures.h"
#include "../src/data_structures.c"
#include "../src/file_cleaner.h"
#include "../src/file_cleaner.c"

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


void test_clean_line_start() {
    printf("Running test_clean_line_start...");

    char str1[50] = "    hello";
    clean_line_start(str1);
    assert(strcmp(str1, "hello") == 0);

    char str2[50] = "\t\n  tabs and spaces";
    clean_line_start(str2);
    assert(strcmp(str2, "tabs and spaces") == 0);

    char str3[50] = "no_spaces";
    clean_line_start(str3);
    assert(strcmp(str3, "no_spaces") == 0);

    char str4[50] = "    ";
    clean_line_start(str4);
    assert(strcmp(str4, "") == 0);

    printf(COLOR_GREEN " PASSED!" COLOR_RESET "\n");
}


void test_clean_line_end() {
    printf("Running test_clean_line_end...");

    char str1[50] = "hello    ";
    clean_line_end(str1, strlen(str1));
    assert(strcmp(str1, "hello") == 0);

    char str2[50] = "trailing tabs\t\t";
    clean_line_end(str2, strlen(str2));
    assert(strcmp(str2, "trailing tabs") == 0);

    char str3[50] = "    both ends    ";
    clean_line_start(str3);
    clean_line_end(str3, strlen(str3));
    assert(strcmp(str3, "both ends") == 0);

    printf(COLOR_GREEN " PASSED!" COLOR_RESET "\n");
}


void test_clean_file(){
    printf("Running test_clean_file...");

    LineNode* head = NULL;
    LineNode* line1 = create_line("      #define blah", 1);
    LineNode* line2 = create_line("#include blah", 2);
    LineNode* line3 = create_line("     //i want a ice cream     ", 3);
    LineNode* line4 = create_line("/* hello world", 4);
    LineNode* line5 = create_line("5 stars no drama     ", 5);
    LineNode* line6 = create_line("go home*/", 6);
    LineNode* line7 = create_line("int age = 7       ", 7);
    LineNode* line8 = create_line("void funct() {", 8);
    add_line(&head, line1);
    add_line(&head, line2);
    add_line(&head, line3);
    add_line(&head, line4);
    add_line(&head, line5);
    add_line(&head, line6);
    add_line(&head, line7);
    add_line(&head, line8);

    LineNode* new_head = clean_file(head);
    
    assert(new_head != NULL);
    assert(new_head->line_number == 7);
    assert(strcmp(new_head->line_content, "int age = 7") == 0);

    assert(new_head->next != NULL);
    assert(new_head->next->line_number == 8);
    assert(strcmp(new_head->next->line_content, "void funct() {") == 0);

    assert(new_head->next->next == NULL);

    LineNode* curr = new_head;
    while(curr != NULL) {
        LineNode* temp = curr;
        curr = curr->next;
        free(temp->line_content);
        free(temp);
    }

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ######################################################################################### //
//                                          MAIN                                             //
// ######################################################################################### //


int main() {
    printf(COLOR_GREEN "===== BEGINNING VALIDATOR TEST =====" COLOR_RESET "\n");
    
    test_clean_line_start();
    test_clean_line_end();
    test_clean_file();

    printf(COLOR_GREEN "===== ALL TESTS PASSED SUCCESSFULLY =====" COLOR_RESET "\n");
    return 0;
}