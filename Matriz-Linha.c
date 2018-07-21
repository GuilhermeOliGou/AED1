
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXCOL 10
#define MAXLIN 10

typedef struct S{
    int value;
    int c;
    int l;
    struct S* prox;
}NO;

typedef struct {
    NO* inicio;
}MATRIZ;

void inicializa (MATRIZ * m){
    m->inicio = NULL;
}

void cria (MATRIZ * m, int x[MAXLIN][MAXCOL]){
    NO* ant = NULL;
    int i;
    for (i = 0; i < MAXLIN; i++){
        int j;
        for (j = 0; j < MAXCOL; j++){
            if (x[i][j] != 0){
                NO* novo = (NO*) malloc(sizeof(NO));
                novo->l = i;
                novo->c = j;
                novo->value = x[i][j];
                novo->prox = NULL;
                if (ant)
                    ant->prox = novo;
                else
                    m->inicio = novo;
                ant = novo;
            }
        }
    }
}

void setarColuna (MATRIZ * m, int i, int k){
    NO* ant = NULL;
    NO* aux = m->inicio;
    int j;
    for (j = 0; j < MAXLIN; j++){
        while (aux){
            if (aux->l > j || aux->c == i || (aux->l == j && aux->c > i))
                break;
            ant = aux;
            aux = aux->prox;
        }
        if (aux && aux->c == i){
            aux->value = k;
            ant = aux;
            aux = aux->prox;
        }else {
            NO* novo = (NO*) malloc(sizeof(NO));
            novo->l = j;
            novo->c = i;
            novo->value = k;
            if (ant)
                ant->prox = novo;
            else
                m->inicio = novo;
            ant = novo;
            if (aux)
                novo->prox = aux;
            else
                novo->prox = NULL;
        }
    }
}

void setarLinha (MATRIZ * m, int i, int k){
    NO* ant = NULL;
    NO* aux = m->inicio;
    int j;
    for (j = 0; j < MAXCOL; j++){
        while (aux){
            if (aux->l >= i)
                break;
            ant = aux;
            aux = aux->prox;
        }
        if (aux && aux->l == i){
            aux->value = k;
            ant = aux;
            aux = aux->prox;
        }else {
            NO* novo = (NO*) malloc(sizeof(NO));
            novo->l = i;
            novo->c = j;
            novo->value = k;
            if (ant)
                ant->prox = novo;
            else
                m->inicio = novo;
            ant = novo;
            if (aux)
                novo->prox = aux;
            else
                novo->prox = NULL;
        }
    }
}

void printaMatriz (MATRIZ * m){
    NO* aux = m->inicio;
    while(aux){
        printf("%d\n", aux->value);
        aux = aux->prox;
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
    cria (&m, prematriz);
    setarLinha(&m, 8, 7);
    printaMatriz(&m);
    return 1;
}
