#include "FuncoesArq.h"
#include "ListaEstantes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void stripchar(char *s){
    while(*s){
        if(*s=='\n')
            *s = '\0';
        s++;
    }
}

void lerLivro(char *buffer,livro *l){
    char *c=buffer;
    sscanf(buffer, "%d", &l->id);

    while(*c!='\0'){
        if(*c == ',')
            *c = '\0';
        c++;
    }
    c = buffer;

    while(*c!='\0')
        c++;
    c++;
    strcpy(l->nome,c);

    while(*c!='\0')
        c++;
    c++;
    stripchar(c);
    strcpy(l->autor,c);
    l->flag = 1;
}

lista *lerArq(){
    lista * l = (lista *) malloc(sizeof(lista));
    FILE *f;

    estante *e;
    prateleira *p;
    livro *liv = (livro *) malloc(sizeof(livro));

    char arqEntrada[255],buffer[255];

    do{
        printf("Arquivo de entrada:");
        fgets(arqEntrada,sizeof(arqEntrada),stdin);
        stripchar(arqEntrada);
    }while(!(f = fopen(arqEntrada,"r")));


    int eCount, pCount;
    eCount = -1;

    while(fgets(buffer,sizeof(buffer),f)){
            char scanner;
            sscanf(buffer,"%c", &scanner);

            if(scanner=='E'){
                eCount++;
                pCount = 0;
                if(l->cabeca == NULL)
                    l->cabeca = e = insereEstante(l->cabeca);
                else
                    e = insereEstante(l->cabeca);

            }
            else if (scanner=='P'){
                if(e->prateleiras == NULL)
                    p = e->prateleiras = inserePrateleira(e->prateleiras);
                else
                    p = inserePrateleira(e->prateleiras);

                sprintf(p->nome,"E%dP%d.bin", eCount, pCount);
                pCount++;
            }
            else{
                lerLivro(buffer,liv);
                insereLivro(p,liv,1);
            }
     }

    free(liv);
    fclose(f);

    return l;
}

void SalvarEmBin(lista *l){
    //Verifica se há oque salvar em arquivo
    if(l->cabeca == NULL)
        return;

    estante *e;
    prateleira *p;
    livro *li;

    e = l->cabeca;

    while(e){
        p = e->prateleiras;

        while(p){
            li = p->livros;
            FILE *f = fopen(p->nome,"w+b");
            while(li){
                fwrite(li,sizeof(livro),1,f);
                li = li->prox;
            }
            fclose(f);
            p = p->prox;
        }

        e = e->prox;
    }

    desalocaLivros(l);
}


void AdicionarLivro(lista *l, livro *li, int e, int p){
    prateleira *prat;
    estante *est = l->cabeca;
    char end[255];
    int i, j, flag;

    if(VerificaID(l,li->id,end,&flag)!=NULL){
        char *pnt = end;
        while(pnt!='\0'){
            if(*pnt == '.'){
                *pnt = '\0';
                break;
            }
            pnt++;
        }
        printf("Livro com a id %d ja existe em %s\n", li->id, end);
        return;
    }

    for(i = 0; i < e; i++){
        if(est == NULL){
            printf("Estante Inválida\n");
            return;
        }
        est = est->prox;
    }

    if(est == NULL){
        printf("Estante Inválida\n");
        return;
    }

    prat = est->prateleiras;

    for(j = 0; j < p; j++){
        if(prat == NULL){
            printf("Prateleira Inválida\n");
            return;
        }
        prat = prat->prox;
    }

    if((prat == NULL)){
        printf("Prateleira Inválida\n");
        return;
    }

    FILE *f = fopen(prat->nome,"r+b");
    livro *aux;

    aux = (livro *) malloc(sizeof(livro));
    while( fread(aux,sizeof(livro),1,f) ){
        insereLivro(prat,aux,aux->flag);
    }
    free(aux);

    fclose(f);

    insereLivro(prat,li,1);

    f = fopen(prat->nome,"w+b");

    livro *livroGuardado = prat->livros;
    while(livroGuardado){
        fwrite(livroGuardado,sizeof(livro),1,f);
        livroGuardado = livroGuardado->prox;
    }

    fclose(f);

    desalocaLivros(l);
    printf("Livro adicionado com sucesso\n");
}

//Verifica se o livro existe na lista
prateleira * VerificaID(lista *l, int i, char *endereco, int *flag){
    estante *estant = l->cabeca;
    prateleira *prat;
    livro *aux = (livro*) malloc(sizeof(livro));
    FILE *f;

    while(estant){
        prat = estant->prateleiras;
        while(prat){

            f = fopen(prat->nome,"r+b");
            while( fread(aux,sizeof(livro),1,f) ){
                if ((aux->id == i)){
                    strcpy(endereco,prat->nome);
                    *flag = aux->flag;
                    free(aux);
                    return prat;
                }
            }

            prat = prat->prox;
        }
        estant = estant->prox;
    }

    free(aux);
    return NULL;
}

//Remove o livro da biblioteca
void RemoveLivro(lista *l, int i){
    char end[255];
    int flag;

    prateleira* prat = VerificaID(l,i,end,&flag);
    if(prat==NULL){
        printf("O livro com a id %d não existe na biblioteca\n", i);
        return;
    }

    FILE *f = fopen(end, "r+b");
    livro *aux = (livro*) malloc(sizeof(livro));

    while( fread(aux,sizeof(livro),1,f) ){
        insereLivro(prat,aux,aux->id);
    }

    free(aux);

    livro *p, *pant;

    p = prat->livros;

    ImprimeLivros(prat->livros);

    while(p){
        pant = p;
        p = p->prox;
        if(pant->id == i){
            if(pant->flag == 0){
                printf("O livro está sendo utilizado atualmente e não pode ser removido\n");
            }
            else{
                prat->livros = p;
                free(pant);
            }
            break;
        }
        if(p->id == i){
            if(p->flag == 0){
                printf("O livro está sendo utilizado atualmente e não pode ser removido\n");
                break;
            }
            else{
                pant->prox = p->prox;
                free(p);
                break;
            }
        }
    }

    p = prat->livros;
    ImprimeLivros(prat->livros);

    fclose(f);

    f = fopen(prat->nome,"w+b");
    while(p){
        fwrite(p,sizeof(livro),1,f);
        p = p->prox;
    }

    fclose(f);
    desalocaLivros(l);
    printf("Livro removido com sucesso\n");
}

//Aloca livros na arvore
void AlocaLivros(lista *l){
    livro *aux;
    FILE *f;
    estante *est = l->cabeca;
    prateleira *prat;

    while(est){
        prat = est->prateleiras;
        while(prat){
            f = fopen(prat->nome,"r+b");

            aux = (livro *) malloc(sizeof(livro));
            while( fread(aux,sizeof(livro),1,f) ){
                insereLivro(prat,aux,aux->id);
            }
            free(aux);
            fclose(f);
            prat = prat->prox;
        }

        est = est->prox;
    }

}
