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

#endif