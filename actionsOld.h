#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

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

int dfs(Pilha* p, int state[], int ideal_state[], int *moves)
{
    //No* info;
    push(p, state);

    while (!vaziaPilha(p))
    {
        //printf("%c", p->Topo->status);
        pop(p, state);
        if (memcmp(state, ideal_state, 24 * sizeof(int)) == 0)
        {
            printf("sucesso");
            //printResultado(p);
            return 1;
        }

        if ((*moves) <= 14)
        {
            //printf("%d", p->Topo->cx); //debug
            //system("pause"); //debug
            if (p->Topo->status == 'X')
            {
                //printf("debug");
                p->Topo->status = 'Y';
                push(p, state);
                if (p->Topo->cx < 3)
                {
                rotate_x(state);
                p->Topo->rotation = 'x';
                p->Topo->status = 'X';
                p->Topo->cx++;
                p->Topo->cy = 0;
                p->Topo->cz = 0;
                push(p, state); //arrumar push
                (*moves)++;
                //printf("x\n");
                }
            }
            else if (p->Topo->status == 'Y')
            {
                p->Topo->status = 'Z';
                push(p, state);
                if (p->Topo->cy < 3)
                {
                rotate_y(state);
                p->Topo->rotation = 'y';
                p->Topo->status = 'X';
                p->Topo->cy++;
                p->Topo->cx = 0;
                p->Topo->cz = 0;
                push(p, state);
                (*moves)++;
                //printf("y\n");
                }
            }
            else if (p->Topo->status == 'Z')
            {
                p->Topo->status = 'C';
                push(p, state);
                if (p->Topo->cz < 3)
                {
                rotate_z(state);
                p->Topo->rotation = 'z';
                p->Topo->status = 'X';
                p->Topo->cz++;
                p->Topo->cx = 0;
                p->Topo->cy = 0;
                push(p, state);
                (*moves)++;
                //printf("z\n");
                }
            }
            else
            {
                //pop(p, state);
                (*moves)--;
            }
            //pop(p, state);
            //system("pause");
        }// é possivel fazer sem recursão!
        else
        {
            //pop(p, state);
            (*moves)--;
        }
    }
    return 0;
}


#endif
