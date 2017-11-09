#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "celula.h"
#include "maq.h"

//#define DEBUG

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
    "PUSH",
    "RET",
    "RCL",
    "END",
    "RCE",
    "FREE",
    "ALLOC",
    "JMP",
    "REC",
    "DEP",
    "ATAC",
    "MOV",
    "POP",
    "DUP",
    "STO",
    "STL",
    "JIT",
    "JIF",
    "CALL",
    "PRN",
    "TOP",
    "SAVE",
    "REST",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "EQ",
    "GT",
    "GE",
    "LT",
    "LE",
    "NE",
    "PCEL",
    "ATR"
};
#else
#  define D(X)
#endif

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

/*funcao para teste que permite
criar maquina sem antes criar a arena*/
Maquina *cria_maquina(INSTR *p,int lP) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;
  m->lenProg = lP;
  m->prog = p;
  m->rcb = 0;
  m->cristal = 0;
  return m;
}

/*cria a maquina virtual (robô) já dentro da arena declarada
* INSTR *p: vetor com as intruções que a máquina irá realizar;
* int nM: número da máquina: inteiro identidade da máquina. cada máquina terá um
* diferente e o sistema identificará cada máquina por esse número. Também
* indica o exército a qual a máquina pertence;
* int lP: length Program, o número de linhas que o programa carregado na máquina
*                                                                        possui;
* Arena *a: Arena na qual a máquina está sendo criada.                        */
Maquina *cria_maquinaArena(INSTR *p, int nM, int lP, Arena *a) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;           //as máquinas começam com a intrução 0
  m->lenProg = lP;
  m->prog = p;
  m->rcb = 0;

  /*Além do nM que é a identidade da máquina na arena, as máquinas possuem
  * identidades internas:
  * exer: inteiro que indica o número do exército que a máquina pertence
  * nMaq: inteiro que identifica a máquina dentro de seu exército
  * Essas atrubuições funcionam porque cada exército terá 5 (definido por TAMEXER)
  *robôs. Dessa maneira, o as máquinas nM com de 0 a 4 estarão atribuídas ao exército 0, as de nM de
  * 5 a 9 ao exército 1, e assim por diante. Entretanto, do ponto de vita de cada
  * exército, sempre estarão disponíveis 5 máquinas com nMaq de 0 a 4.          */
  m->exer = nM / TAMEXER;
  m->nMaq = nM % TAMEXER;
  m->cristal = 0;
  m->arena = a;
  Coord pos = a->bases[nM/TAMEXER]; //os robôs começam na célula
  m->pos = pos;               //da base de seus exércitos

  /*Atualização da arena
  * A cada robô criado a arena também é imediatamente informada através
  * dos seguintes atributos:
  * - cel[i][j]: o atributo ocupacao da célula[i][j] recebe o nM da máquina
  * criada assim a arena sabe exatamente qual robô está nesta célula.
  *                                                               Veja celula.c;
  * - cord[nM]: a arena também possui o vetor cord[], indexado por nM,  que
  *  contém todas as posições de todos os robôs da arena;
  * - ativ[nM]: a arena também possui um vetor ativ[], inexador por nM, que
  * contém o estado de atividade de todos os robôs da arena.                  */
  a->cel[pos.i][pos.j]->ocupacao = nM;
  a->cord[nM].i = pos.i;
  a->cord[nM].j = pos.j;
  a->ativ[nM] = 1;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)
#define rcb (m->rcb)
#define arena (m->arena)


/*Conforme o enunciado da fase dois, estamos verificando
* o tipo de operando no topo da pilha de dados. Para tal
* agrupamos as instrucoes conforme os quantidade e tipos de
* operando que elas usam.
* Para cada grupo de instrucoes há um if que verifica se
* o topo da pilha tem o tipo necessario para aquele grupo */
void exec_maquina(Maquina *m, int n) {
  int k;
  Celula *celula;

  for (k = 0; k < n; k++) {
	OpCode   opc = prg[ip].instr;
	OPERANDO arg = prg[ip].op;


	OPERANDO tmp;
    int i,j;

    //instruções que nao usam topo da pilha
    if ((PUSH <= opc) && (opc <= MOV)){
        switch (opc) {
        case PUSH:
    	  empilha(pil, arg);
    	  break;
        case RET:
		  	ip = desempilha(exec).n;
		  	break;
        case RCL:
          	empilha(pil,m->Mem[arg.n]);
          	break;
        case END:
    	  	return;
        case RCE:
            empilha(pil,exec->val[arg.n + rcb]);
            break;

        case ALLOC:
            exec->topo += arg.n;
            for (j = rcb + 1;j <= rcb + arg.n; j++){
                exec->val[j].t = arg.t;
                exec->val[j].n = 0;
            }
            break;
        case FREE:
            exec->topo -= arg.n;
            break;
        case JMP:
            ip = arg.n;
            continue;

        //instruções especiais: chamadas de sistema tem que ser empilhadas
        //na pilha de dados e tratadas de uma maneira diferente das demais intr
        case MOV:
            sistema(ip, m);
            k=n;
            break;
        case REC:
            k=n;
            sistema(ip, m);
            break;
        case DEP:
            sistema(ip, m);
            k=n;
            break;
        case ATAC:
            sistema(ip, m);
            k=n;
            break;
        }
    }

    //instrs que usam OPERANDO de qualquer
    // tipo no topo da pilha
    if ((POP <= opc) && (opc <= STL)){
        if (pil->topo > 0){
            switch (opc){
                case POP:
                    desempilha(pil);
                    break;
                case DUP:
                    tmp = desempilha(pil);
                    empilha(pil, tmp);
                    empilha(pil, tmp);
                    break;
                case STO:
                    m->Mem[arg.n] = desempilha(pil);
                    break;
                case STL:
                    exec->val[arg.n + rcb] = desempilha(pil);
                    break;
            }
        }
        else printf("piLha vazia. O topo deve ser OPERANDO de qualquer tipo\n");
    }

    //instrs que usam NUM no topo da pilha
    if ((JIT <= opc) && (opc <= REST)){
        if (pil->topo > 0){
            if(pil->val[pil->topo - 1].t == NUM){
                switch (opc){
        	    case TOP:
        	        exec-> topo = desempilha(pil).n;
        	        break;
        		case JIT:
        		  	if (desempilha(pil).n != 0) {
        				ip = arg.n;
        				continue;
        			  }
        		  	break;
        		case JIF:
        		  	if (desempilha(pil).n == 0) {
        				ip = arg.n;
        				continue;
        			  }
        		  break;
        		case CALL:
        			tmp.t =NUM;
        			tmp.n = ip;
        	      	rcb = exec->topo;
        			empilha(exec, tmp);
        			ip = arg.n;
        		  continue;
        	    case SAVE:
        	        tmp = desempilha(pil);
        	        m->Mem[tmp.n].t = NUM;
        	        m->Mem[tmp.n].n = rcb;
        	        break;
        	    case REST:
        	        rcb = m->Mem[desempilha(pil).n].n;
        	        break;
        	    case PRN:
        		  	printf("%d\n", desempilha(pil).n);
        		  	break;
                }
            }
            else printf("topo deve ser tipo NUM\n" );
        }
        else printf("piLha vazia. O topo deve ser NUM\n");
    }

    //instrs que usam dois NUMs no topo da pilha
    //PCEL  ADD  SUB  MUL  DIV  EQ  GT  GE  LT  LE  NE
    if ((ADD <= opc) && (opc <= PCEL)){
        if (pil->topo > 1){
            if(pil->val[pil->topo - 1].t == NUM
                && pil->val[pil->topo - 2].t == NUM){
                switch (opc) {
                case PCEL:
                    j = desempilha(pil).n;
                    i = desempilha(pil).n;
                    tmp.t = CEL;
                    tmp.n = 0;  //n importa
                    tmp.ac = 0; //n importa
                    tmp.c = arena->cel[i][j];
                    empilha(pil,tmp);
                    break;
                case ADD:
                    tmp.t =NUM;
                    tmp.n = desempilha(pil).n + desempilha(pil).n;
                    empilha(pil, tmp);
                    break;
                case SUB:
                    tmp = desempilha(pil);
                    tmp.n =  desempilha(pil).n-tmp.n;
                    empilha(pil,tmp);
                    break;
                case MUL:
                    tmp.t =NUM;
                    tmp.n = desempilha(pil).n*desempilha(pil).n;
                    empilha(pil,tmp);
                    break;
                case DIV:
                    tmp = desempilha(pil);
                    tmp.n = desempilha(pil).n/tmp.n;
                    empilha(pil, tmp);
                    break;
                case EQ:
                    tmp.t = NUM;
                    if (desempilha(pil).n == desempilha(pil).n)
                        tmp.n = 1;
                    else
                        tmp.n = 0;
                    empilha(pil, tmp);
                    break;
                case GT:
                    tmp.t = NUM;
                    if (desempilha(pil).n < desempilha(pil).n)
                        tmp.n = 1;
                    else
                        tmp.n = 0;
                    empilha(pil, tmp);
                    break;
                case GE:
                    tmp.t = NUM;
                    if (desempilha(pil).n <= desempilha(pil).n)
                        tmp.n = 1;
                    else
                        tmp.n = 0;
                    empilha(pil, tmp);
                      break;
                case LT:
                    tmp.t = NUM;
                    if (desempilha(pil).n > desempilha(pil).n)
                        tmp.n = 1;
                    else
                        tmp.n = 0;
                    empilha(pil, tmp);
                      break;
                case LE:
                    tmp.t = NUM;
                    if (desempilha(pil).n >= desempilha(pil).n)
                        tmp.n = 1;
                    else
                        tmp.n = 0;
                    empilha(pil, tmp);
                    break;
                case NE:
                    tmp.t = NUM;
                    if (desempilha(pil).n != desempilha(pil).n)
                        tmp.n = 1;
                    else
                        tmp.n = 0;
                    empilha(pil, tmp);
                    break;
                }
            }
            else printf("os dois topos deve ser tipo NUM\n" );
        }
        else printf("pilha tem que ter pelo menos 2 Ops de tipo NUM\n" );
    }

    //instr(s) que usam CEL no topo da pilha
    //Intrução ATR, requisitada no enunciado
    if (opc >= ATR){
        if (pil->topo > 0){
            if (pil->val[pil->topo - 1].t == CEL){
                switch (opc) {
                    case ATR:
                        /*desempilha um operando que contem o endereço da celula na variavel tmp
                em seguida, tranfere-o para a "celula ponteiro" celula. Nesse ponto
                podemos alterar novamente o conteudo de tmp. Através de álgebra
                complicada justificada em https://www.codeproject.com/Questions/85450/How-to-access-structure-member-using-address-of-st
                obtemos o valor do atributo desejado, e o armazenamos em tmp.n.
                Resetamos o tipo de tmp como NUM e reempilhamos tmp. (o segundo
                argumento de empilha() precisa ser um OPERANDO).*/
                        tmp = desempilha(pil);
                        celula = tmp.c;
                        tmp.t = NUM;
                        tmp.n = *((int*)celula +arg.n);
                        tmp.ac = 0;
                        tmp.c = NULL;

                        empilha(pil, tmp);
                        break;
                }
            }
            else printf("topo deve ser celula\n");
        }
        else printf("pilha vazia. O OPERANDO deve ter tipo celula\n");
    }


	D(printf("ip = %d",ip));
	D(printf("\npil = "));
	D(imprime(pil,5));
	D(printf("\nexec = "));
	D(imprime(exec,5));
	D(puts("\n"));

	ip++;
    /*Caso o ip passe do tamanho do programa, ele volta ao zero
    * Esse loop evita falha de segmentação caso o programa não encerre
    * antes do fim do jogo.
    * Caso o programador não queira que o robô continue no loop, pode usar a
    * instrução END ao final do programa                                      */
    ip %= m->lenProg;
  }
}
