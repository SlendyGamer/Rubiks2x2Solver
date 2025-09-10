#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "pilhas.h"

// Rotaciona e devolve o próprio ponteiro (estado é modificado in-place)
No* rotate_x(No* state);
No* rotate_y(No* state);
No* rotate_z(No* state);

// Visualização do cubo (somente leitura)
void print_open(int cube[]);

// Embaralha aplicando até 'max' movimentos aleatórios (x/y/z)
void shuffle(No* cube, int max);

// Suporte ao seu DFS antigo (se ainda for usar)
void sucessora(Pilha *p, No* state, char dir);
int  dfs(Pilha *p, No* state, int ideal_pattern[]);

#endif // ACTIONS_H_INCLUDED
