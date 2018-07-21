
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define NP 5

typedef struct {
    int A [MAX];
    int base [NP+1];
    int topo [NP+1];
}NPPILHAS;

typedef struct {
    int A [MAX];
    int topo;
}PILHA;

void NPInicializa (NPPILHAS * np){
    int i;
    for (i = 0; i <= NP; i++){
        np->base[i] = (i*(MAX/NP))-1;
        np->topo[i] = (i*(MAX/NP))-1;
    }
}

void PInicializa (PILHA * p){
    p->topo = -1;
}

bool PCheio (PILHA * p){
    if (p->topo == MAX-1)
        return true;
    return false;
}

bool NPCheio (NPPILHAS * np, int k){
    if (np->topo[k] == np->base[k+1])
        return true;
    return false;
}

int main()
{
    return 1;
}
