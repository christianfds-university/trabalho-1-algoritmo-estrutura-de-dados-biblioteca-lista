#ifndef LISTASIMPLES_H
#define LISTASIMPLES_H
// estrutura de nó para lista encadeada
typedef struct no {
    int info;
    struct no *prox;
} no;


// Aponta a lista l para NULL
// Entrada: lista
// Retorno: l apontando pra NULL
void novaLista(struct no *l);

// Testa se uma lista  ́e vazia
// Entrada: lista
// Retorno: 1 se a lista  ́e vazia ou 0 caso contrário
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int vazia(struct no *l);

// Insere um elemento na cauda da lista
// Entrada: lista e inteiro a ser inserido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento é inserido na cauda da lista
struct no* insere(struct no* l, int info);

// Remove um elemento da lista
// Entrada: lista e inteiro a ser removido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento  ́e removido da lista
struct no* remover(struct no* l, int info);

// Remove a cabeça da lista
// Entrada: lista
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento é removido da lista
struct no* removerFirst(struct no* l);

// Remove um elemento da lista
// Entrada: lista e inteiro a ser removido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento  ́e removido da lista
struct no* removerRec(struct no* l, int info);

// Imprime os elementos da lista
// Entrada: lista
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: os elementos são impressos no console
void imprime(struct no* l);

// Imprime os elementos da lista
// Entrada: lista
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: os elementos são impressos no console
void imprimeRec(struct no* l);

// Desaloca toda a lista
// Entrada: lista
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: nenhum
void desalocar(struct no* l);

#endif // LISTASIMPLES_H
