#include <stdlib.h>
#include "Coord.h"

Coord* criaCoord(int x, int y){
	Coord *c = malloc(sizeof(Coord));
	c->i = x;
	c->j = y;
	return c;
}