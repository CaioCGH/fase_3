#include "pilha.h"
//#include "Coord.h"
//#include "instr.h"

#define MAXMEM 100


struct Maquina{
  int lenProg;
  int exer;
  int nMaq;
  Coord pos;
  int cristal;
  Arena *arena;

  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  int rcb;
  int ip;
  INSTR *prog;
};


Maquina *cria_maquina(INSTR *p,int lP);

Maquina *cria_maquinaArena(INSTR *p,int nM, int lP,  Arena *a);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);
