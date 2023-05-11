
struct ASTnode * makeASTNode(int operation, struct ASTnode *left, struct ASTnode *right, int intvalue); 

struct ASTnode * makeASTLeaf(int operation, int intvalue); 

struct ASTnode * makeUnaryASTNode(int operation, struct ASTnode * left, int intvalue); 