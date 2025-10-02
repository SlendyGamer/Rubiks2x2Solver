#ifndef NO_H
#define NO_H

typedef struct pilha Pilha;

typedef struct no
{
    int pattern[24];
    int cx;
    int cNx;
    int cy;
    int cNy;
    int cz;
    int cNz;
    int moves;
    char rotation;
    char status; //old
    struct no *pai;
    struct no *prox;
}No;

typedef struct search_strategy
{
    void* (*criaStruct)(void);
    void (*insereStruct)(void* dataStruct, No* state); //insere na estrutura
    No* (*retiraStruct)(void* dataStruct); //retira da estrutura
    int (*vaziaStruct)(void* dataStruct); //funcao checa se estrutura esta vazia
    void (*preparePathStruct)(void* dataStruct, Pilha* path); //prepara o path final para o openGl resolver
    void* (*liberaStruct)(void* dataStruct); //libera estrutura
}strat;


/*farei isso na main:
strat dfs = {void push, no* pop, void sucessora, int vaziaPilha }
strat bfs = {void insereFila, no* retiraFila, void sucessoraBFS, int vaziaFila }
*/
#endif