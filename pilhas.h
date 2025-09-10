#ifndef PILHAS_H_INCLUDED
#define PILHAS_H_INCLUDED

// ===== Estruturas =====

typedef struct no {
  int pattern[24];   // configuração do cubo
  int cx, cy, cz;    // contadores auxiliares
  int moves;         // profundidade na árvore de busca
  char rotation;     // rotação que levou até este nó
  char status;       // não usado atualmente
  struct no* pai;    // ponteiro para nó pai (para reconstruir caminho)
  struct no* prox;   // ponteiro para próxima célula (pilha encadeada)
} No;

typedef struct pilha {
  No* Topo;
} Pilha;

// ===== Operações =====

// cria pilha vazia
Pilha* CriaPilha(void);

// insere estado no topo
void push(Pilha* p, No* state);

// remove e retorna uma cópia do topo
No* pop(Pilha* p);

// libera memória de toda a pilha
Pilha* libera(Pilha* p);

// imprime rotações subindo pela cadeia de pais
void imprimePilha(Pilha* p);

// imprime versão antiga (varre prox em vez de pai)
void imprimePilhaOld(Pilha* p);

// verifica se a pilha está vazia (retorna 1 se vazia, 0 se não)
int vaziaPilha(Pilha* p);

#endif // PILHAS_H_INCLUDED
