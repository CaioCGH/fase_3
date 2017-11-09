#include "typedefs.h"

struct Coord {
    int i;
    int j;
};

struct CubeCoord {
    int x;
    int y;
    int z;
};

Coord *cria_coordenada();
void destroi_coordenada();
