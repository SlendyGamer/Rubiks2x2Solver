#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhas.h"
#include "actions.h"

// fila
typedef struct filaNode { //cada celula da fila guarda um ponteiro para no
    No* value;
    struct filaNode *next;
} filaNode;

typedef struct {//guarda inicio fim
    filaNode *inicio, *fim;
    int size;
} fila;

static fila* fila_create(void){  //cira a fila vazia
    fila *q = (fila*)malloc(sizeof(fila));
    q->inicio = q->fim = NULL; q->size = 0;
    return q;
}
static int fila_empty(fila *q)
    { return q->size == 0; }//retorno 1 se a fila estivervazia


static void fila_push(fila *q, No* v){//insere um no nofim da fila
    filaNode *n = (filaNode*)malloc(sizeof(filaNode));
    n->value = v; n->next = NULL;
    if (!q->fim) q->inicio = q->fim = n;
    else { q->fim->next = n; q->fim = n; }
    q->size++;
}
static No* fila_pop(fila *q){ //remove e devolve o no do incino da fila
    if (!q->inicio) return NULL;
    filaNode *n = q->inicio; No* v = n->value;
    q->inicio = n->next; if(!q->inicio) q->fim = NULL;
    free(n); q->size--;
    return v;
}
// ---------------------------------

// (modelo idêntico à sua 'sucessora', mas empilhando na fila de BFS)
static void enqueue_successor(fila *frontier, No* parentState, char move){
    No* child = (No*)malloc(sizeof(No));
    memcpy(child, parentState, sizeof(No));

    // metadados do nó
    child->pai   = parentState;
    child->moves = parentState->moves + 1;
    child->rotation = move;

    // zera contadores auxiliares (não são usados no BFS)
    child->cx = child->cy = child->cz = 0;

    // aplica ação
    switch (move){
        case 'x': rotate_x(child); break;
        case 'y': rotate_y(child); break;
        case 'z': rotate_z(child); break;
        default:
            perror("move inválido em enqueue_successor");
            exit(2);
    }

    fila_push(frontier, child);
}

static void print_solution_path(No* goalNode){
    //aqui ele vai mostrar o caminho
    //guarda as rotações em seq e imprime de tras pra frente
    int steps = 0;
    for (No* p = goalNode; p; p = p->pai) if (p->rotation != '-') steps++;

    char *seq = (char*)malloc(steps);
    int i = 0;
    for (No* p = goalNode; p; p = p->pai)
        if (p->rotation != '-') seq[i++] = p->rotation;

    printf("Solução (%d passos): ", steps);
    for (int k = steps - 1; k >= 0; k--) printf("%c ", seq[k]);
    puts("");
    free(seq);
}

int bfs(No* initialState, const int goalPattern[24]){
  //limite max para a solução do cubo
    const int MAX_DEPTH = 14;

    // inicia no inciail
    initialState->pai = NULL;
    initialState->moves = 0;
    initialState->rotation = '-';
    initialState->cx = initialState->cy = initialState->cz = 0;

    // fronteira BFS
    fila *frontier = fila_create();
    fila_push(frontier, initialState);

    int visitedCount = 0;

    while (!fila_empty(frontier)){
        No* current = fila_pop(frontier);
        visitedCount++;

        // checagem de objetivo
        if (memcmp(current->pattern, goalPattern, 24 * sizeof(int)) == 0){
            printf("Estados visitados: %d\n", visitedCount);
            printf("Profundidade (moves): %d\n", current->moves);
            print_solution_path(current);
            return 1;
        }

        //limite de profundidade
        if (current->moves >= MAX_DEPTH) {
            
            continue;
        }

        // gera sucessores

        enqueue_successor(frontier, current, 'z');
        enqueue_successor(frontier, current, 'y');
        enqueue_successor(frontier, current, 'x');
    }

    // sem solução dentro do limite
    return 0;
}
