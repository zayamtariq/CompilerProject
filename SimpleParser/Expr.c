// naive expression parser (no notion of precedence, for now)
#include <stdio.h> 
#include "../SimpleLexer/Token.h"
#include "AST.h" 
#include "../SimpleLexer/Data.h" 
#include "Tree.h"
#include "../SimpleLexer/SimpleLexer.h"
#include "Expr.h"

// function that converts tokens into AST operations (arbitrary for now)
int tokenToAST(int tok) { 
    switch(tok) { 
        case T_PLUS: 
            return A_ADD; 
        case T_MINUS: 
            return A_SUBTRACT; 
        case T_STAR: 
            return A_MULTIPLY; 
        case T_SLASH: 
            return A_DIVIDE; 
        default: 
            printf("unknown token"); 
            return -1; 
    }
}

// we also need a function to hold a number and create an AST node to hold that value 
// (these must be treated differently than how we treat operations, in terms of how we populate things)
static struct ASTnode *primary(void) { 
    struct ASTnode *n; 

    // we will: 
    // 1. make leaf ast node for our number 
    // 2. scan next token for our global variable to hold the latest scanned token 
    if (Token.token == T_NUMBER) { 
        n = makeASTLeaf(A_NUMBER, Token.intvalue); 
        scan(&Token); 
        return n; 
    }
    else { 
        printf("syntax error on line "); // need to integrate lines for the whole system, make global  
    }
}

// returns the AST tree's root, which should be a binary operator 
// (this is our simple, naive parser)
struct ASTnode *binexpr(void) { 
    // TO DO
    struct ASTnode * root; 
    struct ASTnode * left; 
    struct ASTnode * right; 
    int operation; 

    left = primary(); 

    if (Token.token == T_EOF) { 
        // our base case. no more tokens to read in. 
        return left; 
    }

    operation = tokenToAST(Token.token); // this is the new token that was scanned in via primary 

    // ok now we have two options to populate the right node: 
    // 1. if there's nothing after the number, then right node just equals number (base case) 
    // 2. if there IS something after the number, then recurse 
    right = binexpr(); 

    return makeASTNode(operation, left, right, NULL); 
}

int evaluateTree(struct ASTnode * node) { 
    int left; 
    int right;

    if (node->left) { // will keep on recursing until we hit a number 
        left = evaluateTree(node->left); 
    } 
    if (node->right) { 
        right = evaluateTree(node->right); 
    }

    switch(node->operation) { 
        case A_ADD: 
            return left + right; 
        case A_SUBTRACT: 
            return left - right; 
        case A_MULTIPLY: 
            return left * right; 
        case A_DIVIDE: 
            return left / right; 
        case A_NUMBER:
            return node->intvalue; 
        default: 
            printf("Unknown operator"); 
            return -1; 
    }
}