Bruna Meneguzzi                         9327136
Caio Calisto Gaede Hirakawa             7590899
Ian Silva Galvão                        6817482

Técnicas de Programação - Projeto Batalha
Segunda Fase

Os arquivos estão comentados para esclarecer suas funções.

Como executar:

Há dois arquivos de teste: testeJogo.in e FatArena.in. No primeiro testamos os
comandos novos do robô, que são as chamadas do sistema, o comando PCEL, que põe
um OPERANDO com ponteiro para celula no topo da pilha, e o ATR, que empilha o
atributo desejado da celula no topo da pilha. O segundo roda a função fatorial,
e é util pois testamos outras funções, como CALL e RET, que mantém funcionamento
parecido, mas tiveram que ser atualizadas para rodar com a nova struct OPERANDO,
que agora possui tipo além de valores.

1. Para gerar os arquivos em C que executarão o programa, use:
    testeJogo:
    $python montador < testeJogo.in > testeJogo.c
    FatArena:
    $python montador < FatArena.in > FatArena.c

2. No diretório contendo todos os arquivos do programa, usar o comando make.
Isso compilará todos os arquivos C, criando os arquivos executaveis.

3. Para rodar o programas gerados, usar os comandos ./testeJogo ou ./FatArena

4. O programa deverá imprimir, na saída padrão, todos os estados intermediários
da arena, bem como valores que as máquinas tenham eventualmente sido programadas
para imprimir. Mensagens de erro ou de eventos do sistema também serão
impressas. A execução do programa termina quando as rodadas forem esgotadas.
