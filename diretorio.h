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
    EntradaDiretorio* entradasDiretorio;
    Lista* entradasLivres; 
} Diretorio;

void inicializaDiretorio(Diretorio* diretorio);
void inicializarEntradaDiretorio(EntradaDiretorio* entradaDiretorio);
void adicionaEntradaDiretorio(Diretorio* diretorio, char* nome, int indice_iNode);
int diretorioEstaVazio(Diretorio *dir);
void removeEntradaDiretorio(Diretorio *dir, int indice);
