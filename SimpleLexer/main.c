#include <stdio.h>
#include "Token.h"
#include "SimpleLexer.h"

// declaration
FILE * fileToCompile;  

char* tokenTypes[] = {"+", "-", "*", "/", "intliteral"}; 

// this function should just keep scanning, creating, and then printing tokens
static void scan_file() { 
    struct Token t; 

    // while there's still tokens to scan    
    while (scan(&t)) { 
        printf("Token type: %s ", tokenTypes[t.token]); 
        if (t.token == T_NUMBER) { 
            printf("Token value: %d", t.intvalue); 
        }
        printf("\n"); 
    }
}

int main()  
{ 

    fileToCompile = fopen("test_file", "r"); 

    scan_file(); 

    return 0; 
}