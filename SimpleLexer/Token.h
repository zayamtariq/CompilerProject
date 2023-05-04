// struct for a simple token 
struct Token { 
    int token; // is it a +, -, /, *, or a number 
    int intvalue; // the integer value that was scanned in 
}; 

// types of tokens we can store 
enum { 
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_NUMBER 
}; 