#include "Tree.h"
#include "../SimpleLexer/SimpleLexer.h"

int tokenToAST(int tok); 

static struct ASTnode *primary(void); 

struct ASTnode *binexpr(void); 

int evaluateTree(struct ASTnode * node); 