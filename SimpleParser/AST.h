// file will help define the structure of our nodes in the AST for our simple parser 
#include <stdio.h> 

// AST node types 
enum { 
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_NUMBER 
}; 

// an abstract syntax tree is just that, a tree we have to traverse 
struct ASTnode { 
    int operation; // the operation that will be performed on the tree (if not a number)
    struct ASTnode *left; 
    struct ASTnode *right; 
    int intvalue; // if token is a number 
}; 