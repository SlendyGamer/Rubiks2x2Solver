#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

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

No* rotate_NOTx(No* state) //ok
{
    int aux = state->pattern[1];
    state->pattern[1] = state->pattern[16];
    state->pattern[16] = state->pattern[12];
    state->pattern[12] = state->pattern[11];
    state->pattern[11] = aux; //ok

    aux = state->pattern[17];
    state->pattern[17] = state->pattern[13];
    state->pattern[13] = state->pattern[9];
    state->pattern[9] = state->pattern[2];
    state->pattern[2] = aux; //ok

    aux = state->pattern[0];
    state->pattern[0] = state->pattern[15];
    state->pattern[15] = state->pattern[14];
    state->pattern[14] = state->pattern[10];
    state->pattern[10] = aux; //ok

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

No* rotate_NOTy(No* state) //ok
{
    int aux = state->pattern[0];
    state->pattern[0] = state->pattern[9];
    state->pattern[9] = state->pattern[8];
    state->pattern[8] = state->pattern[4];
    state->pattern[4] = aux; //ok

    aux = state->pattern[10];
    state->pattern[10] = state->pattern[6];
    state->pattern[6] = state->pattern[5];
    state->pattern[5] = state->pattern[1];
    state->pattern[1] = aux; //ok

    aux = state->pattern[2];
    state->pattern[2] = state->pattern[11];
    state->pattern[11] = state->pattern[7];
    state->pattern[7] = state->pattern[3];
    state->pattern[3] = aux; //ok

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

No* rotate_NOTz(No* state) //ok
{
    int aux = state->pattern[2];
    state->pattern[2] = state->pattern[5];
    state->pattern[5] = state->pattern[19];
    state->pattern[19] = state->pattern[15];
    state->pattern[15] = aux; //ok

    aux = state->pattern[3];
    state->pattern[3] = state->pattern[20];
    state->pattern[20] = state->pattern[16];
    state->pattern[16] = state->pattern[0];
    state->pattern[0] = aux; //ok

    aux = state->pattern[4];
    state->pattern[4] = state->pattern[18];
    state->pattern[18] = state->pattern[17];
    state->pattern[17] = state->pattern[1];
    state->pattern[1] = aux; //ok

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
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'x';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_x(auxNo);
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
            auxNo = rotate_NOTx(auxNo);
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
            auxNo = rotate_y(auxNo);
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
            auxNo = rotate_NOTy(auxNo);
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
            auxNo = rotate_z(auxNo);
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
            auxNo = rotate_NOTz(auxNo);
            push(p, auxNo);
            break;
        default:
            perror("variavel dir deve ser 'x/X', 'y/Y' ou 'z/Z'");
            exit(2);
    }
}

int dfs(Pilha *p, No* state, int solution[])
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
           imprimePilha(pFinal);
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

/*int DFS(Pilha* p, int state[], int ideal_state[], int *moves)
{
    //Pilha *py = CriaPilha();
    //Pilha *pz = CriaPilha();
    if (memcmp(state, ideal_state, 24 * sizeof(int)) == 0)
    {
        printResultado(p);
        //printf("sucesso");
        return 1;
    }

    if ((*moves) >= 14)
        return 0;

    //printf("%d", p->Topo->cx); //debug
    //system("pause"); //debug
    if (p->Topo->cx < 3)
    {
        push(p, state); //arrumar push
        rotate_x(state);
        p->Topo->cx++;
        p->Topo->cy = 0;
        p->Topo->cz = 0;
        (*moves)++;
        //printf("x\n");
        if (DFS(p, state, ideal_state, moves)) //roda em x primeiro ate atingir altura max
        return 1;
        (*moves)--;
        pop(p, state); //arrumar pop
    }
    if (p->Topo->cy < 3)
    {
        push(p, state);
        rotate_y(state);
        p->Topo->cy++;
        p->Topo->cx = 0;
        p->Topo->cz = 0;
        (*moves)++;
        //printf("y\n");
        if (DFS(p, state, ideal_state, moves)) //roda em y apos rodar em x
            return 1;
        (*moves)--;
        pop(p, state);
    }
    if (p->Topo->cz < 3)
    {
        push(p, state);
        rotate_z(state);
        p->Topo->cz++;
        p->Topo->cx = 0;
        p->Topo->cy = 0;
        (*moves)++;
        //printf("z\n");
        if (DFS(p, state, ideal_state, moves)) //roda em z apos rodar em x e y
            return 1;
        (*moves)--;
        pop(p, state);
    }
    //pop(p, state);
    //system("pause");
    return 0;
}// é possivel fazer sem recursão!
*/



#endif
