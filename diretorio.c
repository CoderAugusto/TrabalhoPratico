#include "diretorio.h"

void inicializaDiretorio(Diretorio* diretorio){
    // aloca espaço para o vetor/lista de entradas de diretorio daquele diretorio?
    diretorio->entradasDiretorio = (EntradaDiretorio*)malloc(sizeof(EntradaDiretorio)*MAX_ENTRADAS_DIR); //depois mudar pra lista
    diretorio->entradasLivres = inicializaLista(MAX_ENTRADAS_DIR);
}

void adicionaEntradaDiretorio(Diretorio* diretorio, char* nome, int indice_iNode){
    EntradaDiretorio entrada;
    entrada.iNodeIndice = indice_iNode;
    strcpy(entrada.nome, nome); 

    //insere uma nova entrada de diretorio na lista de entrada do diretorio
    int indice = primeiroLista(diretorio->entradasLivres); //ter uma lista com os indices livres?
    diretorio->entradasDiretorio[indice]=entrada;
}