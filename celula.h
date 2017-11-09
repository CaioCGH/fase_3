#include "typedefs.h"

struct Celula {
    int cristais;
    int terreno;
    int base;
	int ocupacao;
};

Celula *cria_celula();
void destroi_celula(Celula *c);
void atualiza_cristais(Celula *c,int crist);
void atualiza_ocupacao(Celula *c, int m);
void atualiza_base(Celula *c, int ex);
void imprimeCelula(Celula *c);