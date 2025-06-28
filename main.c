#include <stdio.h>
#include <stdlib.h> // Para system()
#include <string.h> // Para strcpy

// Assumindo que "funcionalidades.h" contém suas outras definições necessárias
#include "funcionalidades.h"

// --- Funções Auxiliares para a UI ---

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
    static int escolhas[2]; // Usar 'static' para que o array persista após a função
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
    printf("\n   Caminho Atual: %s\n", caminhoAtual); // Sempre mostra o caminho atual
    printf("-------------------------------------------------\n\n");

    printf("   [1] Criar Diretório\n");
    printf("   [2] Listar Conteúdo do Diretório\n");
    printf("   [3] Renomear Diretório (Em Breve!)\n"); // Indica funcionalidades não implementadas
    printf("   [4] Entrar em um Diretório\n");
    printf("   [5] Voltar ao Diretório Pai\n");
    printf("   [6] Criar Arquivo (Em Breve!)\n"); // Adicionei este como placeholder
    // Adicione mais operações de arquivo aqui conforme forem implementadas:
    // printf("   [7] Acessar Arquivo\n");
    // printf("   [8] Renomear Arquivo\n");
    // printf("   [9] Mover Arquivo\n");
    // printf("   [10] Excluir Arquivo\n");

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
    int *config_escolhas = menuInicial(); // Chama o menu inicial para configuração
    // Use config_escolhas[0] para o tamanho da partição, config_escolhas[1] para o tamanho do bloco.
    // Você precisará passar esses valores para 'inicializaDisco' de forma apropriada.
    // Por enquanto, manterei seu 'qtdBlocos' original para demonstração.

    int qtdBlocos = 20; // Isso idealmente deve ser determinado por config_escolhas

    Disco disco;
    inicializaDisco(&disco, qtdBlocos); // Inicializa o disco com o diretório raiz

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
                    printf("   A funcionalidade de renomear diretório ainda não está disponível. Por favor, escolha outra opção.\n");
                    break;

                case 4:
                    printf("\n   --- Entrar em um Diretório ---\n");
                    listarConteudoDiretorio(diretorioAtual); // Lista o conteúdo antes de pedir para navegar
                    navegarDiretorio(&disco, &diretorioAtual, caminhoAtual);
                    printf("   Novo Caminho: %s\n", caminhoAtual);
                    break;

                case 5:
                    printf("\n   --- Voltar ao Diretório Pai ---\n");
                    Diretorio* novoDir = encontrarDiretorioPai(&disco, diretorioAtual, caminhoAtual);
                    if (novoDir != NULL) {
                        diretorioAtual = novoDir;
                        printf("   Movido com sucesso para o diretório pai. Novo caminho: %s\n", caminhoAtual);
                    } else {
                        printf("   Já está no diretório raiz. Não é possível ir para o pai.\n");
                    }
                    break;

                case 6:
                    printf("\n   --- Criar Arquivo ---\n");
                    printf("   A funcionalidade de criar arquivo ainda não está disponível. Por favor, escolha outra opção.\n");
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