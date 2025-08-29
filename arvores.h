#ifndef ARVORES_H_INCLUDED
#define ARVORES_H_INCLUDED

#define NE 0
#define BE 1
#define E  2
 typedef struct NoArvore
 {
     int v[24];
     int state;
     struct NoArvore *rotx;
     struct NoArvore *roty;
     struct NoArvore *rotz;
 }NoArv;


 typedef struct Arvore
 {
     NoArv *raiz;
 }Arv;

 Arv* arv_Criar() //cria arvore
 {
        Arv *aux;
        aux = (Arv*)malloc(sizeof(Arv));
        aux->raiz = NULL;
        return aux;
 }

 void removeCR(char charVet[])                                  //remove algo
 {
     charVet[strcspn(charVet, "\r\n")] = 0;
 }

 int arv_Vazia(Arv* A) //checa arvore vazia
 {
     if (A->raiz == NULL)
     {
         return 1;
     }
     return 0;
 }

 NoArv* insereAux(NoArv *no, int estado[], int rot)
 {
     int end_flag;
     NoArv *pai;
     NoArv *novo = (NoArv*)malloc(sizeof(NoArv));

     //novo->v = estado[] //arrumar para receber estado apos rotacao

     novo->rotx = NULL;
     novo->roty = NULL;
     novo->rotz = NULL;
     novo->state = NE;    //TALVEZ SEJA DESNECESSARIO
     if (no == NULL)
     {
         return novo;
     }
     else
     {
         pai = no;
         end_flag = 0;
         while (end_flag != 1)
         {
             if (rot == 0)
             {
                 if (pai->rotx != NULL && pai->rotx->state != E) //conferir dps state se esta certo essa comparação ou usar == NE
                 {
                     pai = pai->rotx;
                 }
                 else
                 {
                     pai->rotx = novo;
                     end_flag = 1;
                 }
             }
             else if(rot == 1)
             {
                 if (pai->roty != NULL && pai->roty->state != E) //conferir dps state se esta certo essa comparação ou usar == NE
                 {
                     pai = pai->roty;
                 }
                 else
                 {
                     pai->roty = novo;
                     end_flag = 1;
                 }
             }
             else if(rot == 2)
             {
                if (pai->rotz != NULL && pai->rotz->state != E) //conferir dps state se esta certo essa comparação ou usar == NE
                 {
                     pai = pai->rotz;
                 }
                 else
                 {
                     pai->rotz = novo;
                     end_flag = 1;
                 }
             }
             else
             {
                 printf("\n\tNós ja explorados! ignorando...");
                 end_flag = 1;
             }
         }
     }
     return no;
 }

 void arv_Inserir(Arv *A, int estado[], int rot)
 {
     A->raiz = insereAux(A->raiz, &estado, rot);
 }

/*NoArv* removeAux(NoArv *pai, int matricula)
 {
     if (pai == NULL)
     {
         printf("\n\tNão existe matrícula %d na árvore!\n", matricula);
     }
     else
     {
        if (matricula > pai->dado.matricula)
        {
            pai->dir = removeAux(pai->dir, matricula);
        }
        else
        {
            if (matricula < pai->dado.matricula)
            {
                pai->esq = removeAux(pai->esq, matricula);
            }
            else
            {
                if (pai->dir == NULL && pai->esq == NULL)
                {
                     free(pai);
                     pai = NULL;
                     printf("\n\tMatrícula %d removida da árvore!\n", matricula);
                }
                else
                {
                    if (pai->esq == NULL)
                    {
                        NoArv *aux = pai;
                        pai = pai->dir;
                        free(aux);
                        printf("\n\tMatrícula %d removida da árvore!\n", matricula);
                    }
                    else
                    {
                        if (pai->dir == NULL)
                        {
                            NoArv *aux = pai;
                            pai = pai->esq;
                            free(aux);
                            printf("\n\tMatrícula %d removida da árvore!\n", matricula);
                        }
                        else
                        {
                            NoArv *aux;
                            aux = pai->esq;
                            while (aux->dir != NULL)
                            {
                                aux = aux->dir;
                            }
                            pai->dado.matricula = aux->dado.matricula;
                            aux->dado.matricula = matricula;
                            pai->esq = removeAux(pai->esq, matricula);
                        }
                    }
                }
            }
        }
    }
    return pai;
 }*/ //editar para fazer remoção de nos ja explorados, assim evitando uso de memoria a toa
 
/*Arv* arv_Remover(Arv *A, int matricula)
 {
     NoArv *aux = A->raiz;
     if (aux->dado.matricula == matricula && (aux->dir == NULL && aux ->esq == NULL))
     {
         free(aux);
         A->raiz=NULL;
         return A;
     }
     A->raiz = removeAux(A->raiz, matricula);
     return A;
 }*/ //editar para fazer remoção de nos ja explorados, assim evitando uso de memoria a toa

/* NoArv* buscaArv(NoArv* pai, int matricula) {
     if (pai == NULL) {
         printf("\nNao existe matricula %d na arvore!\n", matricula);
         return NULL;
     }

     if (matricula > pai->dado.matricula)
     {
         return buscaArv(pai->dir, matricula);
     }
     else
     {
        if (matricula < pai->dado.matricula)
        {
            return buscaArv(pai->esq, matricula);
        }
        else
        {
             return pai;
        }
    }
 }*/

/* NoArv* editaBuscaArv(NoArv* pai, int matricula) {
     if (pai == NULL) {
         printf("\nNao existe matricula %d na arvore!\n", matricula);
         return NULL;
     }
     if (matricula > pai->dado.matricula)
     {
         return editaBuscaArv(pai->dir, matricula);
     }
     else
     {
        if (matricula < pai->dado.matricula)
        {
            return editaBuscaArv(pai->esq, matricula);
        }
        else
        {
             int select;
        do
        {
            select = -1;
            printf("\n\to que deseja editar?\n");
            printf("\t1 - Nome\n");
            printf("\t2 - Idade\n");
            printf("\t3 - Cargo\n");
            printf("\t4 - Salario\n");
            printf("\n\\:\t");
            fflush(stdin);
            scanf("%d", &select);

            switch(select)
            {
                case 1:
                    printf("\n\tNovo nome - AVISO: substituirá %-38s\n", pai->dado.nome);
                    setNome(pai->dado.nome);
                    break;
                case 2:
                    printf("\n\tNova idade de %-38s\n", pai->dado.nome);
                    pai->dado.idade = setIdade();
                    break;
                case 3:
                    printf("\n\tNovo cargo de %-38s\n", pai->dado.nome);
                    setCargo(pai->dado.cargo);
                    break;
                case 4:
                    printf("\n\tNovo salário de %-38s\n", pai->dado.nome);
                    pai->dado.salario = setSalario();
                    break;
                default:
                    printf("\n\tErro\n");
                    break;
            }
        } while (select <1 || select > 4);
        return pai;
        }
    }
 }
*/


 /*void editaArv(Arv* pai, int matricula)
 {
    if (pai != NULL)
    {
        editaBuscaArv(pai->raiz, matricula);
    }

 }*/


/*void imprimeInfo(NoArv* pai)
{
    printf("\t%04d\t  | %-38s| %d     | %-23s | %.2f\n", pai->dado.matricula, pai->dado.nome, pai->dado.idade, pai->dado.cargo, pai->dado.salario);

}*/

/* void ImprimeAuxPre(NoArv* nA)
 {
    if (nA != NULL)
     {
        imprimeInfo(nA);
        ImprimeAuxPre(nA->dir);
        ImprimeAuxPre(nA->esq);
     }
 }*/

/* void ImprimeAuxIn(NoArv* nA)
 {
    if (nA != NULL)
     {
        ImprimeAuxIn(nA->dir);
        imprimeInfo(nA);
        ImprimeAuxIn(nA->esq);
     }
 }*/

/* void ImprimeAuxPos(NoArv* nA)
 {
    if (nA != NULL)
     {
        ImprimeAuxPos(nA->dir);
        ImprimeAuxPos(nA->esq);
        imprimeInfo(nA);
     }
 }*/

/* void ImprimeArv(Arv *A, int type)
 {
     if (!arv_Vazia(A))
     {
         NoArv *nA = A->raiz;
         printf("\n\tMatrícula | Nome\t\t\t\t  | Idade  | Cargo\t\t     | Salário\n");
         printf("\t----------------------------------------------------------------------------------------------\n");
         switch(type)
         {
         case 1: //pre

             imprimeInfo(nA);
             ImprimeAuxPre(nA->dir);
             ImprimeAuxPre(nA->esq);
             break;
         case 2: //in
             ImprimeAuxIn(nA->dir);
             imprimeInfo(nA);
             ImprimeAuxIn(nA->esq);
             break;
         case 3: //pos
             ImprimeAuxPos(nA->dir);
             ImprimeAuxPos(nA->esq);
             imprimeInfo(nA);
             break;
         default:
             break;
         }
     }
 }*/

 NoArv* liberaAux(NoArv* nA)
 {
    if (nA != NULL)
     {
         liberaAux(nA->rotx);
         liberaAux(nA->roty);
         liberaAux(nA->rotz);
         free(nA);
         printf("#"); //para debug
     }
     return NULL;
 }

 Arv* arv_Liberar(Arv *A, int n)
 {
     if (!arv_Vazia(A))
    {
        A->raiz = liberaAux(A->raiz);
        printf("\n\tÁrvore liberada!\n");
    }
     return A;

 }

#endif // ARVORES_H_INCLUDED
