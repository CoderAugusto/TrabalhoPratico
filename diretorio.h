// sistema de diretório hierárquico
// diretório raiz -> diretorio de usuario -> subdiretorios -> arquivo de usuario
// caminhos = PATH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "iNode.h"

#define MAX_ENTRADAS_DIR 5

typedef struct entradaDiretorio {
    char nome[100];
    int iNodeIndice;
} EntradaDiretorio;

typedef struct diretorio {
    EntradaDiretorio* entradasDiretorio; //vetor pq vai ter uma quantidade limitada de entradas = 5
    Lista* entradasLivres; //melhor ser uma lista com as posicoes livres?
} Diretorio;

void inicializaDiretorio(Diretorio* diretorio);
void inicializarEntradaDiretorio(EntradaDiretorio* entradaDiretorio);
void adicionaEntradaDiretorio(Diretorio* diretorio, char* nome, int indice_iNode);
int diretorioEstaVazio(Diretorio *dir);
void removeEntradaDiretorio(Diretorio *dir, int indice);

// achar /usuario/ufv/so/tp
// I-node para o diretório raiz está na memória
// dentro do diretorio raiz tem lista de i-nodes dos arquivos/diertorios que estão nele
// com ele acha o inode /usuario dentro da lista
// achar o diretorio /usuario
// ...