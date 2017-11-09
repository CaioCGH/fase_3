CC     = gcc
CFLAGS = -Wall -lm
RM     = rm -rf

#---------------------------------#
all: testeJogo FatArena

testeJogo: testeJogo.c arena.c celula.c Coord.c maq.c pilha.c printArena.c
	$(CC) -o testeJogo $^

FatArena: FatArena.c arena.c celula.c Coord.c maq.c pilha.c printArena.c
	$(CC) -o FatArena $^
