#ifndef PARSER_H
#define PARSER_H

#include "data_structures.h"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //

/**
 * @brief Parses the cleaned lines of a C source file to extract variables, typedefs, and checks variable usage.
 *
 * Implements a simple sequential 3-state machine:
 * - State 0: Global declarations and user-defined typedefs before main().
 * - State 1: Local declarations, contiguous, at the beginning of main().
 * - State 2: Actual code body instructions where variable usage is checked.
 *
 * @param clean_lines_head The head of the cleaned LineNode linked list.
 * @param var_list_head Double pointer to the head of the VariableNode list to be populated.
 * @param custom_types_head Double pointer to the head of the TypedefNode list to be populated.
 */
void parse_file(LineNode* clean_lines_head, VariableNode** var_list_head, TypedefNode** custom_types_head);

// ----------------------------------------------------------------------------------------- //

#endif