// astar_min.c — A* mínimo para 2×2 (QTM) sem depender da sua HashTable
// Depende de: no.h, actions.h  (NÃO usa "hash.h")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "no.h"
#include "actions.h"


//vou utilizar uma key para cada estado, ele vai servir para ver se dois estados são iguais

//nos estados visitados que vai ter posterioemnte, vou verificar os estados ja feitos

//ou seja, cada estado que visitarmos vai ter uma key diferente, caso o estado seja igual, vai ter a mesma key, pois ele pega a posição do vetor em patterns[24] para fazer a key


//poda
static inline unsigned long long state_key(const No *s){
   //recebe um ponteiro pro estado s e retorna um unsigned long long 
    const unsigned char *p = (const unsigned char*)s->pattern;// converte o array(patterns[24]) para um ponteiro de bytes
    //cada estado da um valor diferente
    size_t n = 24 * sizeof(int);
    unsigned long long h = 1469598103934665603ULL;//semente inicial  // FNV-1a offset
    //função hash, pra misturar bytes eproduzir numeros 64-bit

    for (size_t i = 0; i < n; ++i){
        h ^= p[i];
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
typedef struct Node {
    No                *state;    // estado do cubo, pelo menos copia ele(clona ele)
    int                g;        // custo já percorrido (QTM)
    int                h;        // a heurística 
    int                f;        // f = g + h
    unsigned long long key;      //a key que vamos criar para cada posição do vetor patterns
    struct Node       *parent;   // para reconstruir solução
    char               move;     //movimento que gerou este nó
} Node;


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

static Visited* vis_new(size_t cap_pow2){
    size_t cap=1; while(cap<cap_pow2) cap<<=1;
    Visited* V = (Visited*)calloc(1,sizeof(*V));
    V->cap = cap;
    V->tab = (VisEnt*)calloc(cap,sizeof(VisEnt));
    return V;
}
static inline size_t vis_idx(const Visited* V, unsigned long long k){
    return (size_t)(k & (V->cap - 1));
}
static int vis_get(const Visited* V, unsigned long long k, int* out_g){
    size_t i = vis_idx(V,k), start=i;
    for(;;){
        if(!V->tab[i].used) return 0;
        if(V->tab[i].key==k){ if(out_g) *out_g=V->tab[i].g; return 1; }
        i=(i+1)&(V->cap-1); if(i==start) return 0;
    }
}
static void vis_put_min(Visited* V, unsigned long long k, int g){
    size_t i = vis_idx(V,k), start=i;
    for(;;){
        if(!V->tab[i].used){ V->tab[i].used=1; V->tab[i].key=k; V->tab[i].g=g; return; }
        if(V->tab[i].key==k){ if(g < V->tab[i].g) V->tab[i].g=g; return; }
        i=(i+1)&(V->cap-1); if(i==start){ /* cheio: ignorado p/ simplicidade */ return; }
    }
}
static void vis_free(Visited* V){ free(V->tab); free(V); }



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
        case 'x':  rotate_x(c);     break;
        case 'X':  rotate_NOTx(c);  break;
        case 'y':  rotate_y(c);     break;
        case 'Y':  rotate_NOTy(c);  break;
        case 'z':  rotate_z(c);     break;
        case 'Z':  rotate_NOTz(c);  break;
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

//função principal que vai chamar todo mundo
int solve_astar_min(const No *start_in, int max_depth_qtm){//recebe o estado inicial e o limite max
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
