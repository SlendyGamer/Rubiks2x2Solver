#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED
#include "pilhas.h"
#include <string.h>

No* rotate_xX(No* state) //ok
{
    int aux;
    // Ciclo 1: 1 → 16 → 12 → 11 → 1
    aux = state->pattern[3];
    state->pattern[3] = state->pattern[19];
    state->pattern[19] = state->pattern[4];
    state->pattern[4] = state->pattern[23];
    state->pattern[23] = aux;

    // Ciclo 2: 17 → 13 → 9 → 2 → 17
    aux = state->pattern[1];
    state->pattern[1] = state->pattern[17];
    state->pattern[17] = state->pattern[6];
    state->pattern[6] = state->pattern[21];
    state->pattern[21] = aux;

    // Ciclo 3: 0 → 15 → 14 → 10 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[15];
    state->pattern[15] = state->pattern[13];
    state->pattern[13] = state->pattern[12];
    state->pattern[12] = aux;

    return state;
}

No* rotate_NOTxX(No* state) //ok
{
    // Ciclo 1: 1 → 16 → 12 → 11 → 1
    int aux = state->pattern[3];
    state->pattern[3] = state->pattern[23];
    state->pattern[23] = state->pattern[4];
    state->pattern[4] = state->pattern[19];
    state->pattern[19] = aux;

    // Ciclo 2: 17 → 2 → 9 → 13 → 17
    aux = state->pattern[1];
    state->pattern[1] = state->pattern[21];
    state->pattern[21] = state->pattern[6];
    state->pattern[6] = state->pattern[17];
    state->pattern[17] = aux;

    // Ciclo 3: 0 → 10 → 14 → 15 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[12];
    state->pattern[12] = state->pattern[13];
    state->pattern[13] = state->pattern[15];
    state->pattern[15] = aux;

    return state;
}

No* rotate_yY(No* state) //ok
{
    int aux;
    // Ciclo 1: 0 → 9 → 8 → 4 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[2];
    state->pattern[2] = state->pattern[10];
    state->pattern[10] = state->pattern[6];
    state->pattern[6] = aux;

    // Ciclo 2: 10 → 6 → 5 → 1 → 10
    aux = state->pattern[15];
    state->pattern[15] = state->pattern[3];
    state->pattern[3] = state->pattern[11];
    state->pattern[11] = state->pattern[7];
    state->pattern[7] = aux;

    // Ciclo 3: 2 → 11 → 7 → 3 → 2
    aux = state->pattern[17];
    state->pattern[17] = state->pattern[16];
    state->pattern[16] = state->pattern[18];
    state->pattern[18] = state->pattern[19];
    state->pattern[19] = aux;

    return state;
}

No* rotate_NOTyY(No* state) //ok
{
    int aux;
    // Ciclo 1: 0 → 9 → 8 → 4 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[6];
    state->pattern[6] = state->pattern[10];
    state->pattern[10] = state->pattern[2];
    state->pattern[2] = aux;

    // Ciclo 2: 10 → 6 → 5 → 1 → 10
    aux = state->pattern[15];
    state->pattern[15] = state->pattern[7];
    state->pattern[7] = state->pattern[11];
    state->pattern[11] = state->pattern[3];
    state->pattern[3] = aux;

    // Ciclo 3: 2 → 11 → 7 → 3 → 2
    aux = state->pattern[17];
    state->pattern[17] = state->pattern[19];
    state->pattern[19] = state->pattern[18];
    state->pattern[18] = state->pattern[16];
    state->pattern[16] = aux;

    return state;
}

No* rotate_zZ(No* state) //ok
{
    int aux;
    // Ciclo 1: 5 → 19 → 15 → 2 → 5
    aux = state->pattern[11];
    state->pattern[11] = state->pattern[17];
    state->pattern[17] = state->pattern[12];
    state->pattern[12] = state->pattern[22];
    state->pattern[22] = aux;

    // Ciclo 2: 20 → 16 → 0 → 3 → 20
    aux = state->pattern[9];
    state->pattern[9] = state->pattern[16];
    state->pattern[16] = state->pattern[14];
    state->pattern[14] = state->pattern[23];
    state->pattern[23] = aux;

    // Ciclo 3: 4 → 18 → 17 → 1 → 4
    aux = state->pattern[2];
    state->pattern[2] = state->pattern[3];
    state->pattern[3] = state->pattern[1];
    state->pattern[1] = state->pattern[0];
    state->pattern[0] = aux;

    return state;
}

No* rotate_NOTzZ(No* state) //ok
{
    int aux;
    // Ciclo 1: 5 → 19 → 15 → 2 → 5
    aux = state->pattern[11];
    state->pattern[11] = state->pattern[22];
    state->pattern[22] = state->pattern[12];
    state->pattern[12] = state->pattern[17];
    state->pattern[17] = aux;

    // Ciclo 2: 20 → 16 → 0 → 3 → 20
    aux = state->pattern[9];
    state->pattern[9] = state->pattern[23];
    state->pattern[23] = state->pattern[14];
    state->pattern[14] = state->pattern[16];
    state->pattern[16] = aux;

    // Ciclo 3: 4 → 18 → 17 → 1 → 4
    aux = state->pattern[2];
    state->pattern[2] = state->pattern[0];
    state->pattern[0] = state->pattern[1];
    state->pattern[1] = state->pattern[3];
    state->pattern[3] = aux;

    return state;
}

void print_open(int cube[])
{
printf("        %2d %2d\n"
       "        %2d %2d\n"
       "      ---------\n",
cube[18], cube[19],
cube[16], cube[17]); // top

printf("%2d %2d | %2d %2d | %2d %2d | %2d %2d\n"
       "%2d %2d | %2d %2d | %2d %2d | %2d %2d\n",
       cube[10], cube[11], cube[2], cube[3],
       cube[14], cube[15], cube[6], cube[7],
       cube[8], cube[9], cube[0], cube[1],
       cube[12], cube[13], cube[4], cube[5]); // middle

printf("      ---------\n"
       "        %2d %2d\n"
       "        %2d %2d\n",
       cube[22], cube[23],
       cube[20], cube[21]); // bottom
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
                cube = rotate_xX(cube);
                printf("rot x\n");
                //print_open(cube);
                break;
            case 1:
                cube = rotate_yY(cube);
                printf("rot y\n");
                //print_open(cube);
                break;
            case 2:
                cube = rotate_zZ(cube);
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
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'x';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_xX(auxNo);
            push(p, auxNo);
            break;
        case 'X': //X'
            auxNo->cx = 0;
            auxNo->cNx++;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'X';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTxX(auxNo);
            push(p, auxNo);
            break;
        case 'y':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy++;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_yY(auxNo);
            push(p, auxNo);
            break;
        case 'Y': //Y'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy++;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'Y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTyY(auxNo);
            push(p, auxNo);
            break;
        case 'z':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz++;
            auxNo->cNz = 0;
            auxNo->rotation = 'z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_zZ(auxNo);
            push(p, auxNo);
            break;
        case 'Z': //Z'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz++;
            auxNo->rotation = 'Z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTzZ(auxNo);
            push(p, auxNo);
            break;
        default:
            perror("variavel dir deve ser 'x/X', 'y/Y' ou 'z/Z'");
            exit(2);
    }
}

int dfs(Pilha *p, No* state, int solution[], Pilha *path)
{
    Pilha* pFinal = CriaPilha();
    state->pai = NULL;
    state->cx = 0;
    state->cy = 0;
    state->cz = 0;
    state->moves = 0;
    state->rotation = '-';
    state->pai = NULL;
    state->prox = NULL;
    print_open(state->pattern);
    push(p, state);
    while(!vaziaPilha(p))
    {
        state = pop(p);
        push(pFinal, state);

        if(memcmp(state->pattern, solution, 24 * sizeof(int)) == 0)
        {
           //printa moves
           printf("sucesso com %d moves\n", state->moves);
           print_open(state->pattern);
           preparePathPilha(pFinal, path);
           imprimePilha(path);
           //imprimePilha(pFinal);
           return 1;
        }

        if (state->moves < 14)
        {
            if (state->cz < 2 && state->cNz == 0)
                sucessora(p, state, 'z');
            if (state->cNz < 1 && state->cz == 0)
                sucessora(p, state, 'Z');

            if (state->cy < 2 && state->cNy == 0)
                sucessora(p, state, 'y');
            if (state->cNy < 1 && state->cy == 0)
                sucessora(p, state, 'Y');

            if (state->cx < 2 && state->cNx == 0)
                sucessora(p, state, 'x'); //soma cx em 1
            if (state->cNx < 1 && state->cx == 0)
                sucessora(p, state, 'X');
        }
        //nao preciso de moves--; em else aqui
    }
    return 0;
}

void sucessoraBFS(Fila *f, No* state, char dir)
{
    No* auxNo = malloc(sizeof(No));
    memcpy(auxNo, state, sizeof(No));
    switch(dir)
    {
        case 'x':
            auxNo->cx++;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'x';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_xX(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'X': //X'
            auxNo->cx = 0;
            auxNo->cNx++;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'X';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTxX(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'y':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy++;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_yY(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'Y': //Y'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy++;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'Y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTyY(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'z':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz++;
            auxNo->cNz = 0;
            auxNo->rotation = 'z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_zZ(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'Z': //Z'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz++;
            auxNo->rotation = 'Z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTzZ(auxNo);
            InsereFila(f, auxNo);
            break;
        default:
            perror("variavel dir deve ser 'x/X', 'y/Y' ou 'z/Z'");
            exit(2);
    }
}

int bfs(Fila *f, No* state, int solution[], Pilha *path)
{
    Fila* fFinal = CriaFila();
    state->pai = NULL;
    state->cx = 0;
    state->cy = 0;
    state->cz = 0;
    state->moves = 0;
    state->rotation = '-';
    state->pai = NULL;
    state->prox = NULL;
    print_open(state->pattern);
    InsereFila(f, state);
    while(!VaziaFila(f))
    {
        state = RetiraFila(f);
        //printf("rotation: %c\n",state->rotation);
        InsereFila(fFinal, state);

        if(memcmp(state->pattern, solution, 24 * sizeof(int)) == 0)
        {
           //printa moves
           printf("sucesso com %d moves\n", state->moves);
           print_open(state->pattern);
           preparePathFila(fFinal, path);
           imprimePilha(path);
           //imprimeFila(fFinal);
           return 1;
        }

        if (state->moves < 14)
        {
            if (state->cz < 2 && state->cNz == 0)
                sucessoraBFS(f, state, 'z');
            if (state->cNz < 1 && state->cz == 0)
                sucessoraBFS(f, state, 'Z');

            if (state->cy < 2 && state->cNy == 0)
                sucessoraBFS(f, state, 'y');
            if (state->cNy < 1 && state->cy == 0)
                sucessoraBFS(f, state, 'Y');

            if (state->cx < 2 && state->cNx == 0)
                sucessoraBFS(f, state, 'x'); //soma cx em 1
            if (state->cNx < 1 && state->cx == 0)
                sucessoraBFS(f, state, 'X');
        }
        //nao preciso de moves--; em else aqui
    }
    return 0;
}


#endif
