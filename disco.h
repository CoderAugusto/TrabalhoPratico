// disco = sequencia linear de blocos de tamanho fixo 

#include "bloco.h"

typedef struct disco { 
    int qtdBlocos; //qtd total de blocos calculada a partir do tamanho da particao e dos blocos

    //usar um bloco pra gerenciar  blocos livres = ultimo
    Lista* blocosLivres; // usar= usar para gerenciar espaço livre
    Lista* iNodesLivres; // bloco 0

    //usar um bloco para armazenar iNodes = penultimo
    iNode* iNodes; //bloco 1 armazenar iNodes

    //usar um bloco para armazenar o diretorio Raiz = antepenultimo
    Diretorio* diretorioRaiz; //bloco 2 = 

    //restante dos blocos para armazenar arquivos/diretorios
    Bloco* blocos; // restante dos blocos = arquivos/diretorios
} Disco;

void inicializaDisco(Disco *disco, int qtdBlocos);
void insereINode(Disco *disco, int indice);