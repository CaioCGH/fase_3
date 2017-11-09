#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "maq.h"
#include "celula.h"
#include <time.h>

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
/*a funcao printArena imprime a arena no terminal. Para que ela possa
ser atualizada corretamente turno a turno o terminal deve estar com
24 linhas de altura. Se houver prints no programa passado para o robo,
a arena saira do seu registro no terminal.
Para recriar o padrão hexagonal, cada celula precisa ocupar duas
linhas, que devem ser printadas de modo diferente. Além disso,
dependendo do nº da celula na linha, ela é printada para baixo ou
para cima. Por isso a função tem vários ifs que checam a paridade da
linha e da coluna, além de outros para checar o que tem na celula.

A ocupacao de cada celula é representada da seguinte forma:

	robo = 		 /RR\
		   		 \RR/

	n Cristais = /nC\
		         \CC/

	base  = 	 /BB\
		    	 \BB/

	vazia = 	 /^^\
		    	 \__/

Como os graficos no terminal sao provisorios e servem para realização
de testes, há um problema que não nos preocupamos em corrigir: a
primeira e a ultima linha não imprimem o que tem em cada celula, o
que nao é problema, pois a informacao é disponivel na linha vizinha.

*/
void printArena(Arena *a){

	int i;
	int j;
	for (j= 0 ; j < a->dim/2; j++){
		printf("    /^^\\");
	}
	printf("\n");
	for (i= 0 ; i < a->dim * 2  - 1; i++){
		// if ((i%2) == 0) printf("  ");
		if (i%2 == 0){
			for (j= 0 ;j<a->dim;j++){
				if (a->cel[i/2][j]->ocupacao >= 0){
					if ((j%2) == 0) printf("/RR\\");
					else printf ("\\RR/");
				}
				else if (a->cel[i/2][j]->base >= 0){
					if ((j%2) == 0) printf("/BB\\");
					else printf ("\\BB/");
				}
				else if (a->cel[i/2][j]->cristais > 0){
					if ((j%2) == 0) printf("/%dC\\",a->cel[i/2][j]->cristais);
					else printf ("\\%dC/",a->cel[i/2][j]->cristais);
				}
				else{
					int t = a->cel[i/2][j]->terreno;
				if ((j%2) == 0) printf("/%d^\\", t);
					else printf ("\\%d_/",t);
				}
			}
		}
		else{
			for (j= 0 ;j<a->dim;j++){
				if ((j%2) == 0){
					if (a->cel[i/2][j]->ocupacao >= 0) printf ("\\RR/");
					else {
						if (a->cel[i/2][j]->base >= 0) printf ("\\BB/");
						else {
							if (a->cel[i/2][j]->cristais > 0) printf ("\\CC/");
							else printf ("\\__/");
						}
					}
				}
				else {
					if (a->cel[i/2+1][j]->ocupacao >= 0) printf ("/RR\\");
					else {
						if (a->cel[i/2+1][j]->base >= 0) printf ("/BB\\");
						else {
							if (a->cel[i/2+1][j]->cristais > 0) printf ("/CC\\");
							else printf ("/^^\\");
						}
					}
				}
			}
		}

		printf("\n");

		//printf("\\__/");
		//for (j= 0 ;j < a->dim/2;j++){
		//	printf("/^^\\\\__/");
		//}
		//printf("\n");
		// if ((i%2) == 0) printf("  ");

	}
	for (j= 0 ;j<(a->dim + 1)/2;j++){
		printf("\\__/    ");
	}
	printf("\n");
	// if ((i%2) == 0) printf("  ");
/*	printf("/RR\\");
	for (j= 0 ;j< 5;j++){
		printf("\\\\////\\\\");
	}
	printf("\n");
	// if ((i%2) == 0) printf("  ");
	printf("\\RR/");
	for (j= 0 ;j<5;j++){
		printf("//\\\\\\\\//");
	}
	printf("\n");*/

}
