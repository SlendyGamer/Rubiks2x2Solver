#ifndef PILHAS_H_INCLUDED
#define PILHAS_H_INCLUDED

#include "no.h"   // usa a definição única de No

#ifdef __cplusplus
extern "C" {
#endif

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

// libera memória de toda a pilha (libera todos os No* encadeados e a própria Pilha)
void libera(Pilha* p);

#ifdef __cplusplus
}
#endif

#endif // PILHAS_H_INCLUDED
