#include "Generator.h" 

// we're assuming we have four registers to work with/manipulate 
static int freereg[4]; // 1 if free, 0 if full 
static char *reglist[4]= { "%r8", "%r9", "%r10", "%r11" };

// frees all registers in our register list 
void freeall_registers() { 
    freereg[0] = 1; 
    freereg[1] = 1; 
    freereg[2] = 1; 
    freereg[3] = 1; 
}

// allocate a free register 
int alloc_register() { 
    for (int i=0; i < 4; i++) {
        if (freereg[i]) {
            freereg[i]= 0;
            return(i);
        }
    }
    printf("Out of registers!\n");
    return -1; 
}

// free an allocated register 
void free_register(int register_number) { 
    freereg[register_number] = 1; 
}

// Print out the assembly preamble
void codeGeneratorPreamble()
{
  freeall_registers();
  printf(
	"\t.text\n"
	".LC0:\n"
	"\t.string\t\"%d\\n\"\n"
	"printint:\n"
	"\tpushq\t%rbp\n"
	"\tmovq\t%rsp, %rbp\n"
	"\tsubq\t$16, %rsp\n"
	"\tmovl\t%edi, -4(%rbp)\n"
	"\tmovl\t-4(%rbp), %eax\n"
	"\tmovl\t%eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"\t.globl\tmain\n"
	"\t.type\tmain, @function\n"
	"main:\n"
	"\tpushq\t%rbp\n"
	"\tmovq	%rsp, %rbp\n");
}

// Print out the assembly postamble
void codeGeneratorPostamble()
{
  printf(
	"\tmovl	$0, %eax\n"
	"\tpopq	%rbp\n"
	"\tret\n");
}

int codeGeneratorLoadReg(int reg_value) { 
  // Get a new register
  int r= alloc_register();

  // Print out the code to initialise it
  printf("\tmovq\t$%d, %s\n", reg_value, reglist[r]);
  return(r);
}

int codeGeneratorAdd(int r1, int r2) { 
  printf("\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
  free_register(r1);
  return(r2);
}

int codeGeneratorSubtract(int r1, int r2) { 
  printf("\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
  free_register(r2);
  return(r1);
}

int codeGeneratorMultiply(int r1, int r2) { 
  printf("\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
  free_register(r1);
  return(r2);
}

int codeGeneratorDivide(int r1, int r2) { 
  printf("\tmovq\t%s,%%rax\n", reglist[r1]);
  printf("\tcqo\n");
  printf("\tidivq\t%s\n", reglist[r2]);
  printf("\tmovq\t%%rax,%s\n", reglist[r1]);
  free_register(r2);
  return(r1);
}

void codeGeneratorPrintInt(int r) {
  printf("\tmovq\t%s, %%rdi\n", reglist[r]);
  printf("\tcall\tprintint\n");
  free_register(r);
}

// will return the evaluated expression
// in the process, will produce assembly expressions 
static int genAST(struct ASTnode *n) { 
    int left, right; 

    if (n->left) { 
        left = genAST(n->left); 
    }
    if (n->right) { 
        right = genAST(n->right); 
    }

    // once we've gotten to this point, we're at our operation (or our lone integer)
    switch(n->operation) { 
        case (A_ADD): return (codeGeneratorAdd(left, right)); 
        case (A_SUBTRACT): return (codeGeneratorSubtract(left, right)); 
        case (A_MULTIPLY): return (codeGeneratorMultiply(left, right)); 
        case (A_DIVIDE): return (codeGeneratorDivide(left, right)); 
        case (A_NUMBER): return (codeGeneratorLoadReg(n->intvalue)); 
    }
}

// need something to output the 
// preamble, result of our expression, and postamble 
void generateCode(struct ASTnode *n) { 
  int reg;

  codeGeneratorPreamble();
  reg = genAST(n);
  codeGeneratorPrintInt(reg);      // Print the register with the result as an int
  codeGeneratorPostamble();
}
