#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arena.h"
#include "maq.h"
#include "celula.h"
#include "printArena.h"


static void Erro(char *msg) {
  fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

/* Funções de coordenadas:
*Nessa fase do trabalho 2 tipos de coordenadas forma utilizados:
* - coordenadas "even-q vertical layout": possuem 2 eixos, i e j, equivalentes a
*matrizes bidimensionais. Utilizado para descrever a arena, incluindo a posição
*de todos os elementos contidos nela (robôs, bases, células, etc.);
* - coordenadas cúbicas: possuem 3 eixos, x, y e z, um para cada direção que se
*pode sair do hexágono. Sua somatória é sempre 0. Usado nas funções que usam
*localização relativa ao robô (mover, atacar, coletar cristais, depositar
                                                                    cristais)
* Nesse projeto, ambos os tipos de coordenadas estão representados como objetos,
* que possuem como atributos apenas os valores de cada eixo. Veja Coord.h*/

//transforma coordenadas cúbicas em coordenadas layout
Coord toCoord(CubeCoord cC){
    Coord c;
    c.j = cC.x;
    c.i = cC.z + (cC.x + (cC.x&1)) / 2;
    return c;
}

//transforma coordenadas layout em coordenadas cúbicas
CubeCoord toCube(Coord c){
    CubeCoord cC;
    cC.x = c.j;
    cC.z = c.i - (c.j + (c.j&1)) / 2;
    cC.y = -cC.x -cC.z;
    return cC;
}

/*verifica se a coordenada está dentro do limite da arena. Retorna 1 caso
                                                                    positivo*/
int limiteArena (Coord c){
    int i,j;
    i = c.i;
    j =c.j;
    if ((i < 0) || (i >= DIMMAX) || (j < 0) || (j >= DIMMAX))
        return 0;
    return 1;
}

/* dada uma coordenada c e uma direção d, retorna a coordenada da célula
* adjacente naquela direção*/
Coord somaCoord (Coord c, int d){
    Coord newCoord;
    CubeCoord tmp = toCube(c);
    switch (d) {
    case 0:
        tmp.x += 1;
        tmp.y -= 1;
        break;
    case 1:
        tmp.z -= 1;
        tmp.x += 1;
        break;
    case 2:
        tmp.y += 1;
        tmp.z -= 1;
        break;
    case 3:
        tmp.x -= 1;
        tmp.y += 1;
        break;
    case 4:
        tmp.z += 1;
        tmp.x -= 1;
        break;
    case 5:
        tmp.y -= 1;
        tmp.z += 1;
        break;
    }
    newCoord = toCoord(tmp);
    /*Verifica se o robô não está tentando sair/ atacar/ depositar/ recolher
    * fora da arena. Caso positivo, ele retorna a posição da entrada.
    * (no caso da função MOV, faz ele ficar parado)                          */
    if (limiteArena(newCoord))
	   return newCoord;
    return c;
}

int dist(Coord a, Coord b){
    CubeCoord cubeA,cubeB;
    cubeA = toCube(a);
    cubeB = toCube(b);
    return (abs(cubeA.x - cubeB.x) + abs(cubeA.y - cubeB.y) + abs(cubeA.z - cubeB.z)) / 2;
}

Arena* criaArena(int nJogadores) {
    Arena *a = (Arena*)malloc(sizeof(Arena));
    if (!a) Fatal("Memória insuficiente",4);
    int i, j;
    for (i = 0; i < DIMMAX; i++){
        for (j = 0; j < DIMMAX; j++){
            a->cel[i][j] = cria_celula();
        }
    }
    a->dim = DIMMAX;    //a arena começa com dimensão iagual a dimensão máxima,
 	a->nRobos = 0;      // e 0 robôs.
 	a->jAtiv = nJogadores;      // e 0 robôs.
    return a;
}

void preencheArena(Arena *a){
    insereTerreno(a);
    insereBases(a);
    //insereExercito(a);
    insereCristais(a); //falta verificar exercitos
}

void insereTerreno(Arena *a){
    int i, j, t;
    srand(time(NULL));
    for (i = 0; i < DIMMAX; i++){
        for (j = 0; j < DIMMAX; j++){
            t = rand() % 3 + 1;
            a->cel[i][j]->terreno = t;
        }
    }
}


void insereCristais(Arena *a){
    int k,b,c;
    Coord base,celula;
    srand(time(NULL));
    b = 0;
    c = 0;
            //int n = DIMMAX * DIMMAX / DENS;
    while (c < CRISTAISARENA){
        b = 0;
        celula.i = rand() % DIMMAX;
        celula.j = rand() % DIMMAX;

        for (k = 0; k < a->jAtiv; k++){

            base = a->bases[k];

                    //printf("dist = %d\n", dist(base,celula) );
            if (dist(base,celula) <= CRISTDIST){
                b = 1;
                break;
            }
        }

        if (b == 0) {
            printf("i,j = %d  %d\n", celula.i, celula.j );
            a->cel[celula.i][celula.j]->cristais += NCRISTAIS;
            c += 1;
            printf("c = %d\n", c );
        }
    }
}
void insereBases(Arena *a){
    int k,b,bases;
    Coord base,novaBase,centro;
    srand(time(NULL));
    b = 0; //1 se a celula estiver perto demais de uma base
    bases = 0; //bases já alocadas
            //int n = DIMMAX * DIMMAX / DENS;
    centro.i = DIMMAX/2;
    centro.j = DIMMAX/2;
    while (bases < a->jAtiv-1){
        b = 0;
        novaBase.i = rand() % DIMMAX;
        novaBase.j = rand() % DIMMAX;
        //printf("dist = %d\n", dist(base,celula) );

        for (k = 0; k < bases; k++){

            base = a->bases[k];

            if (dist(base,novaBase) <= 4){
                b = 1;
                break;
            }
        }

        if (dist(novaBase,centro) <= 4){
            b = 1;
            continue;
        }



        if (b == 0) {
            a->bases[bases] = novaBase;
            a->cel[novaBase.i][novaBase.j]->base = bases;
            bases++;
        }
    }
}

void carregaArena(Arena *a,char *terreno[][11]){
    int l = 11;     //estamos usando 11 como tamanho fixo da arena
    int i,j;
    int ex = 0;
    for (i = 0; i < l; i++){
        for (j = 0; j < l; j++){
            if (*terreno[i][j] == 66){  // compara se terreno[i][j] == "B".
                Coord c = {i,j};        // cria uma base na coordenada c
                a->bases[ex] = c;       // caso afirmativo.
                a->cel[i][j]->base = ex;
                a->jAtiv++;             //numero de jogadores é especificado
                ex++;                   //pelo numero de bases na arena
                //posteriormente realiazaremos a inserções dos exercitos nesta
                //função.
            }

            if (*terreno[i][j] == 67)   // compara se terreno[i][j] == "B".
                a->cel[i][j]->cristais = 9;  // cria 9 cristais na coordenada c
        }                                    // caso afirmativo
    }
}

//libera o espaço da arena e das estruturas que ela aponta (Maquinas e celulas)
void destroi_arena(Arena *a) {
    int i;
    int j;
    for (i = 0;i < a->nRobos/TAMEXER;i++){
		removeExercito(a,i);
	}
  	for (i = 0; i < DIMMAX; i++){
      	for (j = 0; j < DIMMAX; j++)
    		destroi_celula(a->cel[i][j]);
  	}
  free(a);
}


void  insereExercito(Arena *a, INSTR *p, int lP){
    int i;
    /* Cria todos os robôs de um determinado exército, carregando-os com o
    * programa p de comprimento lP.
    * Para cada robô criado o vetor ativ[] indexado por nM, é atualizado para 1,
    *  indicando que o robo está ativo.                                       */
    for (i = 0; i < 1;i++){
        a->robos[a->nRobos] = cria_maquinaArena(p, a->nRobos ,lP ,a);
        a->ativ[a->nRobos] = 1;
        a->nRobos += 1;
    }
    a->jAtiv++;
}

/*verifica se a base localizada na posição x, y possui 5 ou mais cristais
* em caso positivo, remove o exército dono dessa base.                     */
void checarCristaisBase(Arena *a, int x, int y){
	if (a->cel[x][y]->cristais >= 5){
		int ex, nEx;
		nEx = a->jAtiv;
		for (ex = 0; ex < nEx + 1; ex++){
            if((a->bases[ex].i == x) && (a->bases[ex].j == y))
				removeExercito(a, ex);
		}
	}
}

//Move o robô m para a direção dir.
void mover(Arena *a, int m, int dir){
	Coord coord = a->cord[m];
	Coord newCoord = somaCoord(coord,dir);
	int x0 = coord.i;
	int y0 = coord.j;
	int x1 = newCoord.i;
	int y1 = newCoord.j;
	a->cel[x0][y0]->ocupacao = -1; //indica que a célula de partida está vazia
	a->cel[x1][y1]->ocupacao = m;  //indica que a célula de destino contém o
                                                                        //robô m
	a->cord[m].i = x1; //atualiza o vetor cord[] da arena, que contém as
	a->cord[m].j = y1; // posições de todos os robôs.
}

//Faz com que o robô m ataque o robô na direção dir
//Funciona de modo similar ao MOV
void atacar(Arena *a, int m, int dir){
	Coord coord = a->cord[m];
	Coord newCoord = somaCoord(coord,dir);
	int x0 = coord.i;
	int y0 = coord.j;
	int x1 = newCoord.i;
	int y1 = newCoord.j;
	int m2 = a->cel[x1][y1]->ocupacao;
	Maquina *alvo = a->robos[m2];
	destroi_maquina(alvo);
	a->ativ[m2] = 0;
	mover(a,m,dir);
}


//Faz com que o robô m deposite 1 cristal na base na direção dir
//Funciona de modo similar ao MOV
//Por enquanto ele pode depositar em qualquer lugar, não precisa ser base.
void depositar(Arena *a, int m, int dir){
	Coord coord = a->cord[m];
	Coord newCoord = somaCoord(coord,dir);
	int x0 = coord.i;
	int y0 = coord.j;
	int x1 = newCoord.i;
	int y1 = newCoord.j;
    if (a->robos[m]->cristal > 0){
        a->robos[m]->cristal -= 1;
        a->cel[x1][y1]->cristais += 1;
    }

	checarCristaisBase(a,x1,y1); //checa se a base foi destruida
}


//Faz com que o robô m recolha 1 cristal da celula na direção dir
//Funciona de modo similar ao MOV
void recolher(Arena *a, int m, int dir){
	Coord coord = a->cord[m];
	Coord newCoord = somaCoord(coord,dir);
	int x0 = coord.i;
	int y0 = coord.j;
	int x1 = newCoord.i;
	int y1 = newCoord.j;
    if (a->cel[x1][y1]->cristais > 0){
	   a->cel[x1][y1]->cristais -= 1;
	   a->robos[m]->cristal += 1;
    }
}

/*Acessa o topo de uma pilha de dados de uma maquina, verifica a chamada lá
*  eempilhada e realiza, na arena, a ação pretendida pelo robô                */
void resolve_chamadas(Maquina *m, Arena *a){

    OPERANDO chSys = desempilha(&m->pil);
    int dir = chSys.n;     //acessa o argumento da instrução empilhada
	OpCode ch = chSys.ac;   //acessa o OpCode da instrução empilhada
	int mm = m->nMaq;       //acessa o número da máquina que está tendo a sua
                            //chamada resolvida.

	    switch (ch) {

	      	case MOV:
	        	mover(a,mm,dir);
	      		break;
	      	case ATAC:
	        	atacar(a,mm,dir);
	        	break;
	      	case REC:
	        	recolher(a,mm,dir);
	        	break;
	    	case DEP:
	        	depositar(a,mm,dir);
	        	break;
		}
    //"No retorno, o resultado se encontrará no topo da pilha."
    //"por enquanto retorna sempre 1."
    OPERANDO resultado;
    resultado.n = 1;
    resultado.t = NUM;
    resultado.ac = 0;
    resultado.c = NULL;
    empilha(&m->pil, resultado);
    empilha(&m->pil, resultado);
    OPERANDO o = desempilha(&m->pil);
}

/*A cada rodada, permite que cada máquina execute um certo número de operações
* (50). Depois, quando houver, resolve as chamadas de sistema de cada máquina.*/
void atualiza(Arena *a,int rodadas){
    int i,j;
    for (j = 0; j < rodadas; j++){
	    for (i = 0; i < a->nRobos; i++){
            if(a->ativ[i] == 1) //verifica se o robô está ativo
		          exec_maquina(a->robos[i], 250);
        }
        for (i = 0; i < a->nRobos; i++){
            if(a->ativ[i] == 1){ //verifica se o robô está ativo
                /*verifica se de fato há uma chamada de sistema na pilha,
                * i. e. comandos entre REC e MOV*/
                OPERANDO tmp = desempilha(&a->robos[i]->pil);
                empilha(&a->robos[i]->pil,tmp);
                if ((tmp.ac >= REC) && (tmp.ac <= MOV))
                    resolve_chamadas(a->robos[i], a);
            }
        }
        waitFor(1);
        printArena(a);
    }
}

void removeExercito(Arena *a,int ex){
    int i;
    for (i = 0; i< TAMEXER;i++)
        a->ativ[ex * TAMEXER + i] = 0; //seta a ativ[] de todos os robôs do exército
                                // como 0 (inativos).
    printf("O exercito %d foi removido do jogo\n", ex);
}


void sistema(int ip, Maquina *m){
    /*"eventuais operandos estão colocados na pilha de dados"
    * A pilha de dados só aceita OPERANDO, então temos que converter
    * um INSTR para um OPERANDO*/

    OPERANDO chSys; //OPERANDO da chamada de sistema
    chSys.t  = NUM;
    //manda o n do OPERANDO (aka argumento) da INSTR para o n do OPERANDO da
    //chamada de sistema
    chSys.n  = m->prog[ip].op.n;
    //manda o OpCode da INSTR para o OpCode do OPERANDO
    chSys.ac = m->prog[ip].instr;
    // nessas chamadas de sistema, o atributo da célula não é utilizado
    chSys.c  = NULL;

    empilha(&m->pil, chSys);      //finalmente empilha o OPERANDO chSys
}
