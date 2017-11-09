#include "typedefs.h"
/* Códigos das instruções */
enum OpCode{
  PUSH,//n
  RET,//n
  RCL,//n
  END,//n
  RCE, //n
  FREE, //n
  ALLOC, //n
  JMP,//n
  REC,//n
  DEP,//n
  ATAC,//n
  MOV, //n
  POP,//o
  DUP,//o
  STO,//o
  STL, //o
  JIT,//1
  JIF,//1
  CALL,//1
  PRN,//1
  TOP,//1
  SAVE,//1
  REST,//1
  ADD,//2
  SUB,//2
  MUL,//2
  DIV,//2
  EQ, //2
  GT,//2
  GE,//2
  LT,//2
  LE,//2
  NE,//2
  PCEL, //2
  ATR //c
};

/* Tipos dos operandos */
/* no momento, são todos inteiros */
enum Tipo{
  NUM,
  ACAO,
  VAR,
  CEL
};

/* Operando */
 struct OPERANDO {
  int n;
  Tipo t;
  OpCode ac;
  Celula *c;
};
// typedef int OPERANDO;



/* Instrução */
struct INSTR {
  OpCode instr;
  OPERANDO op;
};
