#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdbool.h>


// ######################################################################################### //
//                                     DATA STRUCTURES                                       //
// ######################################################################################### //


typedef struct VariableNode { 
	char* name; 
	char* type; 
	int line_declared; 
	bool is_used; 
	bool valid_name; 
	bool valid_type; 
	struct VariableNode* next; 
} VariableNode;


// ----------------------------------------------------------------------------------------- //


typedef struct TypedefNode { 
	char* name; 
	struct TypedefNode* next; 
} TypedefNode;


// ----------------------------------------------------------------------------------------- //


typedef struct LineNode {
    char* line_content;
    int line_number;
    struct LineNode* next;
} LineNode;


// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


/**
 * @brief Creates a new singular variable node
 *
 * Creates a new node for a variable and dynamically allocates memory for it.
 * This node is intended for use as a link node in a linked list.
 * 
 * All boolean flags are initialized as false for a fail-safe approach.
 *
 * @param name The variable's name.
 * @param type The variable's declared type. Could be either standard, or user defined.
 * @param line The line at which the variable has been declared.
 * @warning The function may return NULL if heap memory is insufficient.
 * @return The created node.
 */
VariableNode* create_variable(const char* name, const char* type, int line);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Creates a new singular user-type node
 *
 * Creates a new node for a user defined type and dynamically allocates memory for it.
 * This node is intended for use as a link node in a linked list.
 *
 * @param name The type's name.
 * @warning The function may return NULL if heap memory is insufficient.
 * @return The created node.
 */
TypedefNode* create_typedef(const char* name);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Creates a new singular line node.
 *
 * Dynamically allocates memory for a file line content and its line number.
 *
 * @param content The raw string content of the line.
 * @param line_number The line number in the source file.
 * @return The created node, or NULL if heap memory is insufficient.
 */
LineNode* create_line(const char* content, int line_number);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Appends a variable node to the list.
 *
 * If the list is empty, the passed node becomes the new head of the list.
 * If the list isn't empty, it keeps iterating until it finds a node whose `next` field points to NULL.
 * When found, it makes it point to the passed node instead.
 *
 * @param head The variable list's head.
 * @param new_node The variable node to append.
 */
void add_variable(VariableNode** head, VariableNode* new_node);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Appends a user-type node to the list.
 *
 * If the list is empty, the passed node becomes the new head of the list.
 * If the list isn't empty, it keeps iterating until it finds a node whose `next` field points to NULL.
 * When found, it makes it point to the passed node instead.
 *
 * @param head The typedef list's head.
 * @param new_node The typedef node to append.
 */
void add_typedef(TypedefNode** head, TypedefNode* new_node);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Appends a line node to the linked list.
 *
 * @param head The line list's head.
 * @param new_node The line node to append.
 */
void add_line(LineNode** head, LineNode* new_node);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Releases the heap memory occupied by a variable linked list (in a safe way).
 *
 * The list is freed in an inside-out manner, prioritizing field deletion before node deletion in order to avoid memory leaks.
 * 
 * @param head The variable list's head.
 */
void free_variables(VariableNode* head);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Releases the heap memory occupied by a typedef linked list (in a safe way).
 *
 * The list is freed in an inside-out manner, prioritizing field deletion before node deletion in order to avoid memory leaks.
 * 
 * @param head The typedef list's head.
 */
void free_typedefs(TypedefNode* head);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Releases the heap memory occupied by a line linked list.
 *
 * @param head The line list's head.
 */
void free_lines(LineNode* head);


// ----------------------------------------------------------------------------------------- //


#endif