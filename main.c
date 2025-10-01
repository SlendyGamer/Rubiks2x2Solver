#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "arvores.h"
#include "no.h"
#include "pilhas.h"
#include "actions.h"
#include "bfs.h"



int solve_astar_min(const No *start_in, int max_depth_qtm); //prototipo da função


#define SEED 1344
#define GODSNUMBER 14
#define FACES 24
int main()
{
       


        srand(SEED);
        ////viewer                                 =(B0,A1,E3,E2,A0,D1,C1,E0,D0,C0, B1, E1, C2, F3, B3, B2, F1, A3, A2, F0, D3, C3, D2, F2); APENAS PARA VISUALIZAR
        int correct_state[FACES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
        //int current_state[FACES] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};



        No* current_state = malloc(sizeof(No));
        if (!current_state) { perror("malloc"); return 1; }

        memcpy(current_state->pattern, correct_state, 24 * sizeof(int));

        current_state->moves = 0;
        current_state->rotation = '-';
                
        memset(&current_state->cx, 0, 6 * sizeof(int));
        current_state->pai = NULL;
        current_state->prox = NULL;


        print_open(correct_state);


        shuffle(current_state, 20); //usar 6 pada debug
        
        printf("\n\n");
        print_open(current_state->pattern);

        puts("\nBusca A");


    int ok_astar = solve_astar_min(current_state, GODSNUMBER);//devolve 0 ou 1 se resolveu

     if (ok_astar == 1) {
        puts(" Solucao encontrada");
     } else {
        puts("sem Solucao");
     }



    free(current_state);
    return 0;


        /*
        if(bfs(current_state,correct_state))
                printf("sucesso bfs\n");
        else 
                printf("sem solução\n");

        return 0;

        
        if (dfs(p_states, current_state, correct_state) == 1)
        {
                printf("sucesso!");
        }
 
                printf("\n\n");
                print_open(current_state->pattern);

        libera(p_states);
        return 1;
        */

}
