#include <stdio.h>
#include "Tree.h"

// we want to build ast nodes and trees 

// lets populate a node given a call
struct ASTnode * makeASTNode(int operation, struct ASTnode *left, struct ASTnode *right, int intvalue) { 
    struct ASTnode * toReturn; 

    toReturn->operation = operation; 
    toReturn->left = left; 
    toReturn->right = right; 
    toReturn->intvalue = intvalue; 

    return toReturn; 
}

// make a leaf node, using the above function 
struct ASTnode * makeASTLeaf(int operation, int intvalue) { 
    return makeASTNode(operation, NULL, NULL, intvalue); 
}

// make a unary node (one child only)
struct ASTnode * makeUnaryASTNode(int operation, struct ASTnode * left, int intvalue) { 
    return makeASTNode(operation, left, NULL, intvalue); 
}