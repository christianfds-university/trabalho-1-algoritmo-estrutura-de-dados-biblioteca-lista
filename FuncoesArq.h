#ifndef FUNCOES_H
#define FUNCOES_H
#include "ListaEstantes.h"

// Remove \n de uma string e substitui por \0
// Entrada: Ponteiro pra string
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: string sem \n
void stripchar(char *s);

// Le um livro do arquivo txt
// Entrada: Ponteiro pra string lida do arquivo txt, ponteiro pro livro que ira receber as informações
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: livro recebe as informações lidas
void lerLivro(char *buffer,livro *l);

// Le o arquivo txt e cria uma arvore de estante, prateleiras e livros
// Entrada: void
// Retorno: Ponteiro pra lista que contém a arvore
// Pré-condição: nenhuma
// Pós-condição: nenhuma
lista *lerArq();

// Salva as prateleiras da lista em formato binário e desaloca os livros da arvore para evitar a utilização de muito memória
// Entrada: Ponteiro pra cabeça da lista
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Cria um arquivo para cada prateleira
void SalvarEmBin(lista *l);

// Le a estante e prateleira informada e adiciona um novo livro a ela
// Entrada: Ponteiro lista, ponteiro pro livro, estante e prateleira
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Adiciona um novo livro a estante e prateleira informada e salva em binário
void AdicionarLivro(lista *l, livro *li, int e, int p);

// Verifica se o livro existe na lista
// Entrada: Ponteiro pra lista, id do livro, string para retorno do endereço, flag inteira pra retorno da disponibilidade do livro
// Retorno: Ponteiro pra prateleira onde o livro se encontra, endereço e a disponibilidade do livro
// Pré-condição: nenhuma
// Pós-condição: string recebe o endereço do livro, flag recebe a disponibilidade
prateleira *VerificaID(lista *l, int i, char *endereco, int *flag);

// Remove um livro da biblioteca
// Entrada: Ponteiro pra lista, id do livro a ser removido
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Remove o livro, caso não esteja sendo utilizado
void RemoveLivro(lista *l, int i);

// Aloca os livros na arvore
// Entrada: Ponteiro pra lista
// Retorno: void
// Pré-condição: nenhuma
// Pós-condição: Livros alocados na lista
void AlocaLivros(lista *l);

#endif // FUNCOES_H
