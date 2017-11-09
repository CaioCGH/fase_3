#include "instr.h"
#include "typedefs.h"

#define PILMAX 99

struct Pilha{
  int topo;
  int base;
  OPERANDO val[PILMAX+1];
};

Pilha *cria_pilha();
void destroi_pilha(Pilha *p);
void empilha(Pilha *p, OPERANDO op);
OPERANDO desempilha(Pilha *p);
void imprime(Pilha *p, int n);
