#include "diretorio.h" // que inclui "iNode.h"

typedef struct bloco{
    // ou vai ter diretorio ou vai ter conteudo
    Diretorio* diretorio; 
    char* conteudo; 
} Bloco;
