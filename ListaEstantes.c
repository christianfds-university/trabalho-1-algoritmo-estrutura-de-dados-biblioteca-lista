#include "ListaEstantes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Insere uma nova estante na lista de estantes informadas
estante* insereEstante(estante *l){
    estante *p = (estante*) malloc(sizeof(estante));

    p->prateleiras = NULL;
    p->prox = NULL;

    estante *s = l;

    //Insere sempre no final da lista
    if(s == NULL){
        s = p;
        return p;
    }
    while(s->prox != NULL)
        s = s->prox;

    s->prox = p;

    return p;
}

//Insere uma nova prateleira na lista de prateleiras informada
prateleira* inserePrateleira(prateleira *l){
    prateleira *p = (prateleira*) malloc(sizeof(prateleira));

    p->livros = NULL;
    p->prox = NULL;

    prateleira *s = l;

    //Insere sempre no final da lista
    if(s == NULL){
        s = p;
        return p;
    }
    while(s->prox != NULL)
        s = s->prox;

    s->prox = p;

    return p;
}

//Insere um novo livro na prateleira informada
void insereLivro(prateleira *l, livro *p, int flag){
    livro *t = (livro*) malloc(sizeof(livro));

    t->id = p->id;
    strcpy(t->nome,p->nome);
    strcpy(t->autor,p->autor);
    t->prox = NULL;
    t->flag = flag;

    livro *s = l->livros;

    if(l->livros == NULL)
        l->livros = t;
    else{
        livro *sant = s;
        while(s){
            sant = s;
            s = s->prox;
            if(s == NULL){
                sant->prox = t;
                break;
            }
            if((sant == l->livros) && (s->id > t->id)){
                l->livros = t;
                t->prox = sant;
                break;
            }
            if((sant->id < t->id) && (s->id > t->id)){
                sant->prox = t;
                t->prox = s;
                break;
            }
        }
    }
}

//Desaloca todos os livros da lista informada
void desalocaLivros(lista *l){
    estante *e = l->cabeca;
    prateleira *p;
    livro *li, *lia;
    while(e){
        p = e->prateleiras;
        while(p){
            li = p->livros;
            while(li){
                lia = li;
                li = li->prox;
                free(lia);
            }
            p->livros = NULL;
            p = p->prox;
        }
        e = e->prox;
    }
}

//Desaloca recursivamente todos os livros apartir do informado
void desalocaL(livro *l){

    if(l != NULL){
        desalocaL(l->prox);
//        printf("Livro %d Desalocado\n", l->id);
        free(l);
    }

}

//Desaloca todas as prateleiras apartir da informada
void desalocaP(prateleira *l){
    prateleira* p;
    prateleira* q;
    p = q = l;

    while(p != NULL){
        q = p;

        desalocaL(q->livros);
//        printf("Prateleira %s Desalocada\n", q->nome);
        free(q);

        p = p->prox;
    }

}

//Desaloca todas as estantes, prateleiras e livros da lista informada
void desaloca(lista *l){
    estante* p;
    estante* q;
    p = q = l->cabeca;

    while(p != NULL){
        q = p;

        desalocaP(q->prateleiras);
//        printf("Estante Desalocada\n");
        free(q);

        p = p->prox;
    }

    l->cabeca = NULL;
}

void ImprimeLivros(livro *l){
    livro *p = l;
    while(p!=NULL){
        printf("\t\tID:%d\n",p->id);
        printf("\t\tNome: %s\n", p->nome);
        printf("\t\tAutor: %s\n\n", p->autor);
        p = p->prox;
    }
}

void ImprimePrateleira(prateleira *l){
    char aux[255], *ptr;
    while(l!=NULL){
        strcpy(aux, l->nome);
        ptr = aux;
        while(ptr){
            if(*ptr == '.'){
                *ptr = '\0';
                break;
            }
            ptr++;
        }
        printf("\t%s\n", aux);
        ImprimeLivros(l->livros);
        l = l->prox;
    }
}


void ImprimeLista(lista *l){
    estante*p = l->cabeca;
    int e = 0;
    while(p){
        printf("E%d\n", e++);
        ImprimePrateleira(p->prateleiras);
        p = p->prox;
    }
    printf("==========================================================================\n");
}
