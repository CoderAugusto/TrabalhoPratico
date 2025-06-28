#include "funcionalidades.h"
#include "arquivo.h"

void criarDiretorio(Disco* disco, Diretorio* diretorioAtual) {
    char nome[50];
    printf("\nQual o nome do diretorio? ");
    scanf("%s", nome);
    // TODO conferir se é um nome válido

    // Verificar se o diretório já existe no diretório onde ele será criado
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (strcmp(diretorioAtual->entradasDiretorio[i].nome, nome) == 0) {
            printf("O diretório '%s' já existe.\n", nome);
            return;
        }
    }

    if (verificaListaVazia(diretorioAtual->entradasLivres)){
        printf("O diretório está cheio. Não é possível adicionar mais entradas.\n");
        return;
    }
    
    // Encontrar indice do inode e do bloco do novo diretorio
    int indiceINode = primeiroLista(disco->iNodesLivres);
    int indiceBloco = primeiroLista(disco->blocosLivres);

    // Criar um novo diretório 
    Diretorio* novoDiretorio = (Diretorio*)malloc(sizeof(Diretorio));
    inicializaDiretorio(novoDiretorio);

    // Salva Diretorio em um Bloco
    disco->blocos[indiceBloco].diretorio = novoDiretorio;

    Tipo tipo = diretorio;
    iNode i_node = inicializaINode(tipo);
    disco->iNodes[indiceINode] = i_node;

    //colocar endereço do bloco no primeiro bloco do iNode
    disco->iNodes[indiceINode].enderecosBlocos[0] = indiceBloco;

    
    // Adicionar uma nova entrada no diretório atual
    adicionaEntradaDiretorio(diretorioAtual, nome, indiceINode);

    printf("\nO diretório '%s' foi criado com sucesso.\n", nome);
}

void navegarDiretorio(Disco* disco, Diretorio** diretorioAtual, char* caminhoAtual){
    // Verificar se o diretório existe no diretório atual
    char nomeDiretorio[50];
    printf("\nQual o nome do diretorio qu deseja acessar? ");
    scanf("%s", nomeDiretorio);
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        // Procurar diretório dentro do diretório atual
        if (strcmp((*diretorioAtual)->entradasDiretorio[i].nome, nomeDiretorio) == 0) {
            // Acessar entrada de diretório para pegar o índice do iNode do novo diretório
            int indiceINode = (*diretorioAtual)->entradasDiretorio[i].iNodeIndice;
            if (disco->iNodes[indiceINode].atributos.tipo == diretorio) { // Conferir se realmente é um diretório
                // Pegar o diretório no primeiro bloco do iNode
                int indiceBloco = disco->iNodes[indiceINode].enderecosBlocos[0];
                *diretorioAtual = disco->blocos[indiceBloco].diretorio;
            }

            // Atualizar o caminho atual
            if (strcmp(caminhoAtual, "/") == 0) {
                sprintf(caminhoAtual, "/%s", nomeDiretorio);
            } else {
                sprintf(caminhoAtual, "%s/%s", caminhoAtual, nomeDiretorio);
            }

            return;
        }
    }

    // Se o loop terminar sem retornar, o diretório não foi encontrado
    printf("Diretório '%s' não encontrado.\n", nomeDiretorio);
}

Diretorio* encontrarDiretorioPai(Disco* disco, Diretorio* diretorioAtual, char* caminhoAtual, int silencioso) {
    
    char* ultimaBarra = strrchr(caminhoAtual, '/');
    if (ultimaBarra != NULL) {
        // Substituir a barra por um caractere nulo para indicar o fim do caminho atual
        *ultimaBarra = '\0';
        // Verificar se o caminho atual ficou vazio
        if (*caminhoAtual == '\0') {
            // Se o caminho atual está vazio, atualizar para "/"
            strcpy(caminhoAtual, "/");
        }
    }
    

    // Iniciar a busca pelo diretório pai a partir do diretório raiz
    Diretorio* diretorioPai = disco->diretorioRaiz;

    // verificar se o caminho atual é o diretório raiz
    if (strcmp(caminhoAtual, "/") == 0) {
        if (!silencioso) {
            printf("Você já está no diretório raiz.\n");
        }
        return diretorioPai;
    }

    // Fazer uma cópia do caminho atual para evitar modificá-lo
    char tempCaminho[500];
    strcpy(tempCaminho, caminhoAtual);

    // Tokenizar o caminho por barras "/"
    char* token = strtok(tempCaminho, "/");
    while (token != NULL) {
        // Verificar se o token é válido
        if (strlen(token) > 0) {
            int i;
            int encontrado = 0;

            // Procurar o token no diretório atual
            for (i = 0; i < MAX_ENTRADAS_DIR; i++) {
                if (strcmp(diretorioAtual->entradasDiretorio[i].nome, token) == 0) {
                    // Verificar se é um diretório
                    int indiceINode = diretorioAtual->entradasDiretorio[i].iNodeIndice;
                    if (disco->iNodes[indiceINode].atributos.tipo == diretorio) {
                        // Atualizar o diretório atual
                        diretorioAtual = disco->blocos[disco->iNodes[indiceINode].enderecosBlocos[0]].diretorio;
                        encontrado = 1;
                        break;
                    }
                }
            }

            if (!encontrado) {
                printf("Diretório '%s' não encontrado.\n", token);
                return NULL; // O diretório pai não foi encontrado
            }
        }

        token = strtok(NULL, "/");
    }

    return diretorioAtual; // Retorna o diretório pai encontrado
}

void listarConteudoDiretorio(Diretorio* diretorioAtual) {
    int qtd = MAX_ENTRADAS_DIR - diretorioAtual->entradasLivres->tamanho; 
    printf("\nConteúdo Diretório:\n");
    for (int i = 0; i < qtd; i++) {
        printf("- %s\n", diretorioAtual->entradasDiretorio[i].nome);
    }
}

void renomearDiretorio(Diretorio* diretorio, char* nomeAntigo, char* nomeNovo) {
    int encontrado = 0;

    // Verifica se o novo nome já existe
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (strcmp(diretorio->entradasDiretorio[i].nome, nomeNovo) == 0) {
            printf("Já existe uma entrada com o nome '%s'.\n", nomeNovo);
            return;
        }
    }

    // Procura o diretório pelo nome antigo e renomeia
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (strcmp(diretorio->entradasDiretorio[i].nome, nomeAntigo) == 0) {
            strcpy(diretorio->entradasDiretorio[i].nome, nomeNovo);
            printf("Diretório '%s' renomeado para '%s'.\n", nomeAntigo, nomeNovo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Diretório '%s' não encontrado.\n", nomeAntigo);
    }
}



File* create_file(FileSystem* fs, const char* name) {
    // implementação da função create_file
}

File* criarArquivo(Disco* disco, Diretorio* diretorioAtual) {
    if (verificaListaVazia(diretorioAtual->entradasLivres)) {
        printf("   Erro: Diretório está cheio!\n");
        return NULL;
    }

    char nomeArquivo[100];
    printf("   Digite o nome do arquivo (com extensão): ");
    scanf("%99s", nomeArquivo);

    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (strcmp(diretorioAtual->entradasDiretorio[i].nome, nomeArquivo) == 0) {
            printf("   Erro: Arquivo já existe!\n");
            return NULL;
        }
    }

    printf("   Digite o conteúdo do arquivo: ");
    getchar(); // consumir \n pendente
    char conteudo[4096];
    fgets(conteudo, sizeof(conteudo), stdin);

    int tamanho = strlen(conteudo);
    int blocosNecessarios = (tamanho + BLOCK_SIZE - 1) / BLOCK_SIZE;

    if (blocosNecessarios > QTD_ENDERECOS) {
        printf("   Erro: Arquivo muito grande (máximo %d blocos)\n", QTD_ENDERECOS);
        return NULL;
    }

    int indiceINode = primeiroLista(disco->iNodesLivres);
    if (indiceINode == -1) {
        printf("   Erro: Sem i-nodes livres\n");
        return NULL;
    }

    disco->iNodes[indiceINode] = inicializaINode(arquivo);

    File* arquivo = (File*)malloc(sizeof(File));
    strncpy(arquivo->name, nomeArquivo, sizeof(arquivo->name));
    arquivo->num_blocks = blocosNecessarios;
    arquivo->blocks = (char**)malloc(blocosNecessarios * sizeof(char*));

    for (int i = 0; i < blocosNecessarios; i++) {
        int blocoIdx = primeiroLista(disco->blocosLivres);
        if (blocoIdx == -1) {
            printf("   Erro: Sem blocos livres suficientes\n");
            for (int j = 0; j < i; j++) {
                insereLista(disco->blocosLivres, disco->iNodes[indiceINode].enderecosBlocos[j]);
            }
            free(arquivo->blocks);
            free(arquivo);
            insereLista(disco->iNodesLivres, indiceINode);
            return NULL;
        }

        disco->blocos[blocoIdx].conteudo = (char*)malloc(BLOCK_SIZE + 1);
        strncpy(disco->blocos[blocoIdx].conteudo, conteudo + (i * BLOCK_SIZE), BLOCK_SIZE);
        disco->blocos[blocoIdx].conteudo[BLOCK_SIZE] = '\0';

        disco->iNodes[indiceINode].enderecosBlocos[i] = blocoIdx;
        arquivo->blocks[i] = disco->blocos[blocoIdx].conteudo;
    }

    disco->iNodes[indiceINode].atributos.tamanho = tamanho;

    int entradaIdx = primeiroLista(diretorioAtual->entradasLivres);
    strcpy(diretorioAtual->entradasDiretorio[entradaIdx].nome, nomeArquivo);
    diretorioAtual->entradasDiretorio[entradaIdx].iNodeIndice = indiceINode;

    printf("   Arquivo '%s' criado com sucesso (%d bytes, %d blocos)\n", nomeArquivo, tamanho, blocosNecessarios);
    return arquivo;
}


void renomearArquivo(FileSystem* fs, const char* name, const char* nomeNovo) {
    int found = 0;
    for (int i = 0; i < fs->num_files; i++) {
        if (strcmp(fs->files[i]->name, name) == 0) {
            found = 1;
            for (int j = 0; j < fs->num_files; j++) {
                if (strcmp(fs->files[j]->name, name) == 0) {
                    printf("Já existe um arquivo com o nome '%s'. Escolha um novo nome.\n", nomeNovo);
                    return;
                }
            }

            strcpy(fs->files[i]->name, nomeNovo);
            printf("Arquivo '%s' renomeado para '%s'.\n", name, nomeNovo);
            return;
        }
    }

    if (!found) {
        printf("O arquivo '%s' não existe.\n", name);
    }
}


void escreverArquivo(File* file, const char* content) { // grava o conteúdo no arquivo, dividindo-o em blocos de tam fixo
    int len = strlen(content);
    int num_blocks = len / BLOCK_SIZE + (len % BLOCK_SIZE != 0);
    
    file->content = (char**)malloc(num_blocks * sizeof(char*));
    file->num_blocks = num_blocks;

    for (int i = 0; i < num_blocks; i++) {
        file->content[i] = (char*)malloc((BLOCK_SIZE + 1) * sizeof(char));
        strncpy(file->content[i], content + i * BLOCK_SIZE, BLOCK_SIZE);
        file->content[i][BLOCK_SIZE] = '\0';
    }

    printf("Conteúdo gravado no arquivo '%s'.\n", file->name);
}

void lerArquivo(File* file) {      // exibe o conteudo na saída
    printf("Conteúdo do arquivo '%s':\n", file->name);

    for (int i = 0; i < file->num_blocks; i++) {
        printf("%s", file->content[i]);
    }
    printf("\n");
}

int apagarDiretorioAtual(Disco *disco, Diretorio **dirAtual, char *caminhoAtual) {
    Diretorio *alvo = *dirAtual;

    if (!diretorioEstaVazio(alvo)) {
        printf("   ❌ Diretório não está vazio.\n");
        return -1;
    }

    Diretorio *pai = encontrarDiretorioPai(disco, alvo, caminhoAtual, 1);
    if (pai == NULL) {
        printf("   ❌ Erro interno: pai não encontrado.\n");
        return -1;
    }

    // Encontrar e remover a entrada do pai que aponta para alvo
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (pai->entradasDiretorio[i].iNodeIndice != -1) {
            int inodeIdx = pai->entradasDiretorio[i].iNodeIndice;
            if (disco->iNodes[inodeIdx].atributos.tipo == diretorio &&
                disco->blocos[disco->iNodes[inodeIdx].enderecosBlocos[0]].diretorio == alvo) {
                removeEntradaDiretorio(pai, i);
                // Libera o inode
                insereLista(disco->iNodesLivres, inodeIdx);
                // Libera o bloco
                disco->blocos[disco->iNodes[inodeIdx].enderecosBlocos[0]].diretorio = NULL;
                insereLista(disco->blocosLivres, disco->iNodes[inodeIdx].enderecosBlocos[0]);
                break;
            }
        }
    }

    // Volta ao diretório pai
    *dirAtual = pai;

    char *ultimaBarra = strrchr(caminhoAtual, '/');
    if (ultimaBarra) {
        *ultimaBarra = '\0';
        if (strlen(caminhoAtual) == 0) strcpy(caminhoAtual, "/");
    }

    return 0;
}