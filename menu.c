#include "MenuSala.h"
#include "FuncoesArq.h"
#include "ListaEstantes.h"
#include "listasimples.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void separator(){
    printf("=====================================================================\n");
}

void menu(){
    int op = 0; //VERIFICA A OPÇÃO ESCOLHIDA PELO USUARIO
    int Carregado = 0; //FLAG PARA VERIFICAR SE JA HOUVE A INICIALIZAÇÃO VIA ARQUIVO
    lista *l; //ARVORE DE ESTANTE E PRATELEIRAS
    sala *s1, *s2, *s3; //SALAS DE ESTUDO
    no *f = NULL; //FILA DE ESPERA

    s1 = (sala*) malloc(sizeof(sala));
    s2 = (sala*) malloc(sizeof(sala));
    s3 = (sala*) malloc(sizeof(sala));
    s1->ra = 0;
    s2->ra = 0;
    s3->ra = 0;

    while(op!=-1){
        system("clear");
        separator();
        printf("|%2d| %33s |\n",  1,  "Carregar Arquivo de Inicialização");
        printf("|%2d| %33s |\n",  2,  "Inserir Livro");
        printf("|%2d| %33s |\n",  3,  "Retirar Livro");
        printf("|%2d|  %33s |\n", 4,  "Busca Endereço do Livro");
        printf("|%2d| %33s |\n",  5,  "Locar Sala");
        printf("|%2d| %33s |\n",  6,  "Emprestar Livro");
        printf("|%2d| %33s |\n",  7,  "Liberar Sala");
        printf("|%2d| %33s |\n",  8,  "Imprimir Mapa de Estantes");
        printf("|%2d| %33s |\n",  9,  "Imprimir Mapa de Salas");
        printf("|%2d| %33s |\n", 10,  "Imprimir Fila de Espera");
        printf("|%2d| %33s |\n", -1,  "Sair");
        separator();
        scanf("%d", &op);
        getchar();
        switch(op){
        case 1://CARREGA O ARQUIVO DE INICIALIZAÇÃO
            if(!Carregado){//Verifica se o arquivo de inicialização foi carregado
                l = lerArq();
                SalvarEmBin(l);
                printf("Arquivo carregado com sucesso\n");
                Carregado = 1;
            }
            else{
                printf("O Arquivo já foi carregado anteriormente nesta seção\n");
            }
            getchar();
            break;

        case 2://INSERE UM NOVO LIVRO A BIBLIOTECA
            system("clear");
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                int e, p;
                livro *li = (livro*) malloc(sizeof(livro));
                printf("Nome do Livro:");
                fgets(li->nome,sizeof(li->nome),stdin);
                stripchar(li->nome);
                printf("Nome do Autor:");
                fgets(li->autor,sizeof(li->nome),stdin);
                stripchar(li->autor);
                printf("ID do Livro:");
                scanf("%d", &li->id);
                getchar();
                printf("Em qual estante o livro deve ser adicionado?\n");
                scanf("%d", &e);
                getchar();
                printf("Em qual prateleira o livro deve ser adicionado?\n");
                scanf("%d", &p);
                getchar();
                AdicionarLivro(l,li,e,p);
            }
            else{
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            }
            getchar();
            break;

        case 3://REMOVE UM LIVRO DA BIBLIOTECA
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                int aux;
                printf("Qual a id do livro que você deseja retirar?\n");
                scanf("%d", &aux);
                RemoveLivro(l,aux);
                getchar();
            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 4://PROCURA O ENDEREÇO DE UM LIVRO
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                int i,flag;
                char end[255], *pnt;
                prateleira *prat;
                printf("Qual livro você busca? (insira o id)\n");
                scanf("%d", &i);
                getchar();
                prat = VerificaID(l,i,end,(int *)&flag);
                if(prat && flag==1){
                    pnt = end;
                    while(*pnt != '\0'){
                        if(*pnt == '.'){
                            *pnt = '\0';
                            break;
                        }
                        pnt++;
                    }
                    printf("O Livro %d se encontra em %s\n", i, end);
                }else
                    printf("O Livro %d se encontra indisponível\n", i);
            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 5://LOCA UMA SALA PRA UM ALUNO
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                int ra;

                printf("RA do aluno: ");
                scanf("%d", &ra);
                getchar();
                if(ra == 0){
                    printf("O RA de número 0 é inválido\n");
                    getchar();
                    break;
                }

                //VERIFICA SE HÁ SALA LIVRE
                if(s1->ra==0){
                    s1->ra = ra;
                    printf("Aluno %d na sala 1\n",ra);
                }
                else if(s2->ra==0){
                    s2->ra = ra;
                    printf("Aluno %d na sala 2\n",ra);
                }
                else if(s3->ra==0){
                    s3->ra = ra;
                    printf("Aluno %d na sala 3\n",ra);
                }
                else{
                    printf("Sem sala disponível.\nO aluno %d foi direcionado a fila de espera\n", ra);
                    f = insere(f,ra);
                }
            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 6://EMPRESTA UM LIVRO PRA UM ALUNO QUE JA ESTEJA EM UMA SALA
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                int id, sala, flag, *fla;
                prateleira *prat;
                char end[255];

                printf("Qual livro enviar para qual sala?\n");
                scanf("%d %d", &id, &sala);
                getchar();

                if(((sala == 1) && (s1->ra == 0))||((sala == 2) && (s2->ra == 0))||((sala == 3) && (s3->ra == 0))){
                    printf("Sala inválida ou vazia\n");
                    getchar();
                    break;
                }


                fla = &flag;

                prat = VerificaID(l,id,end,fla);
                printf("%d\n\n", flag);

                if((*fla != 0) && (prat)){
                    //LE A PRATELEIRA ONDE OCORRERÁ ALTERAÇÃO PARA A MEMÓRIA
                    FILE *f = fopen(end, "r+b");
                    livro *aux = (livro*) malloc(sizeof(livro));
                    while( fread(aux,sizeof(livro),1,f) ){
                        insereLivro(prat,aux,aux->flag);
                    }
                    free(aux);
                    fclose(f);

                    aux = prat->livros;

                    while(aux->id != id){
                        aux = aux->prox;
                    }
                    aux->flag = 0;

                    f = fopen(prat->nome,"w+b");
                    aux = prat->livros;
                    //ESCREVE AS ALTERAÇÕES EM ARQUIVO BINÁRIO
                    while(aux){
                        fwrite(aux,sizeof(livro),1,f);
                        aux = aux->prox;
                    }

                    fclose(f);
                    desalocaLivros(l);

                    //INSERE O LIVRO A LISTA DE LIVROS
                    if(sala == 1){
                        s1->l = insere(s1->l,id);
                    }else if(sala == 2){
                        s2->l = insere(s2->l,id);
                    }else if(sala == 3){
                        s3->l = insere(s3->l,id);
                    }
                    printf("Livro enviado para a sala desejada\n");
                    getchar();
                    break;
                }

                printf("Livro indisponível\n");
            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 7://LIBERA UMA SALA
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                int sala;
                no *pnt, *pnt2;

                printf("Qual sala liberar?\n");
                scanf("%d",&sala);
                getchar();

                if((sala != 1) && (sala != 2) && (sala != 3)){
                    printf("Sala inválida\n");
                    getchar();
                    break;
                }

                if(((sala == 1) && (s1->ra == 0))||((sala == 2) && (s2->ra == 0))||((sala == 3) && (s3->ra == 0))){
                    printf("Sala vazia\n");
                    getchar();
                    break;
                }

                //VERIFICA A SALA ESCOLHIDA
                if(sala == 1){
                    s1->ra = 0;
                    pnt = s1->l;
                    s1->l = NULL;
                }else if(sala == 2){
                    s2->ra = 0;
                    pnt = s2->l;
                    s2->l = NULL;
                }else if(sala == 3){
                    s3->ra = 0;
                    pnt = s3->l;
                    s3->l = NULL;
                }

                AlocaLivros(l);
                prateleira *prat;
                livro *li;
                char end[255];
                int flag;

                //DESALOCA OS LIVROS DA SALA E SALVA EM ARQUIVO BINARIO
                while(pnt){
                    prat = VerificaID(l,pnt->info,(char *) &end, (int *) &flag);

                    li = prat->livros;
                    while((li->id != pnt->info)){
                        li = li->prox;
                    }

                    li->flag = 1;

                    pnt2 = pnt;
                    pnt = pnt->prox;
                    free(pnt2);
                }
                SalvarEmBin(l);

                printf("Sala %d esvaziada com sucesso", sala);

                //VERIFICA A FILA
                if(f){
                    printf("Existe pessoas na fila de espera\nA primeira pessoa da fila será transferida automaticamente para a sala %d\n", sala);
                    if(sala == 1){
                        s1->ra = f->info;
                    }else if(sala == 2){
                        s2->ra = f->info;
                    }else if(sala == 3){
                        s3->ra = f->info;
                    }
                    printf("Aluno %d foi transferido para a sala %d\n", f->info, sala);
                    f = removerFirst(f);
                }

            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 8://IMPRIME O MAPA DE ESTANTES
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                AlocaLivros(l);
                ImprimeLista(l);
                desalocaLivros(l);
            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 9://IMPRIME O MAPA DE SALAS
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                no *pnt;
                if(s1->ra){
                    pnt = s1->l;
                    printf("Sala 1\n\tAluno:%d\n\tLivros:",s1->ra);
                    while(pnt){
                        printf("%d ", pnt->info);
                        pnt = pnt->prox;
                    }
                    printf("\n");
                }

                if(s2->ra){
                    pnt = s2->l;
                    printf("Sala 2\n\tAluno:%d\n\tLivros:",s2->ra);
                    while(pnt){
                        printf("%d ", pnt->info);
                        pnt = pnt->prox;
                    }
                    printf("\n");
                }

                if(s3->ra){
                    pnt = s3->l;
                    printf("Sala 3\n\tAluno:%d\n\tLivros:",s3->ra);
                    while(pnt){
                        printf("%d ", pnt->info);
                        pnt = pnt->prox;
                    }
                    printf("\n");
                }

            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;

        case 10://IMPRIME A FILA DE ESPERA
            if(Carregado){//Verifica se o arquivo de inicialização foi carregado
                imprime(f);
            }
            else
                printf("Você precisa carregar o arquivo antes de poder utilizar o sistema\n");
            getchar();
            break;
        }
    }


    //Desaloca tudo que pode ter sobrado do programa principal
    no *pnt2;
    no *pnt = s1->l;
    while(pnt){
        pnt2 = pnt;
        pnt = pnt->prox;
        free(pnt2);
    }
    free(s1);

    pnt = s2->l;
    while(pnt){
        pnt2 = pnt;
        pnt = pnt->prox;
        free(pnt2);
    }
    free(s2);

    pnt = s3->l;
    while(pnt){
        pnt2 = pnt;
        pnt = pnt->prox;
        free(pnt2);
    }
    free(s3);

    if(f)
        desalocar(f);

    if(Carregado)
        desaloca(l);
}
