#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/data_structures.h" 

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


void test_create_variable() {
    printf("Running test_create_variable... ");
    
    VariableNode* node = create_variable("var", "int", 10);
    
    // Verify that created node isn't null
    assert(node != NULL);

    // Verify that values were copied correctly
    assert(strcmp(node->name, "var") == 0); // verify strings using strcmp()
    assert(strcmp(node->type, "int") == 0);
    assert(node->line_declared == 10);
    assert(node->is_used == false);
    assert(node->next == NULL);
    
    // Manual cleaning
    free(node->name);
    free(node->type);
    free(node);
    
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //


void test_create_typedef() {
    printf("Running test_create_typedef... ");
    
    TypedefNode* node = create_typedef("var");
    
    // Verify that created node isn't null
    assert(node != NULL);

    // Verify that values were copied correctly
    assert(strcmp(node->name, "var") == 0);
    assert(node->next == NULL);
    
    // Manual cleaning
    free(node->name);
    free(node);
    
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //


void test_add_variable_empty_list(){
    printf("Running test_add_variable_empty_list... ");

    VariableNode* head = NULL; // Empty list
    VariableNode* node = create_variable("var", "int", 10);

    add_variable(&head, node);

    // Head mustn't be NULL anymore
    assert(head != NULL);
    // Head must be the newly added node
    assert(strcmp(head->name, "var") == 0);
    assert(head->next == NULL);

    // Manual cleaning
    free(node->name);
    free(node->type);
    free(node);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //


void test_add_variable_populated_list() {
    printf("Running test_add_variable_populated_list... ");
    
    VariableNode* head = NULL;
    VariableNode* node1 = create_variable("one", "int", 1);
    VariableNode* node2 = create_variable("two", "float", 2);
    VariableNode* node3 = create_variable("three", "char", 3);
    
    add_variable(&head, node1);
    add_variable(&head, node2);
    add_variable(&head, node3);
    
    assert(head == node1);                     // Is the first node the head?
    assert(head->next == node2);               // Is the second node2?
    assert(head->next->next == node3);         // Is the third node3?
    assert(head->next->next->next == NULL);    // Does the list end after node3?
    
    // Manual cleaning
    free(node1->name); 
    free(node1->type); 
    free(node1);
    free(node2->name); 
    free(node2->type); 
    free(node2);
    free(node3->name); 
    free(node3->type); 
    free(node3);
    
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //


void test_add_typedef_empty_list(){
    printf("Running test_add_typedef_empty_list... ");

    TypedefNode* head = NULL; // Empty list
    TypedefNode* node = create_typedef("var");

    add_typedef(&head, node);

    // Head mustn't be NULL anymore
    assert(head != NULL);
    // Head must be the newly added node
    assert(strcmp(head->name, "var") == 0);
    assert(head->next == NULL);

    // Manual cleaning
    free(node->name);
    free(node);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //


void test_add_typedef_populated_list() {
    printf("Running test_add_typedef_populated_list... ");
    
    TypedefNode* head = NULL;
    TypedefNode* node1 = create_typedef("one");
    TypedefNode* node2 = create_typedef("two");
    TypedefNode* node3 = create_typedef("three");
    
    add_typedef(&head, node1);
    add_typedef(&head, node2);
    add_typedef(&head, node3);
    
    assert(head == node1);                     // Is the first node the head?
    assert(head->next == node2);               // Is the second node2?
    assert(head->next->next == node3);         // Is the third node3?
    assert(head->next->next->next == NULL);    // Does the list end after node3?
    
    // Manual cleaning
    free(node1->name); 
    free(node1);
    free(node2->name); 
    free(node2);
    free(node3->name); 
    free(node3);
    
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //

void test_free_variables() {
    printf("Running test_free_variables... ");
    
    VariableNode* head = NULL;
    add_variable(&head, create_variable("var1", "int", 10));
    add_variable(&head, create_variable("var2", "float", 20));
    add_variable(&head, create_variable("var3", "char", 30));
    
    // If there are issues with pointers and memory, it should blow up here
    free_variables(head);
    
    // If nothing blew up, it's pretty much safe
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //

void test_free_typedefs() {
    printf("Running test_free_variables... ");
    
    TypedefNode* head = NULL;
    add_typedef(&head, create_typedef("var1"));
    add_typedef(&head, create_typedef("var2"));
    add_typedef(&head, create_typedef("var3"));
    
    // If there are issues with pointers and memory, it should blow up here
    free_typedefs(head);
    
    // If nothing blew up, it's pretty much safe
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ######################################################################################### //
//                                          MAIN                                             //
// ######################################################################################### //


int main() {
    printf(COLOR_GREEN "===== BEGINNING DATA STRUCTURES TEST =====" COLOR_RESET "\n");
    
    test_create_variable();
    test_create_typedef();
    test_add_variable_empty_list();
    test_add_variable_populated_list();
    test_add_typedef_empty_list();
    test_add_typedef_populated_list();
    test_free_variables();
    test_free_typedefs();
    
    printf(COLOR_GREEN "===== ALL TESTS PASSED SUCCESSFULLY =====" COLOR_RESET "\n");
    return 0;
}