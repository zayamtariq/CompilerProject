#include <stdio.h> 
#include "Data.h" 

FILE * fileToCompile; // can share this among all files 
struct Token GlobalToken; // global for the token that has been most recently scanned in 