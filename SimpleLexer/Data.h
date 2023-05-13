// what if we had a file that just had all our data for us 
#include <stdio.h> 
#include "Token.h" 

extern FILE * fileToCompile; // can share this among all files 
extern struct Token GlobalToken; 
