#include "diretorio.h" // que inclui "iNode.h"

#define BLOCK_SIZE 4096

typedef struct bloco {
    Diretorio* diretorio; 
    char* conteudo; // Para armazenar dados de arquivo
} Bloco;
