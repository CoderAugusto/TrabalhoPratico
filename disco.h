// disco = sequencia linear de blocos de tamanho fixo 

#include "bloco.h"

typedef struct disco { 
    int qtdBlocos;

    //usar um bloco pra gerenciar  blocos livres = ultimo
    Lista* blocosLivres; // usar= usar para gerenciar espaço livre
    Lista* iNodesLivres; // bloco 0

    //usar um bloco para armazenar iNodes = penultimo
    iNode* iNodes; //bloco 1 armazenar iNodes

    //usar um bloco para armazenar o diretorio Raiz = antepenultimo
    Diretorio* diretorioRaiz;

    //restante dos blocos para armazenar arquivos/diretorios
    Bloco* blocos; 
} Disco;

void inicializaDisco(Disco *disco, int qtdBlocos);
void insereINode(Disco *disco, int indice);