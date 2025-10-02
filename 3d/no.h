#ifndef NO_H
#define NO_H

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

//vai gurardr todas as informações que vamos usar para fazer a estrela
typedef struct Node {
    No                *state;    // estado do cubo, pelo menos copia ele(clona ele)
    int                g;        // custo já percorrido (QTM)
    int                h;        // a heurística 
    int                f;        // f = g + h
    unsigned long long key;      //a key que vamos criar para cada posição do vetor patterns
    struct Node       *parent;   // para reconstruir solução
    char               move;     //movimento que gerou este nó
} Node;

#endif