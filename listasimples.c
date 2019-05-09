#include "listasimples.h"
#include <stdlib.h>
#include <stdio.h>

void novaLista(struct no *l){
    l = NULL;
}


int vazia(struct no *l){
    if(l == NULL)
        return 1;
    return 0;
}

struct no* insere(struct no* l, int info){

    no* p = malloc(sizeof(no));
    p->info = info;
    p->prox = NULL;

    if(l==NULL){
        p->prox = NULL;
        return p;
    }
    else{
        no* q = l;
        while(q->prox!=NULL)
            q = q->prox;
        q->prox = p;
    }

    return l;

}

int pop(struct no* l){
    int aux;
    no *p = l;
    if(l){
        aux = l->info;
        l = l->prox;
        free(p);
        return aux;
    }
    printf("Fila Vazia\n");
    return -1;
}


struct no* remover(struct no* l, int info){
    no *p, *q;
    q = p = l;
    if(l){
        while(p->info != info){
            q = p;
            if(p->prox == NULL){
                printf("Elemento não encontrado\n");
                scanf("%*c%*c");
                return l;
            }
            p = p->prox;
        }
        if(p == l){
            l = l->prox;
            free(p);
        } else{
            q->prox = p->prox;
            free(p);
        }
    }
    else{
        printf("Lista Vazia\n");
        scanf("%*c%*c");
    }
    return l;
}

struct no* removerFirst(struct no* l){
    no * pnt = l;
    if(l){
        l = l->prox;
        free(pnt);
    }
    return l;
}

struct no* removeRecAux(no* l, no* ant, no* atual, int info){
    if(atual == NULL){
        printf("Elemento não encontrada na lista\n");
        return l;
    }
    if((atual->info == info) && (atual == l)){
        l = atual->prox;
        free(atual);
        return l;
    }
    if(atual->info == info){
        ant->prox = atual->prox;
        free(atual);
        return l;
    }

    return removeRecAux(l, atual, atual->prox, info);
}

struct no* removerRec(struct no* l, int info){
    return removeRecAux(l,l,l,info);
}


void imprimeRec(no *l){
    if(l){
        printf("%d\n", l->info);
        imprimeRec(l->prox);
    }

}

void imprime(struct no* l){
    no *p;
    int k = 0;
    p = l;
    if(l!=NULL){
        printf("Fila de Espera\n");
        while(p){
            printf("| %5d |", p->info);
            k++;
            p = p->prox;
        }
        printf("\n%2d Pessoas na lista lista de espera\t", k);
    }
    else{
        printf("Lista Vazia\n");
    }
}

void desalocar(struct no*l){
    if(l==NULL || l->prox==NULL){
        free(l);
    }
    else
        desalocar(l->prox);
}
