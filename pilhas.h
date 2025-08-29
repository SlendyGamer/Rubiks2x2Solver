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

typedef struct no
{
    int pattern[24];
    int cx;
    int cy;
    int cz;
    int moves;
    char rotation;
    char status; //old
    struct no *pai;
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

No* ins_ini (No* t, No* state)
{
    No* aux = (No*) malloc(sizeof(No));
    memcpy(aux, state, sizeof(No));
    if (t == NULL)
    {
        aux->cx = 0;
        aux->cy = 0;
        aux->cz = 0;
        aux->moves = 0;
        aux->pai = NULL;
        aux->rotation = '-';
    }
    else
    {
        aux->cx = state->cx;
        aux->cy = state->cy;
        aux->cz = state->cz;
        aux->moves = state->moves + 1;
        //aux->pai = state;
        aux->rotation = state->rotation;
    }
    aux->prox = t;
    return aux;
};

void push (Pilha* p, No* state)
{
    p->Topo = ins_ini(p->Topo, state);
};

No* ret_ini (No* l)
{
    No* p = l->prox;
    free(l);
    return p;
};

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

void imprimePilha(Pilha *p)
{
    No* q = malloc(sizeof(No));
    q = p->Topo;
    /*
    if(!p)
    {
        printf("\n\n\tPILHA VAZIA!!!!\n\n");
    }
    else
    {
        printf("\n\n\tImpress�o da Pilha: ");
        for (q=p->Topo; q!=NULL; q=q->prox)
        {
            printf(" %c",q->rotation);
        }
        printf("\n\n");
    }*/

while(q != NULL){
    printf("%c ", q->rotation);
    q = q->pai;
}
};

                    void imprimePilhaOld(Pilha *p)
                    {
                        No* q;
                        if(!p)
                        {
                            printf("\n\n\tPILHA VAZIA!!!!\n\n");
                        }
                        else
                        {
                            printf("\n\n\tImpress�o da Pilha: ");
                            for (q=p->Topo; q!=NULL; q=q->prox)
                            {
                                printf(" %c",q->rotation);
                            }
                            printf("\n\n");
                        }

                    };

int vaziaPilha(Pilha *p)
{
    if (p->Topo==NULL)
    {
        return 1; //pilha vazia
    }
    return 0;
}



#endif // PILHAS_H_INCLUDED
