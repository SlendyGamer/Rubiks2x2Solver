#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "no.h"
#include "pilhas.h"
#include "FILA.h"
#include "actions.h"

#define SEED 1344
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
        int correct_state[FACES] = {
        18, 17, 4, 1,        // Front face (4 quads)
        12, 21, 9, 6,        // Back face
        22, 20, 8, 5,        // Left face
        15, 14, 0, 10,       // Right face
        3, 2, 7, 11,         // Top face
        23, 13, 19, 16       // Bottom face
        };

        No* current_state = malloc(sizeof(No));
        memcpy(current_state->pattern, correct_state, 24 * sizeof(int));

        print_open(correct_state);
        Fila *f_states = CriaFila();
        rotate_y(current_state);
        rotate_x(current_state);
        rotate_y(current_state);
        rotate_z(current_state);
        rotate_y(current_state);
        rotate_z(current_state);
        rotate_x(current_state);
        rotate_y(current_state);
        rotate_x(current_state);
        rotate_x(current_state);
        rotate_y(current_state);
        rotate_x(current_state);
        rotate_y(current_state);
        rotate_x(current_state);
        rotate_y(current_state);
        rotate_x(current_state);
        rotate_y(current_state);
        //shuffle(current_state, 20); //usar 6 pada debug

        printf("\n\n");
        print_open(current_state->pattern);

        //if (dfs(p_states, current_state, correct_state) == 1)
        if (bfs(f_states, current_state, correct_state) == 1)
        {
                printf("sucesso!");
        }
        else    
                printf("fail!");
                
        liberaFila(f_states);
        return 1;

}
