#include "iNode.h"
#include <time.h>

Atributo inicializaAtributos(Tipo tipo) {
    Atributo atributo;
    atributo.tamanho = 0;
    atributo.tipo = tipo;
    atributo.criado = time(NULL);
    atributo.modificado = atributo.criado;
    atributo.ultimoAcesso = atributo.criado;
    return atributo;
}

iNode inicializaINode(Tipo tipo) {
    iNode novo;
    novo.atributos = inicializaAtributos(tipo);
    for (int i = 0; i < QTD_ENDERECOS; i++) {
        novo.enderecosBlocos[i] = -1; // Inicializa como inválido
    }
    return novo;
}

void imprimirAtributos(Atributo atributo) {
    printf("\nTipo: %s", imprimirTipo(atributo.tipo));
    printf("\nCriado: %s", ctime(&atributo.criado));
    printf("Modificado: %s", ctime(&atributo.criado));
}

char* imprimirTipo(Tipo tipo){
    if (tipo==diretorio)
        return("diretorio");
    else
        return("arquivo");
}

iNode inicializaINodeArquivo() {
    iNode novo;
    novo.atributos = inicializaAtributos(arquivo);
    for (int i = 0; i < QTD_ENDERECOS; i++) {
        novo.enderecosBlocos[i] = -1; // Inicializa como inválido
    }
    return novo;
}