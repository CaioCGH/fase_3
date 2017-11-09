#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Lê, na entrada padrão, um programa na linguagem de montagem da máquina
virtual e retorna um programa em C que executa este programa.

Uso:
    montador < entrada > saida
"""
from sys import stdin


print("#include <stdio.h>")
print('#include "arena.h"')
print('#include "maq.h"')
print('#include "celula.h"')
print('#include "printArena.h"')

# incluimos uma funcionalidade para ler a arena a partir de um arquivo.
# o nome do arquivo deve ser a primeira linha do StdIn.
# a Arena será carregada a partir do vetor de char 'terreno', de mesmas
# dimensões que a arena (11 x 11), que é declarado aqui.

l = stdin.readline() # nome do arquivo
l = l.rstrip()       # retira \n
f = open(l)
lines = f.readlines()

print("char *terreno[11][11] = {")
for line in lines:
    print ("{"),
    for char in line.rstrip():
        print ('"%s",'%(char)),
    print ("},")
print ("};\n")

l = stdin.readline()
ip = 0

tabsim = {}


print("INSTR prog[] = {")
while l:
	label = op = ""
	arg   = 0
	try:
		l = l[:l.index('#')]
	except:
		pass
	keys = l.split()
	if len(keys) > 0 and keys[0].endswith(":"):
		label = keys[0][:-1]              #jogando fora o ':'
		tabsim[label]=ip
		keys.pop(0)
	if len(keys) > 0:
		op = keys.pop(0)
	if len(keys) > 0:
		arg = keys.pop(0)
		if arg in tabsim:
			arg = tabsim[arg]
	if op != "":
        # como o unico tipo de OPERANDO que não é int é a celula, que não faz
        # sentido ser passada como argumento(pois é um ponteiro), os argumentos
        # são todos NUM
		print("  {%s, {%s, NUM } },"%(op,arg))
		ip += 1
	else:
		print
	l = stdin.readline()
print("};\n")

print(  "int main(int ac, char **av) {\n"
        "  Arena *a = criaArena();\n"
        "  carregaArena(a,terreno); \n" # load arena a partir da matrix terreno
        "  insereExercito(a,prog," + str(ip) + ");\n"
        "  atualiza(a,27);\n"
        "  printArena(a);\n"
        "  destroi_arena(a);\n"
        "  return 0;\n}")

# 27 é o numero de rodadas ideal para rodar o programa em testeJogo.in, pois
# no estado final do terminal é possível verificar todos os prints importantes,
# que são: Os que printam os ATRs e o de remoção de exército, além de visualisar
# as mudanças ocorridas na arena em função das chamadas de sistem(MOV,REC e DEP)





# Local variables:
# mode: python
# End:
