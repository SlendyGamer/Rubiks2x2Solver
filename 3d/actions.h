#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED
#include "pilhas.h"
#include <string.h>

No* rotate_xX(No* state) //ok
{
    int aux;
    // Ciclo 1: 1 → 16 → 12 → 11 → 1
    aux = state->pattern[3];
    state->pattern[3] = state->pattern[19];
    state->pattern[19] = state->pattern[4];
    state->pattern[4] = state->pattern[23];
    state->pattern[23] = aux;

    // Ciclo 2: 17 → 13 → 9 → 2 → 17
    aux = state->pattern[1];
    state->pattern[1] = state->pattern[17];
    state->pattern[17] = state->pattern[6];
    state->pattern[6] = state->pattern[21];
    state->pattern[21] = aux;

    // Ciclo 3: 0 → 15 → 14 → 10 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[15];
    state->pattern[15] = state->pattern[13];
    state->pattern[13] = state->pattern[12];
    state->pattern[12] = aux;

    return state;
}

No* rotate_NOTxX(No* state) //ok
{
    // Ciclo 1: 1 → 16 → 12 → 11 → 1
    int aux = state->pattern[3];
    state->pattern[3] = state->pattern[23];
    state->pattern[23] = state->pattern[4];
    state->pattern[4] = state->pattern[19];
    state->pattern[19] = aux;

    // Ciclo 2: 17 → 2 → 9 → 13 → 17
    aux = state->pattern[1];
    state->pattern[1] = state->pattern[21];
    state->pattern[21] = state->pattern[6];
    state->pattern[6] = state->pattern[17];
    state->pattern[17] = aux;

    // Ciclo 3: 0 → 10 → 14 → 15 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[12];
    state->pattern[12] = state->pattern[13];
    state->pattern[13] = state->pattern[15];
    state->pattern[15] = aux;

    return state;
}

No* rotate_yY(No* state) //ok
{
    int aux;
    // Ciclo 1: 0 → 9 → 8 → 4 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[2];
    state->pattern[2] = state->pattern[10];
    state->pattern[10] = state->pattern[6];
    state->pattern[6] = aux;

    // Ciclo 2: 10 → 6 → 5 → 1 → 10
    aux = state->pattern[15];
    state->pattern[15] = state->pattern[3];
    state->pattern[3] = state->pattern[11];
    state->pattern[11] = state->pattern[7];
    state->pattern[7] = aux;

    // Ciclo 3: 2 → 11 → 7 → 3 → 2
    aux = state->pattern[17];
    state->pattern[17] = state->pattern[16];
    state->pattern[16] = state->pattern[18];
    state->pattern[18] = state->pattern[19];
    state->pattern[19] = aux;

    return state;
}

No* rotate_NOTyY(No* state) //ok
{
    int aux;
    // Ciclo 1: 0 → 9 → 8 → 4 → 0
    aux = state->pattern[14];
    state->pattern[14] = state->pattern[6];
    state->pattern[6] = state->pattern[10];
    state->pattern[10] = state->pattern[2];
    state->pattern[2] = aux;

    // Ciclo 2: 10 → 6 → 5 → 1 → 10
    aux = state->pattern[15];
    state->pattern[15] = state->pattern[7];
    state->pattern[7] = state->pattern[11];
    state->pattern[11] = state->pattern[3];
    state->pattern[3] = aux;

    // Ciclo 3: 2 → 11 → 7 → 3 → 2
    aux = state->pattern[17];
    state->pattern[17] = state->pattern[19];
    state->pattern[19] = state->pattern[18];
    state->pattern[18] = state->pattern[16];
    state->pattern[16] = aux;

    return state;
}

No* rotate_zZ(No* state) //ok
{
    int aux;
    // Ciclo 1: 5 → 19 → 15 → 2 → 5
    aux = state->pattern[11];
    state->pattern[11] = state->pattern[17];
    state->pattern[17] = state->pattern[12];
    state->pattern[12] = state->pattern[22];
    state->pattern[22] = aux;

    // Ciclo 2: 20 → 16 → 0 → 3 → 20
    aux = state->pattern[9];
    state->pattern[9] = state->pattern[16];
    state->pattern[16] = state->pattern[14];
    state->pattern[14] = state->pattern[23];
    state->pattern[23] = aux;

    // Ciclo 3: 4 → 18 → 17 → 1 → 4
    aux = state->pattern[2];
    state->pattern[2] = state->pattern[3];
    state->pattern[3] = state->pattern[1];
    state->pattern[1] = state->pattern[0];
    state->pattern[0] = aux;

    return state;
}

No* rotate_NOTzZ(No* state) //ok
{
    int aux;
    // Ciclo 1: 5 → 19 → 15 → 2 → 5
    aux = state->pattern[11];
    state->pattern[11] = state->pattern[22];
    state->pattern[22] = state->pattern[12];
    state->pattern[12] = state->pattern[17];
    state->pattern[17] = aux;

    // Ciclo 2: 20 → 16 → 0 → 3 → 20
    aux = state->pattern[9];
    state->pattern[9] = state->pattern[23];
    state->pattern[23] = state->pattern[14];
    state->pattern[14] = state->pattern[16];
    state->pattern[16] = aux;

    // Ciclo 3: 4 → 18 → 17 → 1 → 4
    aux = state->pattern[2];
    state->pattern[2] = state->pattern[0];
    state->pattern[0] = state->pattern[1];
    state->pattern[1] = state->pattern[3];
    state->pattern[3] = aux;

    return state;
}

void print_open(int cube[])
{
printf("        %2d %2d\n"
       "        %2d %2d\n"
       "      ---------\n",
cube[18], cube[19],
cube[16], cube[17]); // top

printf("%2d %2d | %2d %2d | %2d %2d | %2d %2d\n"
       "%2d %2d | %2d %2d | %2d %2d | %2d %2d\n",
       cube[10], cube[11], cube[2], cube[3],
       cube[14], cube[15], cube[6], cube[7],
       cube[8], cube[9], cube[0], cube[1],
       cube[12], cube[13], cube[4], cube[5]); // middle

printf("      ---------\n"
       "        %2d %2d\n"
       "        %2d %2d\n",
       cube[22], cube[23],
       cube[20], cube[21]); // bottom
}

void shuffle(No* cube, int max)
{
    int num_moves = rand() % max + 1;
    for (int i = 0; i < num_moves; i++)
    {
        int move = rand() % 3; // 0 = rot_x, 1 = rot_y, 2 = rot_z
        //printf("%d\n", move);
        switch (move)
        {
            case 0:
                cube = rotate_xX(cube);
                printf("rot x\n");
                //print_open(cube);
                break;
            case 1:
                cube = rotate_yY(cube);
                printf("rot y\n");
                //print_open(cube);
                break;
            case 2:
                cube = rotate_zZ(cube);
                printf("rot z\n");
                //print_open(cube);
                break;
        }
    }
    //system("pause");
}

void sucessora(Pilha *p, No* state, char dir)
{
    No* auxNo = malloc(sizeof(No));
    memcpy(auxNo, state, sizeof(No));
    switch(dir)
    {
        case 'x':
            auxNo->cx++;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'x';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_xX(auxNo);
            push(p, auxNo);
            break;
        case 'X': //X'
            auxNo->cx = 0;
            auxNo->cNx++;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'X';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTxX(auxNo);
            push(p, auxNo);
            break;
        case 'y':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy++;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_yY(auxNo);
            push(p, auxNo);
            break;
        case 'Y': //Y'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy++;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'Y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTyY(auxNo);
            push(p, auxNo);
            break;
        case 'z':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz++;
            auxNo->cNz = 0;
            auxNo->rotation = 'z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_zZ(auxNo);
            push(p, auxNo);
            break;
        case 'Z': //Z'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz++;
            auxNo->rotation = 'Z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTzZ(auxNo);
            push(p, auxNo);
            break;
        default:
            perror("variavel dir deve ser 'x/X', 'y/Y' ou 'z/Z'");
            exit(2);
    }
}

int dfs(Pilha *p, No* state, int solution[], Pilha *path)
{
    Pilha* pFinal = CriaPilha();
    state->pai = NULL;
    state->cx = 0;
    state->cy = 0;
    state->cz = 0;
    state->moves = 0;
    state->rotation = '-';
    state->pai = NULL;
    state->prox = NULL;
    print_open(state->pattern);
    push(p, state);
    while(!vaziaPilha(p))
    {
        state = pop(p);
        push(pFinal, state);

        if(memcmp(state->pattern, solution, 24 * sizeof(int)) == 0)
        {
           //printa moves
           printf("sucesso com %d moves\n", state->moves);
           print_open(state->pattern);
           preparePathPilha(pFinal, path);
           imprimePilha(path);
           //imprimePilha(pFinal);
           return 1;
        }

        if (state->moves < 14)
        {
            if (state->cz < 2 && state->cNz == 0)
                sucessora(p, state, 'z');
            if (state->cNz < 1 && state->cz == 0)
                sucessora(p, state, 'Z');

            if (state->cy < 2 && state->cNy == 0)
                sucessora(p, state, 'y');
            if (state->cNy < 1 && state->cy == 0)
                sucessora(p, state, 'Y');

            if (state->cx < 2 && state->cNx == 0)
                sucessora(p, state, 'x'); //soma cx em 1
            if (state->cNx < 1 && state->cx == 0)
                sucessora(p, state, 'X');
        }
        //nao preciso de moves--; em else aqui
    }
    return 0;
}

void sucessoraBFS(Fila *f, No* state, char dir)
{
    No* auxNo = malloc(sizeof(No));
    memcpy(auxNo, state, sizeof(No));
    switch(dir)
    {
        case 'x':
            auxNo->cx++;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'x';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_xX(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'X': //X'
            auxNo->cx = 0;
            auxNo->cNx++;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'X';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTxX(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'y':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy++;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_yY(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'Y': //Y'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy++;
            auxNo->cz = 0;
            auxNo->cNz = 0;
            auxNo->rotation = 'Y';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTyY(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'z':
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz++;
            auxNo->cNz = 0;
            auxNo->rotation = 'z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_zZ(auxNo);
            InsereFila(f, auxNo);
            break;
        case 'Z': //Z'
            auxNo->cx = 0;
            auxNo->cNx = 0;
            auxNo->cy = 0;
            auxNo->cNy = 0;
            auxNo->cz = 0;
            auxNo->cNz++;
            auxNo->rotation = 'Z';
            auxNo->pai = state;
            auxNo->moves = state->moves + 1;
            auxNo = rotate_NOTzZ(auxNo);
            InsereFila(f, auxNo);
            break;
        default:
            perror("variavel dir deve ser 'x/X', 'y/Y' ou 'z/Z'");
            exit(2);
    }
}

int bfs(Fila *f, No* state, int solution[], Pilha *path)
{
    Fila* fFinal = CriaFila();
    state->pai = NULL;
    state->cx = 0;
    state->cy = 0;
    state->cz = 0;
    state->moves = 0;
    state->rotation = '-';
    state->pai = NULL;
    state->prox = NULL;
    print_open(state->pattern);
    InsereFila(f, state);
    while(!VaziaFila(f))
    {
        state = RetiraFila(f);
        //printf("rotation: %c\n",state->rotation);
        InsereFila(fFinal, state);

        if(memcmp(state->pattern, solution, 24 * sizeof(int)) == 0)
        {
           //printa moves
           printf("sucesso com %d moves\n", state->moves);
           print_open(state->pattern);
           preparePathFila(fFinal, path);
           imprimePilha(path);
           //imprimeFila(fFinal);
           return 1;
        }

        if (state->moves < 14)
        {
            if (state->cz < 2 && state->cNz == 0)
                sucessoraBFS(f, state, 'z');
            if (state->cNz < 1 && state->cz == 0)
                sucessoraBFS(f, state, 'Z');

            if (state->cy < 2 && state->cNy == 0)
                sucessoraBFS(f, state, 'y');
            if (state->cNy < 1 && state->cy == 0)
                sucessoraBFS(f, state, 'Y');

            if (state->cx < 2 && state->cNx == 0)
                sucessoraBFS(f, state, 'x'); //soma cx em 1
            if (state->cNx < 1 && state->cx == 0)
                sucessoraBFS(f, state, 'X');
        }
        //nao preciso de moves--; em else aqui
    }
    return 0;
}

static inline unsigned long long state_key(const No *s){
   //recebe um ponteiro pro estado s e retorna um unsigned long long 
    const unsigned char *p = (const unsigned char*)s->pattern;// converte o array(patterns[24]) para um ponteiro de bytes
    //cada estado da um valor diferente
    size_t n = 24 * sizeof(int);
    unsigned long long h = 1469598103934665603ULL;//semente inicial  // FNV-1a offset
    //função hash, pra misturar bytes eproduzir numeros 64-bit

    for (size_t i = 0; i < n; ++i){
        h ^= p[i]; // faz um XOR com o byte atual
        h *= 1099511628211ULL; //um primo especifico para misturar                     // FNV-1a prime
    }
    return h;
}

//a heuristica da esrgela, quando vier o LUT colocar aqui
//ele vai retornar o valor de h, para cada estado que agnt visitar
static inline int get_cost(const No *s){
    (void)s;
    // Por enquanto: h=0 (custo uniforme / BFS por custo 1)

    return 0;
}

//vai gurardr todas as informações que vamos usar para fazer a estrela


//vetor que 
typedef struct { //fila de prioridade, semprepermite obter o menor f rapidamente
    Node  **v; //guarda os nós
    size_t  n, cap; //quantos cabem antes de precisar realloc
} MinHeap;

//cria e inicializa um heap minimo pra A, com um vetor interno que guardara ponteiros para Node. Heap começa vazio e com capacidade cap

//minheap sempre mantem uma prioridade de ordem
static MinHeap* hp_new(size_t cap){ //função vai retornar um minheap vazio
    MinHeap *h = (MinHeap*)calloc(1, sizeof(MinHeap)); //aloca o minheap em si, ja vem zerado
    if (cap != 0) 
        h->cap = cap;
    else 
        h->cap = 2048;

    h->v   = (Node**)malloc(h->cap * sizeof(Node*));  //aloca vetor interno que vai guardar os intens do heap/ vetor de ponteiros para Node
    return h;
}


//comparador de prioridade que o heap vai usar
static inline int better(Node *a, Node *b){
    if (a->f != b->f)  //se f for diferente, retorna o menor f
        return a->f < b->f;  // menor f prime
    return a->g > b->g;                    // se forem iguais, devolver com o meior g
}



static void hp_push(MinHeap *h, Node *x){
    if (h->n == h->cap){ //se o tamanho do heap lotou/ precisa colocar mais espaço para adicionar
        h->cap <<= 1; //multiplica por dois( igual o shift de bits do pannas)
        h->v = (Node**)realloc(h->v, h->cap * sizeof(Node*));//realoca o vetor interno para a nova capacidade
    }
    size_t i = h->n++; //recebe o indice do novo elemnto
    h->v[i] = x; //coloca o novo nó na posição i(fim do array)


    while (i){ //aqui que vai comparar os indedices para colocar a fila em ordem(prioridade)
        size_t p = (i - 1) >> 1; // calcula o indice do pai - lembrando que estamos no fim da fila aqui e ele vai comparando e mudando de lugar até encontrar a ordemcerta
        if (better(h->v[p], h->v[i])) break;//chama funçao better e retorna verdadeiro e a for maior que b/ se for verdadeiro, da um break, pois n vai mudar de lugar
        //se não for verdaderio então o filho é melhor, ent pula
        Node *t = h->v[p]; h->v[p] = h->v[i]; h->v[i] = t;//troca pai com filho, o nó sobe um nivel na arvore
        i = p;//atualiza i para continuar compararndo
    }
}
static Node* hp_pop(MinHeap *h){//remove do heap e retorna o melhor nó e dps restaura a ordem do heap
    if (!h->n) return NULL;//se o heap ta vazio n tem oq retornar

    Node *top = h->v[0];//guarda o elemtno da raiz(o menor numero(f))
    h->v[0] = h->v[--h->n];//decrementa
    size_t i = 0;
    for(;;){ //laço infinitico, só é possivel sair com o break, arriscado, se acontecer algum erro de rodar infinito, procurar aqui primiero, maior probabilidade de erro aqui
        size_t l = 2*i + 1, r = l + 1, m = i; //l filho esquerdo, r filho direito, m o propio pai
        if (l < h->n && !better(h->v[m], h->v[l])) 
            m = l;//v c tem filho esquerdo, chama a função de comparar, se o filho for melhor, coloca ele agora como pai
        if (r < h->n && !better(h->v[m], h->v[r])) m = r;//msm coisa para o filho direito
        if (m == i) break; //se depois de uma verificação o mehor ser o pai, então esta tudo certo
        Node *t = h->v[i]; h->v[i] = h->v[m]; h->v[m] = t; //troca o elemtno de posição
        i = m;//posição onde o elemnto foi parar
    }
    return top;
}

//libera a memoria do heap
static void hp_free(MinHeap *h){
     free(h->v); 
     free(h); 
}


//poda
//open addressing:
//-É/ tipo de um jeito de implementar uma tablea hash usando um único vetor de entrada
typedef struct { unsigned long long key; int g; int used; } VisEnt;//o tab vai ter uma key,used(livre ou ocupado) e g(melhor custo)
typedef struct { VisEnt *tab; size_t cap; } Visited;// tab é o nosso vetor

static Visited* vis_new(size_t cap_pow2){ //cria a tabela de estados visitados
    size_t cap=1; while(cap<cap_pow2) cap<<=1; // ajusta capacidade para potência de 2
    Visited* V = (Visited*)calloc(1,sizeof(*V)); //aloca a estrutura em si
    V->cap = cap;
    V->tab = (VisEnt*)calloc(cap,sizeof(VisEnt)); //aloca o vetor interno, ja vem zerado
    return V;
}
static inline size_t vis_idx(const Visited* V, unsigned long long k){
    return (size_t)(k & (V->cap - 1));
}// calcula qual posicao da tabela de visitados o vetor(tab) deve ir, a partir do hash k
static int vis_get(const Visited* V, unsigned long long k, int* out_g){
    size_t i = vis_idx(V,k), start=i;//verifica se o estado ja foi armazenado e se sim, devolve o melhor custo g
    for(;;){//loop infinito, so sai com o return
        if(!V->tab[i].used) return 0;//slot vazio, a chave nunca foi inserida
        if(V->tab[i].key==k){ if(out_g) *out_g=V->tab[i].g; return 1; }//achou a chave, se o slot contem a mesma chave, ele achou o estado. Verifica o ponteiro out_g, se n for nulo, copia o custo g e retorna 1
        i=(i+1)&(V->cap-1); if(i==start) return 0; //se o slot estiver ocupado com outra chave ele avanca para o proximo indice.
    }// se voltou ao ponto inicial, significa que a tabela inteira foi verificada e a chave nao existe, retornar 0
}
static void vis_put_min(Visited* V, unsigned long long k, int g){ //insere ou atualiza estados na tabela de visitados
    size_t i = vis_idx(V,k), start=i;// guarda start para saber quando deu a volta completa
    for(;;){// loop infinito, so sai com return
        if(!V->tab[i].used){ V->tab[i].used=1; V->tab[i].key=k; V->tab[i].g=g; return; }//verifica se slot esta vazio, insere a nova entrada
        if(V->tab[i].key==k){ if(g < V->tab[i].g) V->tab[i].g=g; return; }//verifica se a chave ja existe, se existir, ele compara o novo custo g com o que estava salvo e se for menor, atualiza
        i=(i+1)&(V->cap-1); if(i==start){ /* cheio: ignorado p/ simplicidade */ return; }// se o slot estiver ocupado ele segue para o prox indice, se deu a volta na funcao desiste.
    }
}
static void vis_free(Visited* V){ free(V->tab); free(V); }// libera a memoria alocada



//criar uma copia independende do estado
static inline No* dup_no(const No *src){ //clona um estado
    No *n = (No*)malloc(sizeof(No));//aloca nova memoria do tamnho de no

    if (!n){ perror("malloc"); 
        exit(1); } // caso a alocação falhar encerra o programa, se não da ruim

    memcpy(n, src, sizeof(No));//copia byte a byte todo o conteudo, isso duplica tudo
    return n;// retorna o porntiero par ao clone
}

//gera um filho aplicando 1 movimento
//dado um estado(pai) e um movimento, ela criaum novo estado estado filho aplicando uma unica rotação
static No* make_child(const No *parent, char mv){//cria um novo estado a partir de parent, aplicando o movimento(x,X,y,Y,z,Z)
    No *c = dup_no(parent);//clona o pai
    // zera contadores auxiliares que você usa no projeto
    memset(&c->cx, 0, 6 * sizeof(int));// zera as flags

    c->rotation = mv; c->pai = NULL; c->prox = NULL;//coloca no nó qual movimetno gerou esse estado
    c->moves = parent->moves + 1; // atualiza a profundidade

    switch(mv){//aqui vai aplicar a rotaçãono estado clonado, usando rotate
        case 'x':  rotate_xX(c);     break;
        case 'X':  rotate_NOTxX(c);  break;
        case 'y':  rotate_yY(c);     break;
        case 'Y':  rotate_NOTyY(c);  break;
        case 'z':  rotate_zZ(c);     break;
        case 'Z':  rotate_NOTzZ(c);  break;
        default: free(c); return NULL;
    }
    return c;//devolve o novo estado rotacionado
}
static int is_solved(const No *s){// ve c o cubo esta resolvido
    for (int i=0;i<24;++i)
        if (s->pattern[i] != i) return 0;//se estuver algum fora de lugar, n esta resolvido
    return 1;
}
//vetor de 24 posições, cada posição é um lugar fixo do cubo



static void print_solution(Node *goal){//reconstruir e imprimir a sequencia de moviemntos para completar o cubo
    int len = 0; //contador para o tamnho

    Node *p = goal;//ponteiro aux para percorrer
    while (p != NULL && p->move != '-') {//sobe até a cadeia de parent até chegar na raiz
        len++;
        p = p->parent;
    }
    char *seq = (char*)malloc((size_t)len + 1); //string para guardar os movimentos
    int i = len - 1;
    for (Node *p = goal; p && p->move != '-'; p = p->parent) seq[i--] = p->move;//cada nó, grava o caracter do movimento
    seq[len] = '\0';// fecha a string

    printf("Solução (QTM, %d passos): %s\n", len, seq);// imprime a sequencia que esta na string
    free(seq);
}

int solve_astar_min(const No *start_in, int solution[], int max_depth_qtm){//recebe o estado inicial e o limite max
    static const char MOVES[6] = {'x','X','y','Y','z','Z'};//o vetor de movimentos

    MinHeap *open   = hp_new(0);//cria o miniheap para a fila de prioridades
    Visited *best_g = vis_new(1u<<22); // cria a tabela visited

    // nó inicial
    No *s0 = dup_no(start_in);//clona o estado inicial
    s0->moves = 0;// zera o contador de moviemtnos

    Node *n0 = (Node*)calloc(1, sizeof(Node));//cria o nó de busca do estado incial
    n0->state  = s0;
    n0->g      = 0; //n andou nada ainda
    n0->h      = get_cost(s0); //heuristica que vai vir do looup table
    n0->f      = n0->g + n0->h;
    n0->key    = state_key(s0);
    n0->parent = NULL;
    n0->move   = '-';

    hp_push(open, n0); //coloca nó incial na minheap
    vis_put_min(best_g, n0->key, 0);   // registra no visited

    //laço principal
    while (open->n){ //enquanto tiver nó na minheap

        Node *u = hp_pop(open);//tira o melhor nó para expandir ele

        //depois que tira o nó de heap vai verificar se ta resolvido
        if (is_solved(u->state)){ //testa se
            print_solution(u);

            //limpa tudo, libera memoria
            while (open->n){ Node *t = hp_pop(open); free(t->state); free(t); }
            hp_free(open); vis_free(best_g);

            // libera cadeia
            for (Node *p = u; p; ){
                Node *prev = p->parent;
                free(p->state);
                if (p != u) free(p);
                p = prev;
            }
            free(u);
            return 1;//retorna que deu certo
        }

        // poda por profundidade máxima (opcional)
        if (max_depth_qtm > 0 && u->g >= max_depth_qtm){
            free(u->state);
            free(u);
            continue;
        }

        // função sucessora: 6 movimentos em QTM(cada moviento custando 1)
        for (int i=0;i<6;++i){//pra cada movinmento que da(os 6:x,X,y,Y...) cria um estado filho
            No *vs = make_child(u->state, MOVES[i]);   // custo da aresta = 1
            unsigned long long kv = state_key(vs);
            int g2 = u->g + 1;//como cada rotação teria o custo 1, coloca ele como g = g+1

            // Poda: se já vimos este estado com g melhor/igual, ignora
            int gold;
            if (vis_get(best_g, kv, &gold) && g2 >= gold){
                free(vs);
                continue;
            }

            int h2 = get_cost(vs);   //vai buscar  heuristica de cada rotação
            int f2 = g2 + h2;// pegar o custo aual

            Node *v = (Node*)calloc(1, sizeof(Node));//nó de busca
            v->state = vs; //aponta para o estado do cubo rotacionado
            v->g = g2; //o custo acumulado
            v->h = h2; //a heuristica de quanto ainda falta
            v->f = f2; // o f
            v->key = kv;// a key, para verficar pra poda
            v->parent = u; //serve para quando enocontar a solução pra reconstruir  a sequencia
            v->move = MOVES[i];// guarda qual movimento levou do pai até o filho

            vis_put_min(best_g, kv, g2);  // registra melhor g
            hp_push(open, v);//coloca o novo nó no minheap
        }

    }

    //se no fim não chegar na solução certa da falha
    hp_free(open); vis_free(best_g);
    return 0;
}


int A_star(No *start_in, int solution[], int max_depth_qtm)
{
    memcpy(start_in->pattern, solution, 24 * sizeof(int));
    start_in->moves = 0;
    start_in->rotation = '-';       
    memset(&start_in->cx, 0, 6 * sizeof(int));
    start_in->pai = NULL;
    start_in->prox = NULL;
    return solve_astar_min(start_in, solution, max_depth_qtm);
}

#endif
