#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actions.h"
#include "pilhas.h"

No* rotate_x(No* state) //ok
{
    int aux = state->pattern[1];
    state->pattern[1] = state->pattern[11];
    state->pattern[11] = state->pattern[12];
    state->pattern[12] = state->pattern[16];
    state->pattern[16] = aux; //ok

    aux = state->pattern[17];
    state->pattern[17] = state->pattern[2];
    state->pattern[2] = state->pattern[9];
    state->pattern[9] = state->pattern[13];
    state->pattern[13] = aux; //ok

    aux = state->pattern[0];
    state->pattern[0] = state->pattern[10];
    state->pattern[10] = state->pattern[14];
    state->pattern[14] = state->pattern[15];
    state->pattern[15] = aux; //ok

    //state->cx++;
    //state->cy = 0;
    //state->cz = 0;

    return state;
}

No* rotate_y(No* state) //ok
{
    int aux = state->pattern[0];
    state->pattern[0] = state->pattern[4];
    state->pattern[4] = state->pattern[8];
    state->pattern[8] = state->pattern[9];
    state->pattern[9] = aux; //ok

    aux = state->pattern[10];
    state->pattern[10] = state->pattern[1];
    state->pattern[1] = state->pattern[5];
    state->pattern[5] = state->pattern[6];
    state->pattern[6] = aux; //ok

    aux = state->pattern[2];
    state->pattern[2] = state->pattern[3];
    state->pattern[3] = state->pattern[7];
    state->pattern[7] = state->pattern[11];
    state->pattern[11] = aux; //ok

    //state->cx =0;
    //state->cy++;
    //state->cz = 0;

    return state;
}

No* rotate_z(No* state) //ok
{
    int aux = state->pattern[2];
    state->pattern[2] = state->pattern[15];
    state->pattern[15] = state->pattern[19];
    state->pattern[19] = state->pattern[5];
    state->pattern[5] = aux; //ok

    aux = state->pattern[3];
    state->pattern[3] = state->pattern[0];
    state->pattern[0] = state->pattern[16];
    state->pattern[16] = state->pattern[20];
    state->pattern[20] = aux; //ok

    aux = state->pattern[4];
    state->pattern[4] = state->pattern[1];
    state->pattern[1] = state->pattern[17];
    state->pattern[17] = state->pattern[18];
    state->pattern[18] = aux; //ok

    //state->cx = 0;
    //state->cy = 0;
    //state->cz++;

    return state;
}



void print_open(int cube[])
{
printf("        %2d %2d\n"
       "        %2d %2d\n"
       "      ---------\n",
cube[7], cube[11],
cube[3], cube[2]); // top

printf("%2d %2d | %2d %2d | %2d %2d | %2d %2d\n"
       "%2d %2d | %2d %2d | %2d %2d | %2d %2d\n",
       cube[8], cube[5], cube[4], cube[1],
       cube[0], cube[10], cube[9], cube[6],
       cube[22], cube[20], cube[18], cube[17],
       cube[15], cube[14], cube[12], cube[21]); // middle

printf("      ---------\n"
       "        %2d %2d\n"
       "        %2d %2d\n",
       cube[19], cube[16],
       cube[23], cube[13]); // bottom
}

void shuffle(No* cube, int max)
{
    int num_moves = rand() % max + 1;
    for (int i = 0; i < num_moves; i++)
    {
        int move = rand() % 3; // 0 = rot_x, 1 = rot_y, 2 = rot_z
        //printf("%d\n", move);
        switch (move)
        {
            case 0:
                cube = rotate_x(cube);
                printf("rot x\n");
                //print_open(cube);
                break;
            case 1:
                cube = rotate_y(cube);
                printf("rot y\n");
                //print_open(cube);
                break;
            case 2:
                cube = rotate_z(cube);
                printf("rot z\n");
                //print_open(cube);
                break;
        }
    }
    //system("pause");
}




void sucessora(Pilha *p, No* state, char dir)
{
    No* auxNo = malloc(sizeof(No));
    memcpy(auxNo, state, sizeof(No));
    switch(dir)
    {
        case 'x':
            auxNo->cx++;
            auxNo->cy = 0;
            auxNo->cz = 0;
            auxNo->rotation = 'x';
            auxNo->pai = state;
            push(p, rotate_x(auxNo));
            break;
        case 'y':
            auxNo->cx = 0;
            auxNo->cy++;
            auxNo->cz = 0;
            auxNo->rotation = 'y';
            auxNo->pai = state;
            push(p, rotate_y(auxNo));
            break;
        case 'z':
            auxNo->cx = 0;
            auxNo->cy = 0;
            auxNo->cz++;
            auxNo->rotation = 'z';
            auxNo->pai = state;
            push(p, rotate_z(auxNo));
            break;
        default:
            perror("variavel dir deve ser 'x', 'y' ou 'z'");
            exit(2);
    }
}

int dfs(Pilha *p, No* state, int ideal_pattern[])
{
    Pilha* pFinal = CriaPilha();
    push(p, state);
                printf("%d %d %d %d %c\n", p->Topo->cx, p->Topo->cy, p->Topo->cz, p->Topo->pattern[0], p->Topo->rotation);

    while (!vaziaPilha(p))
    {
        //for(int i=0; i<100; i++)
        //{
        state = pop(p);
        //printf("rotacao %c\n", state->rotation);

        //printf("%d %d %d %d %c", state->cx, state->cy, state->cz, state->pattern[0], state->rotation);
        push(pFinal, state);
        //printf("%d %d %d %d %c", state->cx, state->cy, state->cz, state->pattern[0], state->rotation);

        //system("pause");
        if (memcmp(state->pattern, ideal_pattern, 24 * sizeof(int)) == 0)
        {
            printf("completed %d moves\n", state->moves);
            //printf("%d %d %d %d %c\n", p->Topo->cx, p->Topo->cy, p->Topo->cz, p->Topo->pattern[0], p->Topo->rotation);
            //printf("%d %d %d %d %c", state->cx, state->cy, state->cz, state->pattern[0], state->rotation);
            //while (state != NULL)
            //{
            //    printf("%c\t", state->rotation);
            printf("pai: %c\n", state->pai->rotation);
            //    state = state->pai;
            //}
            imprimePilha(pFinal);
            return 1;
        }
        if (state->moves < 14)
        {
            //push(pFinal, state);
            if (state->cz < 3)
                sucessora(p, state, 'z');
            if (state->cy < 3)
                sucessora(p, state, 'y');
            if (state->cx < 3)
            {
                sucessora(p, state, 'x'); //soma cx em 1
            }
        }

    }
    return 0;
}


