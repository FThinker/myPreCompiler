#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data_structures.h"


//----------------------------------------------------------------------------------------//


const char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "inline", "int", "long",
        "register", "restrict", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while",
        "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex",
        "_Generic", "_Imaginary", "_Noreturn", "_Static_assert",
        "_Thread_local"
};

int keywords_size = sizeof(keywords) / sizeof(keywords[0]);

const char* types[] = {
    "char", "unsigned char", "signed char", "int", "unsigned int", "short", 
    "unsigned short", "long", "unsigned long", "float", "double", "long double"
};

int types_size = sizeof(types) / sizeof(types[0]);

//----------------------------------------------------------------------------------------//


bool is_c_keyword(const char* name) {
    for(int i = 0; i < keywords_size; i++){
        if(strcmp(name, keywords[i]) == 0){
            return true;
        }
    }
    return false;
}


//----------------------------------------------------------------------------------------//


bool is_valid_identifier(const char* name) {
    // Case 0: empty name
    if(name == NULL || name[0] == '\0') {
        return false;
    }

    // Case 1: name doesn't start with _ or letter
    if(name[0] != '_' && !isalpha((unsigned char)name[0])) {
            return false;
    }

    // Case 2: name contains something other than _ or letters/numbers
    for(int i=1; name[i] != '\0'; i++){
        if(name[i] != '_' && !isalnum((unsigned char)name[i])){
            return false;
        }
    }

    // Case 3: return false if name is a reserved keyword
    return !is_c_keyword(name);
}


//----------------------------------------------------------------------------------------//


bool is_valid_type(const char* type_name, TypedefNode* custom_types_head) {
	// Case 0: type_name is null
    if(type_name == NULL){
        return false;
    }
    
    // Case 1: type_name is standard type
    for(int i=0; i < types_size; i++){
        if(strcmp(type_name, types[i]) == 0){
            return true;
        }
    }
    
    // Case 2: type_name is a user-defined type
    while(custom_types_head != NULL){
        if(strcmp(type_name, custom_types_head->name) == 0){
            return true;
        }
        custom_types_head = custom_types_head->next;
    }
    return false;
}


//----------------------------------------------------------------------------------------//