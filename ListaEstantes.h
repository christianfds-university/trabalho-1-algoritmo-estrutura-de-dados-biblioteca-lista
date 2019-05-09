#ifndef ESTANTES_H
#define ESTANTES_H

//Estrutura nó de livros
typedef struct livro{
    int id;
    char nome[255];
    char autor[255];
    int flag; //flag == 1; livro disponível; flag == 0; livro indisponível
    struct livro* prox;
} livro;

//Estrutura nó de prateleiras e ponteiro pra livros
typedef struct prateleira{
    struct livro* livros;
    char nome[255]; //Nome do arquivo binario de livros
    struct prateleira* prox;
} prateleira;

//Estrutura nó de estantes e ponteiro pra prateleiras
typedef struct estante{
    struct prateleira* prateleiras;
    struct estante* prox;
} estante;

//Estrutura que mantém a cabeça da lista de estantes
typedef struct lista{
    estante* cabeca;
}lista;

// Insere uma nova estante na lista de estantes informadas
// Entrada: Ponteiro pra cabeça da lista de estante
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: Nova estante é inserida na cauda da lista
estante* insereEstante(estante *l);

// Insere uma nova prateleira na lista de prateleiras informada
// Entrada: Ponteiro pra cabeça da lista de prateleiras
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: Nova prateleira é inserida na cauda da lista
prateleira* inserePrateleira(prateleira *l);

// Insere um novo livro na prateleira informada na ordem de id crescente
// Entrada: Ponteiro pra prateleira, Ponteiro pro livro, id do livro
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Livro é inserido na lista de livros da prateleira
void insereLivro(prateleira *l, livro *p, int id);

// Desaloca todos os livros da lista informada
// Entrada: Ponteiro pra lista
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: lista com todos os livros desalocados
void desalocaLivros(lista *l);

// Desaloca recursivamente todos os livros apartir do informado
// Entrada: Ponteiro pra cabeça dos livros
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Todos os livros apartir da cabeça são desalocados
void desalocaL(livro *l);

// Desaloca todas as prateleiras e livros apartir da informada
// Entrada: Ponteiro pra cabeça das prateleiras
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Todas as prateleiras e livros apartir da cabeça são desalocados
void desalocaP(prateleira *l);

// Desaloca todas as estantes, prateleiras e livros da lista informada
// Entrada: Ponteiro pra lista
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Toda as enstantes, prateleiras e livros apartir da cabeça da lista são desalocados
void desaloca(lista *l);

// Imprime todas as informações da lista de livros
// Entrada: Ponteiro pra cabeça dos livros
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Imprime no console
void ImprimeLivros(livro *l);

//Imprime todas as informações da lista de prateleiras e seus livros
// Entrada: Ponteiro pra cabeça das prateleiras
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Imprime no console
void ImprimePrateleira(prateleira *l);

//Imprime todas as informações da lista, suas estantes, prateleiras e livros
// Entrada: Ponteiro pra cabeça da lista
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Imprime no console
void ImprimeLista(lista *l);

#endif // ESTANTES_H
