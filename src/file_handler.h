#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "data_structures.h"

/**
 * @brief Opens a file, validates it, and reads it line by line into a linked list.
 *
 * Checks if the filepath is valid, if permissions allow reading, and handles specific
 * errors such as empty or corrupted files. Strips trailing newline characters.
 *
 * @param filepath The path to the input file.
 * @warning An empty file is regarded as an error, and thus returns NULL.
 * @return A pointer to the head of the LineNode linked list, or NULL if errors occur.
 */
LineNode* open_file(const char* filepath);

#endif