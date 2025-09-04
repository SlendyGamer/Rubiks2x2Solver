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

void rotate_xOld(int state[]) //ok
{
    int aux = state[1];
    state[1] = state[11];
    state[11] = state[12];
    state[12] = state[16];
    state[16] = aux; //ok

    aux = state[17];
    state[17] = state[2];
    state[2] = state[9];
    state[9] = state[13];
    state[13] = aux; //ok

    aux = state[0];
    state[0] = state[10];
    state[10] = state[14];
    state[14] = state[15];
    state[15] = aux; //ok

    //state->cx++;
    //state->cy = 0;
    //state->cz = 0;

    //return state;
}

void rotate_yOld(int state[]) //ok
{
    int aux = state[0];
    state[0] = state[4];
    state[4] = state[8];
    state[8] = state[9];
    state[9] = aux; //ok

    aux = state[10];
    state[10] = state[1];
    state[1] = state[5];
    state[5] = state[6];
    state[6] = aux; //ok

    aux = state[2];
    state[2] = state[3];
    state[3] = state[7];
    state[7] = state[11];
    state[11] = aux; //ok

    //state->cx =0;
    //state->cy++;
    //state->cz = 0;

    //return state;
}

void rotate_zOld(int state[]) //ok
{
    int aux = state[2];
    state[2] = state[15];
    state[15] = state[19];
    state[19] = state[5];
    state[5] = aux; //ok

    aux = state[3];
    state[3] = state[0];
    state[0] = state[16];
    state[16] = state[20];
    state[20] = aux; //ok

    aux = state[4];
    state[4] = state[1];
    state[1] = state[17];
    state[17] = state[18];
    state[18] = aux; //ok

    //state->cx = 0;
    //state->cy = 0;
    //state->cz++;

    //return state;
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


/*int DFS(Pilha* p, int state[], int ideal_state[], int moves)
{
    //checa se é final
    //se for. end(returna caminho)
    //else
    //while (!vaziaPilha(p))
    //{
        if (moves < 14)
        {
            push(p, state); //modificar push
            rotate_x(state);
            DFS(p, state, ideal_state, moves); //roda em x primeiro ate atingir altura max

            rotate_y(state);
            DFS(p, state, ideal_state, moves); //roda em y

            rotate_z(state);
            DFS(p, state, ideal_state, moves); //roda em z
        }
        else
        {
            pop(p, state); //modificar pop
            return 0; //nao tem nada aqui, volta para estado passado
        }
    //}
}*/

/*void printResultado(Pilha* p)
{
    Pilha *auxP = CriaPilha();
    int auxV[24];
    //No* auxNo = NULL;
    while(!vaziaPilha(p))
    {
        push(auxP, auxV);
        pop(p, NULL);

    }

    while (auxP != NULL)
    {
        pop(auxP, auxV);
        printf("%c", auxP->Topo->rotation);
    }
}
*/

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
//        else // Proteção contra pilha vazia
//        {
//            No* discard = pop(pFinal);
//            // Opcional: Libere a memória de discard se necessário
//        }
        //}
        //getchar();
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
