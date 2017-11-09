#include <stdio.h>
#include <stdlib.h>
#include "celula.h"

static void Erro(char *msg) {
  fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

/* Cria uma célula default
* As células default tem seus argumentos:
* - terreno: indica o tipo do terreno, que pode implicar em maior ou menor custo
* de rodadas para o robô transpô-lo. Por default é 1, que indica terreno plano,
* cujo custo é 1;
* - cristais: quantidade de cristais na célula. Por default é 0;
* - ocupacao: indica se a celula esta sendo ocupada por um robô e, caso esteja,
* qual robô exatamente. Por default é -1, que indica célula vazia. Os números a
* partir de 0 indicam o nM do robô, dando sua identidade na arena e exército a
* qual pertencem. Ver maq.c função cria_máquina;
* - base: análogo à ocupação, entretanto, ao invés de indicar a presença de um
* robô, indica a presença e identidade de uma base.                           */
Celula *cria_celula() {
  Celula *c = (Celula*)malloc(sizeof(Celula));
  if (!c) Fatal("Memória insuficiente",4);
  c->terreno = 1;
  c->cristais = 0;
  c->ocupacao = -1;
  c->base = -1;

  return c;
}

void destroi_celula(Celula *c) {
  free(c);
}

void atualiza_cristais(Celula *c, int crist) {
    c->cristais = crist;
}

void atualiza_ocupacao(Celula *c, int m) {
    c->ocupacao = m;
}

void atualiza_base(Celula *c, int ex) {
    c->base = ex;
}

void imprimeCelula(Celula *c) {
  return;
}
