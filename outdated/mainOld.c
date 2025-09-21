#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "arvores.h"
#include "pilhasOld.h"
#include "actionsOld.h"

#define SEED 1344 //1344 e 20 quebra
#define GODSNUMBER 14
#define FACES 24
int main()
{
        /*Adicionar estado na estrutura
        Enquanto a estrutura não estiver vazia:
                Remover próximo estado da estrutura
                Avaliar estado
                        SE estado final -> mostrar solução e encerrar o programa
                Adicionar estados seguintes na estrutura
        Retornar "Sem solução"*/
        srand(SEED);
        ////viewer                                 =(B0,A1,E3,E2,A0,D1,C1,E0,D0,C0, B1, E1, C2, F3, B3, B2, F1, A3, A2, F0, D3, C3, D2, F2); APENAS PARA VISUALIZAR
        int correct_state[FACES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
        //int current_state[FACES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
        No* current_state = malloc(sizeof(No));
        memcpy(current_state->pattern, correct_state, 24 * sizeof(int));
        int moves = 0;

        print_open(correct_state);

        Pilha *p_states = CriaPilha();
        shuffle(current_state->pattern, 20); //usar 6 pada debug
        //rotate_x(current_state->pattern);
        //rotate_y(current_state->pattern);
        //rotate_y(current_state->pattern);
        //rotate_y(current_state->pattern);
        //rotate_x(current_state->pattern);
        printf("\n\n");
        print_open(current_state->pattern);
        printf("teste\n");
        //push(p_states, current_state);
        //printf("%d %d %d %d %c %c", p_states->Topo->cx, p_states->Topo->cy, p_states->Topo->cz, p_states->Topo->pattern[0], p_states->Topo->rotation, p_states->Topo->status);
        if (dfs(p_states, current_state, correct_state, &moves))
        {
                printf("sucesso com %d moves\n", moves);
                //imprimePilha(p_states);
        }
        else
        {
            printf("falha");
        }
        printf("\n\n");
        print_open(current_state->pattern);
        libera(p_states);
        return 1;


}
//rot y   rot y
//rot x   rot x
//rot y   rot y
//rot z   rot z
//rot y   rot y
//rot z   rot z
//rot x   rot x
//rot y   rot y
//rot x   rot x
//rot x   rot x
//rot y   rot y
//rot x   rot x
//rot y   rot y
//rot x   rot x
//rot y   rot y
//rot y   rot x
//rot x   rot y
//x z y z y y x y x z y x x y x -

//x z y z y y x y x z y x x y x
