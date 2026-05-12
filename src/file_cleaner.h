#ifndef FILE_CLEANER_H
#define FILE_CLEANER_H
#include "data_structures.h"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


/**
 * @brief Cleans a linked list of lines by removing preprocessor directives and comments.
 *
 * Iterates through the LineNode list and deletes nodes that match any of these criteria:
 * 
 * Starts with a preprocessor directive (#define, #include).
 * 
 * Contains a single-line comment (starts with //).
 * 
 * Is part of a multi-line comment block.
 * 
 * @note This function deallocates the memory of any removed nodes.
 * @param head The head of LineNode linked list.
 * @return The head of LineNode linked list.
 */
LineNode* clean_file(LineNode* head);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Removes leading whitespace from a string in-place.
 *
 * This function shifts the content of the string to the left if initial spaces, 
 * tabs, or other whitespace characters are present. It uses memmove to safely 
 * handle overlapping memory regions and ensures the string remains 
 * null-terminated.
 * @note If the line consists entirely of whitespace, it will be reduced to 
 * an empty string ("\0").
 * @param line_content A pointer to the null-terminated string to be trimmed. 
 * Must not be NULL.
 */
void clean_line_start(char* line_content);

// ----------------------------------------------------------------------------------------- //


/**
 * @brief Removes trailing whitespace from a string in-place.
 * Truncates the string by replacing the first whitespace character following 
 * the last non-whitespace character with a null terminator ('\0').
 * @param line_content A pointer to the null-terminated string to be trimmed.
 * @param size_line The current length of the string (excluding the null terminator).
 */
void clean_line_end(char* line_content, int size_line);

// ----------------------------------------------------------------------------------------- //

#endif