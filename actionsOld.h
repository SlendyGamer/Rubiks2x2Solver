#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#define DEBUG_PRINTF(fmt, ...) \
    do { if (debug) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

int debug = 0;

void rotate_x(int state[]) //ok
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
};

void rotate_y(int state[]) //ok
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
};

void rotate_z(int state[]) //ok
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
};

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
};

void shuffle(int cube[], int max)
{
    int num_moves = rand() % max + 1;
    for (int i = 0; i < num_moves; i++)
    {
        int move = rand() % 3; // 0 = rot_x, 1 = rot_y, 2 = rot_z
        //printf("%d\n", move);
        switch (move)
        {
            case 0:
            rotate_x(cube);
            printf("rot x\n");
            //print_open(cube);
            break;
            case 1:
            rotate_y(cube);
            printf("rot y\n");
            //print_open(cube);
            break;
            case 2:
            rotate_z(cube);
            printf("rot z\n");
            //print_open(cube);
            break;
        }
    }
    //system("pause");
};

int dfs(Pilha* p, No* original_state, int ideal_state[], int *moves) //mudar para original_state//
{
    //DEBUG_PRINTF("[Debug] entrou na func\n");
    print_open(original_state->pattern); //mudar para original_state//
    push(p, original_state); //mudar para original_state//
    print_open(p->Topo->pattern);
    No* state = malloc(sizeof(No));//
    while (!vaziaPilha(p))
    {
        //for(int i=0; i<100; i++)
        //{
        DEBUG_PRINTF("[Debug] while iteration\n");
        //printf("%d\n", i);
        memcpy(state, top(p), sizeof(No));// talvez eu esteja alocando muito, so preciso atualizar o ->prox acho //
        //state = top(p);//
        DEBUG_PRINTF("[Debug] moves ate aqui: %d\n", *moves);
        if (memcmp(state->pattern, ideal_state, 24 * sizeof(int)) == 0)
        {
            DEBUG_PRINTF("[Debug] sucesso\n");
            print_open(state->pattern);
            imprimePilha(p);
            printf("\n\n");
            free(state);
            return 1;
        }
        if ((*moves) <= 14) //se der pau, <=
        {
            DEBUG_PRINTF("[Debug] moves next: %d\n", *moves + 1);
            DEBUG_PRINTF("[Debug] status:%c\n", state->status);
            if (state->prox != NULL)
                DEBUG_PRINTF("[Debug] parent status: %c\n", state->prox->status);
            DEBUG_PRINTF("[Debug] cx, cy e cz: x%d y%d z%d\n", state->cx, state->cy, state->cz);

            switch (state->status)
            {
            case 'X':
                if (state->cx < 3)
                {
                rotate_x(state->pattern);          //funcao sucessora begin
                state->cx = p->Topo->cx + 1;
                state->cy = 0;
                state->cz = 0;
                push(p, state); //arrumar push
                updateParent(p->Topo->prox, top(p));
                (*moves)++;                       //funcao sucessora end
                DEBUG_PRINTF("[Debug] rotacao X\n");
                //printf("[Debug] rotacao x\n");
                break;
                }
            state->status = 'Y'; //rotation, nao status
            DEBUG_PRINTF("[Debug] alterado para Y\n");
            /* fallthrough */
            case 'Y':
                if (state->cy < 3)
                {
                rotate_y(state->pattern);       //funcao sucessora begin
                state->cx = 0;
                state->cy = p->Topo->cy + 1;
                state->cz = 0;
                push(p, state);
                updateParent(p->Topo->prox, top(p));
                (*moves)++;                     //funcao sucessora end
                DEBUG_PRINTF("[Debug] rotacao y\n");
                //printf("[Debug] rotacao y\n");
                break;
                }
            state->status = 'Z';
            DEBUG_PRINTF("[Debug] alterado para z\n");
            /* fallthrough */
            case 'Z':
                if (p->Topo->cz < 3)
                {
                rotate_z(state->pattern);                //funcao sucessora begin
                state->cx = 0;
                state->cy = 0;
                state->cz = p->Topo->cz + 1;
                push(p, state);
                updateParent(p->Topo->prox, top(p));
                (*moves)++;                    //funcao sucessora end
                DEBUG_PRINTF("[Debug]rotacao z\n");
                //printf("[Debug] rotacao z\n");
                break;
                }
            state->status = 'C';
            DEBUG_PRINTF("[Debug] alterado para c\n");
            /* fallthrough */
            default:
                DEBUG_PRINTF("[Debug]nenhuma rotacao disponivel, retirando da pilha...\n");
                pop(p); //ARRUMAR SE NECESSARIO
                (*moves)--;
                break;
            }
        }
        else
        {
            DEBUG_PRINTF("[Debug] limite alcancado, removendo da pilha\n");
            //updateParent(p);
            pop(p);
            (*moves)--;
        }
        //print_open(p->Topo->pattern);
        if (debug)
            getchar();
        //}
    //getchar();
    }
    free(state);
    return 0;
}



int dfss(Pilha* p, No* state, int ideal_state[], int *moves) //mudar para original_state//
{
    print_open(state->pattern); //mudar para original_state//
    push(p, state); //mudar para original_state//
    print_open(p->Topo->pattern);
    while (!vaziaPilha(p))
    {
        push(p, state);
        state = top(p);
        //memcpy(state->pattern, p->Topo->pattern, 24 * sizeof(int));// talvez eu esteja alocando muito, so preciso atualizar o ->prox acho //
        if (memcmp(state->pattern, ideal_state, 24 * sizeof(int)) == 0)
        {
            print_open(state->pattern);
            imprimePilha(p);
            printf("\n\n");
            free(state);
            return 1;
        }
        if ((*moves) < 14) //se der pau, <=
        {
            switch (state->status)
            {
            case 'X':
                if (state->cx < 3)
                {
                rotate_x(state->pattern);          //funcao sucessora begin
                state->cx = p->Topo->cx + 1;
                state->cy = 0;
                state->cz = 0;
                //push(p, state); //arrumar push
                updateParent(p->Topo->prox, top(p));
                (*moves)++;                       //funcao sucessora end
                break;
                }
            state->status = 'Y'; //rotation, nao status
            /* fallthrough */
            case 'Y':
                if (state->cy < 3)
                {
                rotate_y(state->pattern);       //funcao sucessora begin
                state->cx = 0;
                state->cy = p->Topo->cy + 1;
                state->cz = 0;
                //push(p, state);
                updateParent(p->Topo->prox, top(p));
                (*moves)++;                     //funcao sucessora end
                break;
                }
            state->status = 'Z';
            /* fallthrough */
            case 'Z':
                if (p->Topo->cz < 3)
                {
                rotate_z(state->pattern);                //funcao sucessora begin
                state->cx = 0;
                state->cy = 0;
                state->cz = p->Topo->cz + 1;
                //push(p, state);
                updateParent(p->Topo->prox, top(p));
                (*moves)++;                    //funcao sucessora end
                break;
                }
            state->status = 'C';
            /* fallthrough */
            default:
                pop(p); //ARRUMAR SE NECESSARIO
                (*moves)--;
                break;
            }
        }
        else
        {
            pop(p);
            (*moves)--;
        }
    }
    free(state);
    return 0;
}


#endif
