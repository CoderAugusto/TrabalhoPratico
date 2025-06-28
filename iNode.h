#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista.h"

#define QTD_ENDERECOS 10

typedef enum{
    diretorio,arquivo
}Tipo;

typedef struct atributo{
    int tamanho;
    Tipo tipo;
    time_t criado;
    time_t modificado;
    time_t ultimoAcesso;
} Atributo;

typedef struct iNode {
    Atributo atributos;
    int enderecosBlocos[QTD_ENDERECOS]; // endereços de blocos disco
    Lista blocosLivres;
} iNode;

iNode inicializaINode(Tipo tipo);
Atributo inicializaAtributos(Tipo tipo);

void imprimirAtributos(Atributo atributo);
char* imprimirTipo(Tipo tipo);