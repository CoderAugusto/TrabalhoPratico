#include "disco.h"

void inicializaDisco(Disco* disco, int qtdBlocos) {
    printf("\nQuantidade de Blocos = %d", qtdBlocos);
    disco->qtdBlocos = qtdBlocos;

    int blocosLivres = qtdBlocos - 3;

    disco->iNodes = (iNode*)malloc(sizeof(iNode)*blocosLivres); 
    disco->blocos = (Bloco*)malloc(sizeof(Bloco)*blocosLivres);
    disco->blocosLivres = inicializaLista(blocosLivres);
    disco->iNodesLivres = inicializaLista(blocosLivres);
    
    //cria diretorio Raiz
    disco->diretorioRaiz = (Diretorio*)malloc(sizeof(Diretorio));
    inicializaDiretorio(disco->diretorioRaiz);

}
