#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "funcionalidades.h"

// Função para limpar a tela do console
void limparTela() {
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para Linux/macOS
#endif
}

// Função para pausar a execução e esperar o usuário pressionar Enter
void pressioneEnterParaContinuar() {
    printf("\n   Pressione ENTER para continuar...");
    // Limpa o buffer de entrada antes de esperar por nova entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar(); // Espera o pressionamento real da tecla Enter
}

// --- Funções de Menu ---

// Menu inicial para configuração do disco (tamanho da partição e do bloco)
int* menuInicial() {
    static int escolhas[2]; 
    limparTela();

    printf("=================================================\n");
    printf("        🚀 BEM-VINDO AO GERENCIADOR DE ARQUIVOS 🚀 \n");
    printf("=================================================\n\n");

    printf("   Vamos configurar seu disco virtual:\n\n");

    int entradaValida = 0;
    while (!entradaValida) {
        printf("   1. Selecione o tamanho da partição:\n");
        printf("      [1] 64 MB\n");
        printf("      [2] 128 MB\n");
        printf("      [3] 256 MB\n");
        printf("   Digite sua escolha (1-3): ");
        if (scanf("%d", &escolhas[0]) == 1 && escolhas[0] >= 1 && escolhas[0] <= 3) {
            entradaValida = 1;
        } else {
            printf("\n   Entrada inválida. Por favor, digite um número entre 1 e 3.\n");
            // Limpa o buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            pressioneEnterParaContinuar();
            limparTela(); // Limpa e redesenha o cabeçalho
            printf("=================================================\n");
            printf("        🚀 BEM-VINDO AO GERENCIADOR DE ARQUIVOS 🚀 \n");
            printf("=================================================\n\n");
        }
    }
    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    entradaValida = 0;
    while (!entradaValida) {
        printf("\n   2. Selecione o tamanho do bloco:\n");
        printf("      [1] 4 KB\n");
        printf("      [2] 8 KB\n");
        printf("      [3] 16 KB\n");
        printf("   Digite sua escolha (1-3): ");
        if (scanf("%d", &escolhas[1]) == 1 && escolhas[1] >= 1 && escolhas[1] <= 3) {
            entradaValida = 1;
        } else {
            printf("\n   Entrada inválida. Por favor, digite um número entre 1 e 3.\n");
            // Limpa o buffer de entrada
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            pressioneEnterParaContinuar();
            limparTela(); // Limpa e redesenha o cabeçalho
            printf("=================================================\n");
            printf("        🚀 BEM-VINDO AO GERENCIADOR DE ARQUIVOS 🚀 \n");
            printf("=================================================\n\n");
            printf("   Tamanho da partição selecionado: %d\n", escolhas[0]); // Redesenha a escolha anterior válida
        }
    }
    // Limpa o buffer de entrada
    while ((c = getchar()) != '\n' && c != EOF);

    return escolhas;
}


// Função para exibir o menu principal de funcionalidades
int exibirMenuFuncionalidades(const char* caminhoAtual) {
    int opcao;
    limparTela(); // Limpa a tela para uma exibição de menu limpa

    printf("=================================================\n");
    printf("           🚀 MENU DO GERENCIADOR DE ARQUIVOS 🚀 \n");
    printf("=================================================\n");
    printf("\n   Caminho Atual: %s\n", caminhoAtual);
    printf("-------------------------------------------------\n\n");

    printf("   [1] Criar Diretório\n");
    printf("   [2] Listar Conteúdo do Diretório\n");
    printf("   [3] Renomear Diretório \n");
    printf("   [4] Entrar em um Diretório\n");
    printf("   [5] Voltar ao Diretório Pai\n");
    printf("   [6] Criar Arquivo\n");
    printf("   [7] Apagar Diretório ATUAL\n");
    printf("\n-------------------------------------------------\n");
    printf("   [0] Sair da Aplicação\n");
    printf("=================================================\n");

    printf("\n   Digite sua escolha: ");

    // Loop de validação de entrada
    while (scanf("%d", &opcao) != 1) {
        printf("\n   Entrada inválida. Por favor, digite um número.\n");
        // Limpa o buffer de entrada
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        pressioneEnterParaContinuar();
        limparTela();
        exibirMenuFuncionalidades(caminhoAtual); // Redesenha o menu
        printf("\n   Digite sua escolha: "); // Solicita novamente
    }
    // Limpa o buffer de entrada após um scanf bem-sucedido
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return opcao;
}

// --- Lógica Principal do Programa ---

int main() {
    int *config_escolhas = menuInicial();

    int qtdBlocos = 20;

    Disco disco;
    inicializaDisco(&disco, qtdBlocos);

    Diretorio* diretorioAtual = disco.diretorioRaiz;
    char caminhoAtual[500];
    strcpy(caminhoAtual, "/");

    while (1) {
        int escolha = exibirMenuFuncionalidades(caminhoAtual); // Passa o caminhoAtual

        if (escolha == 0) {
            limparTela();
            printf("\n=================================================\n");
            printf("        👋 Saindo do Gerenciador de Arquivos. Até mais! 👋\n");
            printf("=================================================\n\n");
            break; // Sai do loop
        } else {
            switch (escolha) {
                case 1:
                    printf("\n   --- Criar Diretório ---\n");
                    criarDiretorio(&disco, diretorioAtual);
                    break;

                case 2:
                    printf("\n   --- Conteúdo do Diretório ---\n");
                    listarConteudoDiretorio(diretorioAtual);
                    break;

                case 3:
                    printf("\n   --- Renomear Diretório ---\n");

                    if (strcmp(caminhoAtual, "/") == 0) {
                        printf("   Você está no diretório raiz. Não é possível renomeá-lo.\n");
                        break;
                    }

                    char nomeNovo[50];
                    printf("   Digite o novo nome para o diretório atual: ");
                    scanf("%s", nomeNovo);

                    // Extrair o nome atual do diretório (último da barra)
                    char* nomeAntigo = strrchr(caminhoAtual, '/');
                    if (nomeAntigo) nomeAntigo++; // pular o '/'

                    // Criar uma cópia do caminho antes de modificá-lo
                    char caminhoParaPai[500];
                    strcpy(caminhoParaPai, caminhoAtual);

                    // Encontrar o diretório pai com base na cópia
                    Diretorio* pai = encontrarDiretorioPai(&disco, diretorioAtual, caminhoParaPai, 1);
                    if (pai != NULL) {
                        renomearDiretorio(pai, nomeAntigo, nomeNovo);

                        // Atualiza o caminhoAtual também
                        char* ultimaBarra = strrchr(caminhoAtual, '/');
                        if (ultimaBarra) {
                            *ultimaBarra = '\0';
                            if (strlen(caminhoAtual) == 0) strcpy(caminhoAtual, "/");
                            else strcat(caminhoAtual, "/");
                            strcat(caminhoAtual, nomeNovo);
                        }
                    } else {
                        printf("   Não foi possível localizar o diretório pai para renomear.\n");
                    }
                    break;


                case 4:
                    printf("\n   --- Entrar em um Diretório ---\n");
                    listarConteudoDiretorio(diretorioAtual); // Lista o conteúdo antes de pedir para navegar
                    navegarDiretorio(&disco, &diretorioAtual, caminhoAtual);
                    printf("   Novo Caminho: %s\n", caminhoAtual);
                    break;

                case 5:
                    printf("\n   --- Voltar ao Diretório Pai ---\n");
                    if (strcmp(caminhoAtual, "/") == 0) {
                        printf("   Já está no diretório raiz. Não é possível ir para o pai.\n");
                    } else {
                        Diretorio* novoDir = encontrarDiretorioPai(&disco, disco.diretorioRaiz, caminhoAtual, 0);
                        if (novoDir != NULL) {
                            diretorioAtual = novoDir;
                            printf("   Movido com sucesso para o diretório pai. Novo caminho: %s\n", caminhoAtual);
                        }
                    }
                    break;

                case 6:
                    printf("\n   --- Criar Arquivo ---\n");
                    File* novoArquivo = criarArquivo(&disco, diretorioAtual);
                    if (novoArquivo != NULL) {
                        printf("   Arquivo criado com sucesso!\n");
                    } else {
                        printf("   Falha ao criar arquivo.\n");
                    }
                    break;

                case 7:
                    printf("\n   --- Apagar Diretório ATUAL ---\n");

                    /* não permita remover a raiz “/” */
                    if (strcmp(caminhoAtual, "/") == 0) {
                        printf("   ❌ O diretório raiz não pode ser apagado.\n");
                        break;
                    }

                    /* chama a função que apaga o diretório em que estamos */
                    if (apagarDiretorioAtual(&disco, &diretorioAtual, caminhoAtual) == 0) {
                        printf("   ✅ Diretório apagado. Caminho atual: %s\n", caminhoAtual);
                    }
                    break;

                default:
                    printf("\n   Opção inválida. Por favor, escolha um número do menu.\n");
                    break;
            }
            pressioneEnterParaContinuar(); // Pausa após cada ação
        }
    }

    return 0;
}