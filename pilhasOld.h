#ifndef PILHAS_H_INCLUDED
#define PILHAS_H_INCLUDED

/* FUN��ES DE MANIPULA��O DE PILHA

Pilha* CriaPilha ()     CRIA A PILHA

No* ins_ini (No* t, int a)  AUXILIAR DA INSER��O

void push (Pilha* p, int v) INSER��O

No* ret_ini (No* l)         AUXILIAR DA REMO��O

int pop (Pilha* p)          REMOVE RETORNANDO O VALOR QUE FOI REMOVIDO

void libera (Pilha* p)      LIBERA A PILHA

void imprime (Pilha* p)     IMPRIMA A PILHA

int vaziaPilha(Pilha *p)	    VERIFICA SE A PILHA EST� VAZIA, RETORNA 1

*/
void print_open(int cube[]);

typedef struct no
{
    int pattern[24];
    int cx;
    int cy;
    int cz;
    char rotation;
    char status;
    struct no *prox;
}No;

typedef struct pilha
{
   No *Topo;
}Pilha;

Pilha* CriaPilha (void)
{
     Pilha *p;
     p=(Pilha*)malloc(sizeof(Pilha));
     p->Topo = NULL;
   return p;
};


No* ret_ini (No* l)
{
    No* p = l->prox;
    free(l);
    return p;
};



No* ins_ini (No* t, No* state)
{
No* aux = (No*) malloc(sizeof(No));
if (t == NULL)
{
    aux->cx = 0;
    aux->cy = 0;
    aux->cz = 0;
    aux->rotation = '-';
    memcpy(aux->pattern, state->pattern, 24 * sizeof(int));
    
}
else
{
    memcpy(aux, state, sizeof(No)); //talvez nao seja necessario copiar tudo
    //printf("[Debug] status do topo: %c\n", t->status);
    aux->rotation = aux->status;
    //printf("[Debug] status do topo apos: %c\n", aux->rotation);
}
aux->status = 'X';
aux->prox = t;
return aux;
};
                
void push(Pilha* p, No* state)
{
    p->Topo = ins_ini(p->Topo, state);
}

void updateParent(No* pai, No* filho)
{
    switch (filho->rotation)
    {
        case 'X':
        pai->status = 'Y';
            break;
        case 'Y':
        pai->status = 'Z';
            break;
        case 'Z':
        pai->status = 'C';
            break;
        default:
            perror("updateparent error");
            break;
    }
}

No* pop (Pilha* p)
{
    if (p->Topo==NULL)
    {
        printf("Pilha vazia!!\n");
        exit(1); /* aborta programa */
    }

    No* dest = malloc(sizeof(No));
    memcpy(dest, p->Topo, sizeof(No));
    p->Topo = ret_ini(p->Topo);
    return dest;
};

No* top(Pilha* p)
{
    if (p->Topo==NULL)
    {
        printf("Pilha vazia!!\n");
        exit(1); /* aborta programa */
    }
    
    return p->Topo;
};

Pilha * libera (Pilha* p)
{
    No *q = p->Topo;
    while (q!=NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return(NULL);
};

int vaziaPilha(Pilha *p)
{
    if (p->Topo==NULL)
    {
        return 1; //pilha vazia
    }
    return 0;
}

void imprimePilha(Pilha *p)
{
    No* q;
    if(!p)
    {
        printf("\n\n\tPILHA VAZIA!!!!\n\n");
    }
    else
    {
        printf("\n\n\tImpress�o da Pilha: \n");
        for (q=p->Topo; q!=NULL; q=q->prox)
        {
            printf("cx: %d\n",q->cx);
            printf("cy: %d\n",q->cy);
            printf("cz: %d\n",q->cz);
            printf("status: %c\n",q->status);
            printf("rotation: %c\n",q->rotation);
            print_open(q->pattern);
            printf("\n\n\n");
        }
        printf("\n\n");
    }

};




#endif // PILHAS_H_INCLUDED
