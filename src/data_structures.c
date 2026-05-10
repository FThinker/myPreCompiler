#include <stdlib.h>
#include <string.h>
#include "data_structures.h"


// ----------------------------------------------------------------------------------------- //


VariableNode* create_variable(const char* name, const char* type, int line){
    VariableNode* new_var = malloc(sizeof(VariableNode));

    if(new_var == NULL){
        // handle this
        return NULL;
    }

    new_var->name = strdup(name); // == ` (*new_var).name = name `
    new_var->type = strdup(type); // REMEMBER to free() string fields as well!!!
    new_var->line_declared = line;
    new_var-> is_used = false;
    new_var-> valid_name = false;
    new_var-> valid_type = false;
    new_var->next = NULL;

    return new_var;
} 


// ----------------------------------------------------------------------------------------- //


TypedefNode* create_typedef(const char* name){
    TypedefNode* new_type = malloc(sizeof(TypedefNode));

    if(new_type == NULL){
        // handle this
        return NULL;
    }

    new_type->name = strdup(name);
    new_type->next = NULL;

    return new_type;
}


// ----------------------------------------------------------------------------------------- //


LineNode* create_line(const char* content, int line_number){
    LineNode* new_line = malloc(sizeof(LineNode));

    if(new_line == NULL){
        // handle this
        return NULL;
    }

    new_line->line_content = strdup(content);
    new_line->line_number = line_number;
    new_line->next = NULL;

    return new_line;
}

// ----------------------------------------------------------------------------------------- //


void add_variable(VariableNode** head, VariableNode* new_node){
    // Case 1: list is empty
    if(*head == NULL){
        *head = new_node;
        return;
    }

    // Case 2: list isn't empty
    VariableNode* current = *head;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = new_node; // Finally, append
    return;
}; 


// ----------------------------------------------------------------------------------------- //


void add_typedef(TypedefNode** head, TypedefNode* new_node){
    if(*head == NULL){
        *head = new_node;
        return;
    }

    TypedefNode* current = *head;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = new_node;
    return;
}


// ----------------------------------------------------------------------------------------- //


void add_line(LineNode** head, LineNode* new_node){
    if(*head == NULL){
        *head = new_node;
        return;
    }

    LineNode* current = *head;
    while(current->next != NULL){
        current = current->next;
    }

    current->next = new_node;
    return;
}

// ----------------------------------------------------------------------------------------- //


void free_variables(VariableNode* head){
    VariableNode* current = head;

    while(current != NULL){
        VariableNode* next_node = current->next;
        free(current->name);
        free(current->type);
        free(current);
        current = next_node;
    }
} 


// ----------------------------------------------------------------------------------------- //


void free_typedefs(TypedefNode* head){
    TypedefNode* current = head;

    while(current != NULL){
        TypedefNode* next_node = current->next;
        free(current->name);
        free(current);
        current = next_node;
    }
}



// ----------------------------------------------------------------------------------------- //


void free_lines(LineNode* head){
    LineNode* current = head;

    while(current != NULL){
        LineNode* next_node = current->next;
        free(current->line_content);
        free(current);
        current = next_node;
    }
}


// ----------------------------------------------------------------------------------------- //