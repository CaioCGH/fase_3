#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

static void Erro(char *msg) {
  fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Pilha *cria_pilha() {
  Pilha *p = (Pilha*)malloc(sizeof(Pilha));
  if (!p) Fatal("Memória insuficiente",4);
  p->topo = 0;
  p->base = 0;
  return p;
}

void destroi_pilha(Pilha *p) {
  free(p);
}
/*Como a estrutura da struct de OPERANDO foi modificada, a função empilha também
* teve que ser adaptada para essa nova estrutura. Agora ela empilha o n
* (argumento numérico), t (tipo), ac (OpCode), e c (célula) do operando a ser
* empilhado.*/
void empilha(Pilha *p, OPERANDO op) {
  if (p->topo < PILMAX){
    p->val[p->topo].n = op.n;
	p->val[p->topo].t = op.t;
    p->val[p->topo].ac = op.ac;
    p->val[p->topo++].c = op.c;
  }
  else Erro("Pilha cheia");
}

OPERANDO desempilha(Pilha *p) {
  OPERANDO tmp;
  if (p->topo > 0)
  return p->val[--p->topo];
  else{
      return tmp;
      Erro("Pilha vazia");
    }
}

/*Assim como a função empilha(), imprime() também foi adaptada para imprimir os
* 4 atributos do OPERANDO.                                                    */
void imprime(Pilha *p, int n) {
  int t = p->topo-1;
  int i;
  printf("[");
  for (i = t; i >= 0 && i > p->topo-n; i--){
      printf("{%d, ", p->val[i].n);
      printf("%d, ",p->val[i].t);
	printf("%d, ",p->val[i].ac);
	printf("%d}, ",p->val[i].c);
  }
  printf("]");
  return;
}
