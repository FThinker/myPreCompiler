#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/data_structures.h"
#include "../src/validator.h"

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED   "\033[0;31m"
#define COLOR_RESET "\033[0m"

// ######################################################################################### //
//                                        FUNCTIONS                                          //
// ######################################################################################### //


void test_is_valid_identifier(){
    printf("Running test_is_valid_identifier... ");

    
    // Case 0: empty strings or null
    assert(is_valid_identifier(NULL) == false);
    assert(is_valid_identifier("") == false);

    // Case 1: names that start with letter or underscore
    assert(is_valid_identifier("valid") == true);
    assert(is_valid_identifier("_valid") == true);
    assert(is_valid_identifier("1not_valid") == false);    // number as start not admitted

    // Case 2: alphanumerics and underscores
    assert(is_valid_identifier("var_123_ok") == true);
    assert(is_valid_identifier("var-with-dashes") == false); // dash not admitted
    assert(is_valid_identifier("var space") == false);       // spaces not admitted
    assert(is_valid_identifier("var@mail") == false);         // special chars not admitted

    // Case 3: mustn't be a reserved keyword
    assert(is_valid_identifier("while") == false);
    assert(is_valid_identifier("typedef") == false);
    assert(is_valid_identifier("ilovegenshinimpact") == true);            // not a keyword
    
    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ----------------------------------------------------------------------------------------- //


void test_is_c_keyword() {
    printf("Running test_is_c_keyword... ");

    // Positive tests
    assert(is_c_keyword("int") == true);
    assert(is_c_keyword("while") == true);
    assert(is_c_keyword("struct") == true);
    assert(is_c_keyword("_Bool") == true);

    // Negative tests
    assert(is_c_keyword("myinteger") == false);
    assert(is_c_keyword("my_variable") == false);
    assert(is_c_keyword("") == false);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


//----------------------------------------------------------------------------------------//


void test_is_valid_type() {
    printf("Running test_is_valid_type... ");

    TypedefNode* custom_types = NULL;
    TypedefNode* node1 = create_typedef("size_custom");
    TypedefNode* node2 = create_typedef("my_integer");
    TypedefNode* node3 = create_typedef("point_struct");
    add_typedef(&custom_types, node1);
    add_typedef(&custom_types, node2);
    add_typedef(&custom_types, node3);

    // Case 0: NULL check
    assert(is_valid_type(NULL, custom_types) == false);

    // Case 1: Standard types
    assert(is_valid_type("int", custom_types) == true);
    assert(is_valid_type("unsigned long", custom_types) == true);
    assert(is_valid_type("double", custom_types) == true);

    // Case 2: Custom types
    assert(is_valid_type("my_integer", custom_types) == true);
    assert(is_valid_type("point_struct", custom_types) == true);

    // Case 3: Non-existing or invalid types
    assert(is_valid_type("huge_float", custom_types) == false);
    assert(is_valid_type("stringa", custom_types) == false);

    free_typedefs(custom_types);

    printf(COLOR_GREEN "PASSED!" COLOR_RESET "\n");
}


// ######################################################################################### //
//                                          MAIN                                             //
// ######################################################################################### //


int main() {
    printf(COLOR_GREEN "===== BEGINNING VALIDATOR TEST =====" COLOR_RESET "\n");
    
    test_is_c_keyword();
    test_is_valid_identifier();
    test_is_valid_type();

    printf(COLOR_GREEN "===== ALL TESTS PASSED SUCCESSFULLY =====" COLOR_RESET "\n");
    return 0;
}