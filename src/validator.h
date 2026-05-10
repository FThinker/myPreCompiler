#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "data_structures.h"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


/**
 * @brief Checks wether a given variable name is valid or not.
 *
 * Iterates over a char array and returns false if any of the following conditions isn't respected:
 * 
 * a variable name is valid if and only if:
 * 
 * it starts with a letter or an underscore '_'
 * 
 * it only contains alphanumeric and underscore characters
 * 
 * it isn't a reserved C keyword.
 * 
 *
 * @param name The variable's name.
 * @return The name's valid state.
 */
bool is_valid_identifier(const char* name);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Checks if the variable name is a reserved C keyword.
 *
 * Iterates a list of known keywords and returns false if a match is found.
 *
 * @param name The variable's name.
 * @return Wether the variable name is a reserved keyword or not.
 */
bool is_c_keyword(const char* name);


// ----------------------------------------------------------------------------------------- //


/**
 * @brief Checks if the variable type is valid.
 *
 * Iterates a list of known types (both standard and user-defined) and returns true if a match is found.
 *
 * @param name The variable type.
 * @param custom_types_head The pointer to the user-defined types linked list.
 * @return Wether the variable type is valid or not.
 */
bool is_valid_type(const char* type_name, TypedefNode* custom_types_head);


// ----------------------------------------------------------------------------------------- //


#endif