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

Diretorio* encontrarDiretorioPai(Disco* disco, Diretorio* diretorioAtual, char* caminhoAtual) {
    
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
        printf("Você já está no diretório raiz.\n");
        return diretorioPai; // O diretório atual é o diretório raiz, não possui diretório pai
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

void renomearDiretorio(Diretorio* diretorio, char* nomeDiretorio, char* nomeNovo){
    for (int i = 0; i < MAX_ENTRADAS_DIR; i++) {
        if (strcmp(diretorio->entradasDiretorio[i].nome, nomeDiretorio) == 0) {
            strcpy(diretorio->entradasDiretorio[i].nome, nomeNovo);
            // return 1;
        }
    }
    return; // 0; //nao encontrou o diretorio e por isso não renomeou
}


File* create_file(FileSystem* fs, const char* name) {
    // implementação da função create_file
}

File* criarArquivo() {
    FileSystem fs;
    fs.num_files = 0;

    char filename[20];
    printf("Digite o nome do arquivo de texto a ser carregado (incluindo a extensão .txt): ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';  // Remove a quebra de linha do final

    File* file = inicializarArquivo(&fs, "arquivo.txt", "novoarquivo.txt");

    // Verifica se o arquivo já existe no sistema de arquivos
    for (int i = 0; i < fs.num_files; i++) {
        if (strcmp(fs.files[i]->name, filename) == 0) {
            printf("O arquivo '%s' já existe no simulador de sistema de arquivos.\n", filename);
            return NULL;
        }
    }

    // Abre o arquivo em modo de leitura
    FILE* file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("Não foi possível abrir o arquivo '%s'. Certifique-se de que o arquivo existe no diretório atual.\n", filename);
        return NULL;
    }

    // Obtém o tamanho do arquivo
    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    // Calcula o número de blocos necessários
    int num_blocks = (file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // Cria um novo arquivo no sistema de arquivos
    //File* file = (File*)malloc(sizeof(File));
    strncpy(file->name, filename, sizeof(file->name));
    file->num_blocks = num_blocks;
    file->blocks = (char**)malloc(num_blocks * sizeof(char*));

    // Lê o conteúdo do arquivo em blocos
    for (int i = 0; i < num_blocks; i++) {
        file->blocks[i] = (char*)malloc(BLOCK_SIZE + 1);
        size_t bytes_read = fread(file->blocks[i], 1, BLOCK_SIZE, file_ptr);
        file->blocks[i][bytes_read] = '\0';
    }

    // Fecha o arquivo
    fclose(file_ptr);

    // Adiciona o arquivo ao sistema de arquivos
    fs.files[fs.num_files++]= file;

    printf("Arquivo '%s' carregado para o sistema de arquivos.\n", filename);

    return file;
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