#include <stdio.h>
#include <stdlib.h>

typedef struct celulaLista {
    int indice;
    struct celulaLista* prox;
} CelulaLista;

typedef struct {
    CelulaLista* primeiro;
    int tamanho;
} Lista;

Lista* inicializaLista(int qtdBlocos);
int verificaListaVazia(Lista *lista);
void insereLista( Lista *lista, int indice);
void removeLista(Lista *lista, int indice);
int primeiroLista(Lista *lista);
void imprimeLista(Lista *lista);
// InfoProcesso* buscaLista (Lista *lista, int idProcesso);