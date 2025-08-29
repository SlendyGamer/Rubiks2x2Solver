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



No* ins_ini (No* t, int state[])
{
No* aux = (No*) malloc(sizeof(No));
memcpy(aux, state, sizeof(No));
if (t == NULL)
{
    aux->cx = 0;
    aux->cy = 0;
    aux->cz = 0;
    aux->rotation = '-';
    aux->status = 'X';

}
else
{
    aux->cx = t->cx;
    aux->cy = t->cy;
    aux->cz = t->cz;
    aux->status = t->status;
    aux->rotation = t->rotation;
}
aux->prox = t;
return aux;
};
                
void push(Pilha* p, int state[])
{
    p->Topo = ins_ini(p->Topo, state);
}

void pop(Pilha* p, int s[])
{
    if (p->Topo==NULL)
    {
        printf("Pilha vazia!!\n");
        exit(1); /* aborta programa */
    }

    memcpy(s, p->Topo->pattern, 24 * sizeof(int));
    p->Topo = ret_ini(p->Topo);
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
