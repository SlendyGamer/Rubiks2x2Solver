#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhas.h"

// cria pilha vazia
Pilha* CriaPilha (void)
{
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    p->Topo = NULL;
    return p;
}

// insere no início (interno)
static No* ins_ini (No* topo, No* state)
{
    No* novo = (No*) malloc(sizeof(No));
    memcpy(novo, state, sizeof(No));

    if (topo == NULL) {
        // nó raiz da busca
        novo->cx = novo->cy = novo->cz = 0;
        novo->moves = 0;
        novo->pai = NULL;
        novo->rotation = '-';
    } else {
        // nó derivado (push comum)
        novo->cx = state->cx;
        novo->cy = state->cy;
        novo->cz = state->cz;
        novo->moves = state->moves + 1;
        novo->rotation = state->rotation;
        // novo->pai é setado fora pelas buscas (quando necessário)
    }

    novo->prox = topo;
    return novo;
}

// push
void push (Pilha* p, No* state)
{
    p->Topo = ins_ini(p->Topo, state);
}

// remove início (interno)
static No* ret_ini (No* topo)
{
    No* prox = topo->prox;
    free(topo);
    return prox;
}

// pop (copia o topo para um novo bloco e o remove da pilha)
No* pop (Pilha* p)
{
    if (p->Topo == NULL) {
        printf("Pilha vazia!!\n");
        exit(1);
    }

    No* dest = (No*)malloc(sizeof(No));
    memcpy(dest, p->Topo, sizeof(No));
    p->Topo = ret_ini(p->Topo);
    return dest;
}

// libera toda a pilha
Pilha * libera (Pilha* p)
{
    No *q = p->Topo;
    while (q != NULL)
    {
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(p);
    return NULL;
}

// imprime rotações subindo pela cadeia de pais (para mostrar caminho)
void imprimePilha(Pilha *p)
{
    No* q = p->Topo;   // não precisa malloc aqui
    while(q != NULL){
        printf("%c ", q->rotation);
        q = q->pai;
    }
}

// checa se está vazia
int vaziaPilha(Pilha *p)
{
    return p->Topo == NULL;
}
