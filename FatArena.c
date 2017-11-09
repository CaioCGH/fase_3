#include <stdio.h>
#include "arena.h"
#include "maq.h"
#include "celula.h"
#include "printArena.h"
char *terreno[11][11] = {
{ "B", "*", "*", "*", "*", "*", "*", "*", "B", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "C", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "C", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "B", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "B", },
};

INSTR prog[] = {
  {PUSH, {8, NUM } },
  {PUSH, {0, NUM } },
  {SAVE, {0, NUM } },
  {PUSH, {0, NUM } },
  {CALL, {9, NUM } },
  {PRN, {0, NUM } },
  {MOV, {0, NUM } },
  {POP, {0, NUM } },
  {JMP, {0, NUM } },
  {ALLOC, {2, NUM } },
  {PUSH, {1, NUM } },
  {ADD, {0, NUM } },
  {STL, {1, NUM } },
  {DUP, {0, NUM } },
  {STL, {2, NUM } },
  {PUSH, {1, NUM } },
  {EQ, {0, NUM } },
  {JIF, {25, NUM } },
  {PUSH, {1, NUM } },
  {RCE, {1, NUM } },
  {PUSH, {1, NUM } },
  {SUB, {0, NUM } },
  {REST, {0, NUM } },
  {FREE, {2, NUM } },
  {RET, {0, NUM } },
  {RCE, {2, NUM } },
  {PUSH, {1, NUM } },
  {SUB, {0, NUM } },
  {RCE, {1, NUM } },
  {SAVE, {0, NUM } },
  {RCE, {1, NUM } },
  {CALL, {9, NUM } },
  {RCE, {2, NUM } },
  {MUL, {0, NUM } },
  {RCE, {1, NUM } },
  {PUSH, {1, NUM } },
  {SUB, {0, NUM } },
  {REST, {0, NUM } },
  {FREE, {2, NUM } },
  {RET, {0, NUM } },
};

int main(int ac, char **av) {
  Arena *a = criaArena(4);
  carregaArena(a,terreno);
  insereExercito(a,prog,40);
  atualiza(a,27);
  printArena(a);
  destroi_arena(a);
  return 0;
}
