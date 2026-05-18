#ifndef STATISTIC_H
#define STATISTIC_H

#include "data_structures.h"
#include <stdbool.h>

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


/**
 * @brief Generates a statistical report from a linked list of variables.
 *
 * Iterates through the VariableNode list and counts the occurrences where
 * variables have an invalid name (valid_name == false) or are unused (is_used == false).
 * It then logs these metrics to a specified file and optionally displays them 
 * on the terminal.
 * @param head The head of the VariableNode linked list.
 * @param output_filepath The path to the file where the report statistics will be saved.
 * @param verbose If true, prints the resulting counts directly to the standard output.
 */
void generate_report(VariableNode* head, const char* output_filepath, bool verbose);


// ----------------------------------------------------------------------------------------- //

#endif
















#endif