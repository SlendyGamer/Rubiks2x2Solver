#ifndef PILHAS_H_INCLUDED
#define PILHAS_H_INCLUDED

#include "no.h"   // usa a definição única de No

// ===== Estruturas =====
typedef struct pilha {
  No* Topo;
} Pilha;

// ===== Operações =====

// cria pilha vazia
Pilha* CriaPilha(void);

// insere estado no topo (não faz cópia do No*, empilha o ponteiro)
void push(Pilha* p, No* state);

// remove e retorna o topo (retorna o próprio No* empilhado; quem chama decide dar free)
No* pop(Pilha* p);

// verifica se a pilha está vazia (1 se vazia, 0 se não)
int vaziaPilha(Pilha* p);

// imprime rotações ou caminho (implementação livre)
void imprimePilha(Pilha* p);

// imprime versão antiga (se não usar, pode ser stub)
void imprimePilhaOld(Pilha* p);



void print_open(int cube[]);

#include "no.h"


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

No* ins_ini(No* topo, No* state)
{
    if (topo == NULL)
    {
        state->prox = NULL;
    }
    else
    {
        state->prox = topo;
    }
        return state;
}

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

void imprimePilha(Pilha *p)
{
    No* q = malloc(sizeof(No));
    q = p->Topo;
    int i = -1;
while(q != NULL){
        i++;
            //printf("cx: %d\n",q->cx);
            //printf("cy: %d\n",q->cy);
            //printf("cz: %d\n",q->cz);
            //printf("status: %c\n",q->status);
            printf("rotation: %c\n",q->rotation);
            //print_open(q->pattern);
            //printf("\n\n\n");
    q = q->pai;
}
printf("completed REALLY %d moves\n", i);
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
