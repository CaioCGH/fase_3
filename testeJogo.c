#include <stdio.h>
#include "arena.h"
#include "maq.h"
#include "celula.h"
#include "printArena.h"
char *terreno[11][11] = {
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
{ "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", "*", },
};

INSTR prog[] = {












  {MOV, {0, NUM } },
  {MOV, {0, NUM } },
  {MOV, {5, NUM } },
  {MOV, {0, NUM } },
  {MOV, {0, NUM } },
  {MOV, {5, NUM } },
  {PUSH, {5, NUM } },
  {PUSH, {4, NUM } },
  {PCEL, {5, NUM } },
  {ATR, {0, NUM } },
  {PRN, {0, NUM } },
  {PUSH, {10, NUM } },
  {PUSH, {10, NUM } },
  {PCEL, {0, NUM } },
  {ATR, {2, NUM } },
  {PRN, {0, NUM } },
  {PUSH, {4, NUM } },
  {PUSH, {4, NUM } },
  {PCEL, {0, NUM } },
  {ATR, {3, NUM } },
  {PRN, {0, NUM } },
  {REC, {5, NUM } },
  {REC, {5, NUM } },
  {REC, {5, NUM } },
  {REC, {5, NUM } },
  {REC, {5, NUM } },
  {MOV, {0, NUM } },
  {MOV, {0, NUM } },
  {MOV, {5, NUM } },
  {MOV, {0, NUM } },
  {MOV, {0, NUM } },
  {MOV, {5, NUM } },
  {MOV, {0, NUM } },
  {MOV, {0, NUM } },
  {DEP, {5, NUM } },
  {DEP, {5, NUM } },
  {DEP, {5, NUM } },
  {DEP, {5, NUM } },
  {DEP, {5, NUM } },
  {MOV, {4, NUM } },
  {MOV, {3, NUM } },
  {MOV, {2, NUM } },
  {MOV, {1, NUM } },
  {END, {0, NUM } },
};

int main(int ac, char **av) {
  Arena *a = criaArena(4);
  carregaArena(a,terreno);
  insereExercito(a,prog,44);
  preencheArena(a);
  atualiza(a,27);
  printArena(a);
  destroi_arena(a);
  return 0;
}
