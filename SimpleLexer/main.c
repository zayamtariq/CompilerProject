#include <stdio.h>
#include "Token.h"
#include "SimpleLexer.h"
#include "Data.h"

char* tokenTypes[] = {"+", "-", "*", "/", "Integer"}; 

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

// just used for debugging to print out file 
static void print_file() { 
    char c; 
    // Read contents from file
    c = fgetc(fileToCompile);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fileToCompile);
    }
}

int main()  
{ 

    // printf("Hello World!"); // sanity check to make sure program runs  

    fileToCompile = fopen("SimpleLexer/test_file", "r"); // need to be very careful with relative/absolute paths here

    scan_file(); 

    return 0; 
}