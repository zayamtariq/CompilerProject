#include "../SimpleParser/Expr.h"
 
void codeGeneratorPreamble(); 

void codeGeneratorPostamble(); 

int codeGeneratorLoadReg(int reg_value);

int codeGeneratorAdd(int r1, int r2);

int codeGeneratorSubtract(int r1, int r2); 

int codeGeneratorMultiply(int r1, int r2);

int codeGeneratorDivide(int r1, int r2); 

void codeGeneratorPrintInt(int r); 

// set all registers as available 
void freeall_registers(); 

// allocate a free register 
int alloc_register(); 

// free an allocated register 
void free_register(int register_number); 

// given an AST, generate assembly code recursively 
static int genAST(struct ASTnode *n); 

// need something to output the 
// preamble, result of our expression, and postamble 
void generateCode(struct ASTnode *n); 

