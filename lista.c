#include "lista.h"

Lista* inicializaLista(int qtdBlocos) {
    Lista* inicializa = (Lista*)malloc(sizeof(Lista));
    inicializa->primeiro = NULL;
    inicializa->tamanho = 0;

    for (int i = qtdBlocos-1; i >=0; i--) {
        insereLista(inicializa, i);
    }
    return inicializa;
}

int verificaListaVazia(Lista* lista) {
    return (lista->primeiro == NULL);
}

void insereLista(Lista* lista, int indice) {
    CelulaLista* novaCelula = (CelulaLista*)malloc(sizeof(CelulaLista));
    novaCelula->indice = indice;
    novaCelula->prox = lista->primeiro;
    lista->primeiro = novaCelula;
    lista->tamanho ++;
}

int primeiroLista(Lista* lista) {

    if (verificaListaVazia(lista)){
        return -1;
    }

    CelulaLista* primeiro = lista->primeiro;
    int indice = primeiro->indice;
    lista->primeiro = primeiro->prox;
    free(primeiro);
    lista->tamanho--;

    return indice;
}

void imprimeLista(Lista *lista){
    CelulaLista *aux;
    aux = lista->primeiro;
    while (aux != NULL)
    {
        printf("%d - ",aux->indice);
        aux = aux->prox;
    } 
    return;
}