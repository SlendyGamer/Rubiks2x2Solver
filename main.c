#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "arvores.h"
#include "pilhas.h"
#include "actions.h"

#define SEED 1114
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
        //int moves = 0;
        print_open(correct_state);
        Pilha *p_states = CriaPilha();
        shuffle(current_state, 20); //usar 6 pada debug
        printf("\n\n");
        print_open(current_state->pattern);
        //push(p_states, current_state);
        //print_open(current_state.pattern);
        //push(p_states, current_state);
        //if (dfs_old(p_states, current_state, correct_state, &moves))
        if (dfs(p_states, current_state, correct_state) == 1)
        {
                printf("sucesso!");
        }
        //if (DFS(p_states, current_state, correct_state, &moves)) //arumar funcao para evitar rodar mais de 4 vezes na mesma direcao
        //{
        //        printf("sucesso com %d moves", moves);
        //        //printResultado(p_states);
                //imprimePilha(p_states);
                //imprimePilhaOld(p_states);
                printf("\n\n");
                print_open(current_state->pattern);
        //        return 0;
        //}
        //printf("falha");
        libera(p_states);
        return 1;

}
