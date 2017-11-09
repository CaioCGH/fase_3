#include "typedefs.h"
#include "Coord.h"

#define DIMMAX 11
#define CRISTDIST 2
#define CRISTPROB 15
#define CRISTAISARENA 5
#define NCRISTAIS 5
#define ROBMAX 99
#define CHAMMAX 99
#define TAMEXER 5


/*enum CHAMADA{
    MOVE,
    ATAC,
    RECO,
    DEPO
};

struct OPERACAO{
  int m;
  CHAMADA a;
  int dir;
};
*/
struct Arena{
  int nRobos;
  int nChamadas;
  int dim;
  int jAtiv;
  int ativ[(ROBMAX + 1) / TAMEXER]; // robos ativos
  //int maquinas[ROBMAX+1];     // nao sei se precisa

  Coord bases[(ROBMAX + 1) / TAMEXER];
  Coord cord[ROBMAX+1];	// enunciado diz que precisa, parece inutil
  //OPERACAO chamadas[CHAMMAX];

  Maquina *robos[ROBMAX+1];
  Celula     *cel[DIMMAX+1][DIMMAX+1];
};

Arena* criaArena(int nJogadores);
Coord toCoord(CubeCoord cC);
CubeCoord toCube(Coord c);
Coord somaCoord (Coord c, int d);
static void Fatal(char *msg, int cod);
void checarCristaisBase(Arena *a, int x, int y);
void mover(Arena *a, int m, int dir);
void atacar(Arena *a, int m, int dir);
void depositar(Arena *a, int m, int dir);
void recolher(Arena *a, int m, int dir);
void carregaArena(Arena *a,char *terreno[][11]);
void destroi_arena(Arena *a);
void resolve_chamadas(Maquina *m, Arena *a);
void atualiza(Arena *a, int n);
void insereTerreno(Arena *a);
void insereCristais(Arena *a);
void insereBases(Arena *a);
void insereExercito(Arena *a, INSTR *p,int lP);
void removeExercito(Arena *a,int ex);
void registro();
void sistema(int ip, Maquina *m);
