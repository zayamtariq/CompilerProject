// simple lexer has the following elements: 
// 4 math operations: *, +, -, / 
// whole numbers with 1 or more digits 
#include "Token.h"
#include <stdio.h> 
#include "SimpleLexer.h"

// extern linking from main.c
extern FILE * fileToCompile; 
int Putback; // will hold the character we wanted to "put back", if we went too far 
int Line; // keep track of what line we are on currently while reading. 


// function that gets the next character from the input file
// returns the integer representation of character, i guess  
static int next(void) { 
    int c; // what character we're going to be returning 

    if (Putback) {
        c = Putback;  
        Putback = 0; 
        return c; 
    }

    // else, we just need to read from the file again 
    c = getc(fileToCompile); 
    if (c == '\n') Line++; 
    return c; 
    // if this returns an EOF error, we will handle that at scan() function 
}

// if we've read too far in our input stream, we should "put back" the character
static void putback(int c) { 
    Putback = c; 
}

// function that skips over whitespace/garbage until we hit a character
// returns: the first "useful" character that we need 
static int skip(void) { 
    int c; 
    
    c = next(); 
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        c = next();
    } 
    return (c);
}

// scan and return whatever next token has been found 
// returns 1 if valid token, 0 if we're done scanning 
int scan(struct Token *t) { 
    // this is the function that puts it all together 
    int c; 

    c = skip(); 
    if (c != EOF) { 
        if (c == '+') { 
            t->token = T_PLUS; 
        }
        else if (c == '-') { 
            t->token = T_MINUS; 
        }
        else if (c == '*') { 
            t->token = T_STAR; 
        }
        else if (c == '/') { 
            t->token = T_SLASH; 
        }
        else if (c >= 48 && c <= 57) { 
            t->token = T_NUMBER; 
            // we need to do some extra work to read potentially multidigit numbers
            t->intvalue = readInt(c);
        }
        else { 
            printf("Unrecognised character %c on line %d\n", c, Line);
            return 0; 
        }
        return 1; 
    }
    return 0; // we hit EOF 
}

// will return the total, multidigit integer  
// input: the number we start with 
// output: the final number 
static int readInt(int c) { 
    int final_value, current;

    current = c; 
    final_value = 0; 
    while (current < 48 || current > 57) {
        current -= 48; // to convert to an ACTUAL number value from ASCII 
        final_value = final_value * 10 + current; 
        current = next(); 
    } 

    putback(current); // want to put back whatever character it was that we went too far with
    return final_value; 
}