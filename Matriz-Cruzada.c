#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXCOL 10
#define MAXLIN 10

typedef struct S {
    int value;
    int l;
    int c;
    struct S* proxL;
    struct S* proxC;
}NO;

typedef struct {
    NO* col [MAXCOL];
    NO* lin [MAXLIN];
}MATRIZ;

bool comparaColunas (MATRIZ* m, int i, int j){
    NO* aux1 = m->col[j];
    NO* aux2 = m->col[j];
    while (aux1 && aux2){
        if (aux1->value != aux2->value || aux1->c != aux2->c || aux1->l != aux2->l)
            return false;
        aux1 = aux1->proxC;
        aux2 = aux2->proxC;
    }
    if (aux1 || aux2)
        return false;
    return true;
}

bool comparaLinhas (MATRIZ* m, int i, int j){
    NO* aux1 = m->lin[i];
    NO* aux2 = m->lin[j];
    while (aux1 && aux2){
        if (aux1->value != aux2->value || aux1->c != aux2->c || aux1->l != aux2->l)
            return false;
        aux1 = aux1->proxL;
        aux2 = aux2->proxL;
    }
    if (aux1 || aux2)
        return false;
    return true;
}

void inicializa (MATRIZ* m){
    int i = 0;
    while (i < MAXLIN){
        m->col[i] = NULL;
        i++;
    }
    i = 0;
    while (i < MAXCOL){
        m->lin[i] = NULL;
        i++;
    }
}

void cria (int n[MAXLIN][MAXCOL], MATRIZ* m){
    int i = 0;
    int j = 0;
    NO* aux;
    NO* ant;
    NO* atual;
    while (i < MAXLIN){
        while (j < MAXCOL){
            if (n[i][j] != 0){
                NO* novo = (NO*) malloc (sizeof(NO));
                novo->value = n[i][j];
                novo->l = i;
                novo->c = j;
                novo->proxC = NULL;
                novo->proxL = NULL;
                if (m->lin[i] == NULL){
                    m->lin[i] = novo;
                }else {
                    aux->proxL = novo;
                }
                aux = novo;
                if (m->col[j] == NULL){
                    m->col[j] = novo;
                }else {
                    ant = NULL;
                    atual = m->col[j];
                    while (atual){
                        ant = atual;
                        atual = atual->proxC;
                    }
                    ant->proxC = novo;
                }
            }
            j++;
        }
        aux = NULL;
        i++;
        j = 0;
    }
}

NO* busca (MATRIZ * m, int i, int j, NO** acima, NO** esq){
    NO* p = m->lin[i];
    * esq = NULL;
    * acima = NULL;
    while (p){
        if (p->c >= j)
            break;
        *esq = p;
        p = p->proxC;
    }
    NO* resp = p;
    if (p && p->c != j)
        resp = NULL;
    p = m->col[j];
    while (p != NULL){
        if (p->l >= i)
            break;
        *acima = p;
        p = p->proxL;
    }
    return resp;
}

void setar (MATRIZ * m, int i, int j, int k){
    NO* acima = NULL;
    NO* esq = NULL;
    NO* atual = busca(m, i, j, &acima, &esq);
    if (k == 0 && !atual){
        return;
    }else if (k != 0 && atual){
        atual->value = k;
        return;
    }else if (k == 0 && atual){
        if (esq)
            esq->proxL = atual->proxL;
        else
            m->lin[i] = atual->proxL;
        if (acima)
            acima->proxC = atual->proxC;
        else
            m->col[j] = atual->proxC;
        free(atual);
    }else {
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->l = i;
        novo->c = j;
        novo->value = k;
        if (esq){
            novo->proxL = esq->proxL;
            esq->proxL = novo;
        }else {
            if (m->lin[i])
                novo->proxL = m->lin[i];
            else
                novo->proxL = NULL;
            m->lin[i] = novo;
        }
        if (acima){
            novo->proxC = acima->proxC;
            esq->proxC = novo;
        }else {
            if (m->col[j])
                novo->proxC = m->col[j];
            else
                novo->proxC = NULL;
            m->col[j] = novo;
        }
    }
}

void zerarColuna (MATRIZ * m, int n){
    int i = 0;
    while (i < MAXLIN){
        NO* aux = m->lin[i];
        NO* ant = NULL;
        while (aux){
            if (aux->c >= n)
                break;
            ant = aux;
            aux = aux->proxL;
        }
        if (aux && aux->c == n){
            if (ant)
                ant->proxL = aux->proxL;
            else
                m->lin[i] = aux->proxL;
            free(aux);
        }
        i++;
    }
    m->col[n] = NULL;
}

void zerarLinha (MATRIZ * m, int n){
    int i = 0;
    while (i < MAXCOL){
        NO* aux = m->col[i];
        NO* ant = NULL;
        while (aux){
            if (aux->l >= n)
                break;
            ant = aux;
            aux = aux->proxC;
        }
        if (aux && aux->l == n){
            if (ant)
                ant->proxC = aux->proxC;
            else
                m->col[i] = aux->proxC;
            free(aux);
        }
        i++;
    }
    m->lin[n] = NULL;
}

void modificarColuna (MATRIZ* m, int i, int k){
    int j = 0;
    NO* antC = NULL;
    while (j < MAXLIN){
        NO* antL = NULL;
        NO* aux = m->lin[j];
        while (aux){
            if (aux->c >= i)
                break;
            antL = aux;
            aux = aux->proxL;
        }
        if (!aux || aux->c != i){
            NO* novo = (NO*) malloc(sizeof(NO));
            novo->l = j;
            novo->c = i;
            novo->value = k;
            novo->proxL = aux;
            if (antL)
                antL->proxL = novo;
            else
                m->lin[j] = novo;
            if (antC)
                antC->proxC = novo;
            else
                m->col[i] = novo;
            antC = novo;
            novo->proxC = NULL;
        }else
            aux->value = k;
        j++;
    }
}

void modificarLinha (MATRIZ* m, int i, int k){
    int j = 0;
    NO* antL = NULL;
    while (j < MAXCOL){
        NO* antC = NULL;
        NO* aux = m->col[j];
        while (aux){
            if (aux->c >= i)
                break;
            antC = aux;
            aux = aux->proxC;
        }
        if (!aux || aux->l != i){
            NO* novo = (NO*) malloc(sizeof(NO));
            novo->c = j;
            novo->l = i;
            novo->value = k;
            novo->proxC = aux;
            if (antC)
                antC->proxC = novo;
            else
                m->col[j] = novo;
            if (antL)
                antL->proxL = novo;
            else
                m->lin[i] = novo;
            antL = novo;
            novo->proxL = NULL;
        }else
            aux->value = k;
        j++;
    }
}

int colunaZeradas (MATRIZ * m){
    int resp = 0;
    int i = 0;
    while (i < MAXCOL){
        if (!m->col[i])
            resp++;
        i++;
    }
    return resp;
}

int linhasZeradas (MATRIZ * m){
    int resp = 0;
    int i = 0;
    while (i < MAXCOL){
        if (!m->lin[i])
            resp++;
        i++;
    }
    return resp;
}

int zerosNaDiagonalPrincipal (MATRIZ * m){
    int resp = 0;
    int i = 0;
    while (i < MAXLIN){
        NO* aux = m->lin[i];
        while (aux){
            if (aux->c >= i)
                break;
            aux = aux->proxL;
        }
        if (!aux || aux->c > i)
            resp++;
        i++;
    }
    return resp;
}

int valor (MATRIZ * m, int i, int j){
    NO* aux = m->lin[i];
    while (aux){
        if (aux->c >= j)
            break;
        aux = aux->proxL;
    }
    if (aux && aux->c == j)
        return aux->value;
    return 0;
}

int somaColuna (MATRIZ * m, int i){
    int resp = 0;
    NO* aux = m->col[i];
    while (aux){
        resp += aux->value;
        aux = aux->proxC;
    }
    return resp;
}

int somaLinha (MATRIZ * m, int i){
    int resp = 0;
    NO* aux = m->lin[i];
    while (aux){
        resp += aux->value;
        aux = aux->proxL;
    }
    return resp;
}

int contarZeros (MATRIZ * m){
    int elementos = 0;
    int i = 0;
    while (i < MAXLIN){
        NO* aux = m->lin[i];
        while (aux){
            elementos++;
            aux = aux->proxL;
        }
        i++;
    }
    return (MAXLIN*MAXCOL) - elementos;
}

NO* primeiroInteiro (MATRIZ * m, int x){
    int i = 0;
    while (i < MAXLIN){
        NO* aux = m->lin[i];
        while (aux){
            if (aux->value == x)
                return aux;
            aux = aux->proxL;
        }
        i++;
    }
    return NULL;
}

NO* maiorColuna (MATRIZ * m){
    NO* resp = NULL;
    int maior = 0;
    int i = 0;
    while (i < MAXCOL){
        int elementos = 0;
        NO* atual = m->col[i];
        NO* aux = atual;
        while(aux){
            elementos++;
            aux = aux->proxC;
        }
        if (elementos > maior){
            resp = atual;
            maior = elementos;
        }
        i++;
    }
    return resp;
}

NO* maiorLinha (MATRIZ * m){
    NO* resp = NULL;
    int maior = 0;
    int i = 0;
    while (i < MAXLIN){
        int elementos = 0;
        NO* atual = m->lin[i];
        NO* aux = atual;
        while(aux){
            elementos++;
            aux = aux->proxL;
        }
        if (elementos > maior){
            resp = atual;
            maior = elementos;
        }
        i++;
    }
    return resp;
}

void printaColuna (MATRIZ* m, int i){
    NO* p = m->col[i];
    while (p){
        printf("%d\n", p->value);
        p = p->proxC;
    }
}

void printaLinha (MATRIZ* m, int i){
    NO* p = m->lin[i];
    while (p){
        printf("%d\n", p->value);
        p = p->proxL;
    }
}

int main()
{
    int prematriz [MAXLIN][MAXCOL] =  {
        {0, 0, 0, 0, 1, 0, 0, 7, 0, 0},
        {0, 8, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 9, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 6, 0, 0, 0},
        {0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    MATRIZ m;
    inicializa(&m);
    cria(prematriz, &m);
    printf("%d", contarZeros(&m));
    return 1;
}
