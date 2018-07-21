#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct S {
    int value;
    struct S* esq;
    struct S* dir;
}NO;

typedef struct {
    NO* raiz;
}ARVORE_BINARIA;

void inicializa (ARVORE_BINARIA * a){
    a->raiz = NULL;
}

bool adiciona (ARVORE_BINARIA * a,NO* pai, int value, int pos){
    if (pai){
        if (pai->esq && pos ==1)
            return false;
        else if (pai->dir && pos ==2)
            return false;
    }
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->value = value;
    novo->dir = NULL;
    novo->esq = NULL;
    if (!pai)
        a->raiz = novo;
    else {
        if (pos == 1)
            pai->esq = novo;
        else
            pai->dir = novo;
    }
    return true;
}

void exibir (NO* p){
    if (p){
        printf("%d\n", p->value);
        exibir (p->esq);
        exibir (p->dir);
    }
}

NO* criar (int c, int v [15]){
    if (c-1 < 15){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->value = v[c-1];
        novo->esq = criar(2*c, v);
        novo->dir = criar((2*c + 1), v);
        return novo;
    }
    return NULL;
}

NO* busca (NO** pai, int ch, NO* p){
    if (p){

        if(p->value == ch)
            return p;
        NO* aux = busca(pai, ch, p->esq);
        if (aux){
            if(!*pai)
                *pai = p;
            return aux;
        }
        aux = busca(pai, ch, p->dir);
        if (aux){
            if(!*pai)
                *pai = p;
            return aux;
        }
    }
    return NULL;
}



int main(){
    int x[15] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    ARVORE_BINARIA a;
    inicializa(&a);
    a.raiz = criar(1, x);
    NO* pai = NULL;
    NO* p = busca(&pai, 5, a.raiz);
    printf("%d\n%d", pai->value, p->value);
    return 1;
}
