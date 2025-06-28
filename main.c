#include "funcionalidades.h"

int* menu();
int menuFuncionalidades();

int main(){
    int qtdBlocos = 20;

    //inicializa o Disco
    Disco disco;
    inicializaDisco(&disco,qtdBlocos);  //temos o disco com o diretorio raiz ='/' 

    Diretorio* diretorioAtual = disco.diretorioRaiz;

    char caminhoAtual[500]; // permitir navegabilidade no sistema
    strcpy(caminhoAtual, "/");

    //TODO armazenar caminho;

    if (diretorioAtual->entradasLivres->tamanho == MAX_ENTRADAS_DIR){
        printf("\nDiretório Atual está vazio");
    }
    else{
        printf("\nConteúdo do Diretório Atual");
        listarConteudoDiretorio(diretorioAtual);
    }

    while(1){
        printf("\nCaminho atual = %s", caminhoAtual);

        int escolha = menuFuncionalidades();
        
        if (escolha ==0){
            break;
        }

        else{
            switch (escolha) {

                case 1:
                    criarDiretorio(&disco, diretorioAtual);
                    break;
                
                case 2:
                    listarConteudoDiretorio(diretorioAtual);
                    break;
                
                case 3:
                    printf("Renomear diretório ainda não está disponível =(");
                    break;
                
                case 4:
                    listarConteudoDiretorio(diretorioAtual);
                    navegarDiretorio(&disco, &diretorioAtual, caminhoAtual);
                    break;

                case 5:
                    //printf("Voltar ao diretório pai ainda não está disponível =(");
                    diretorioAtual = encontrarDiretorioPai(&disco, diretorioAtual, caminhoAtual); 
                    printf("Novo Caminho Atual %s", caminhoAtual);
                    break;
                
                case 6:
                    criarArquivo();
                    break;

                default:
                    break;
            }
        }
        
    }

    printf("\n");
    return 0;
}

int menuFuncionalidades(){

    int opcao;

    printf("\n============= FUNCIONALIDADES ==============\n");
    printf("\n| 0| Encerrar");
    printf("\n| 1| Criar Diretório");
    printf("\n| 2| Listar Conteúdo Diretório");
    printf("\n| 3| Renomear Diretório");
    printf("\n| 4| Entrar em um Diretório");
    printf("\n| 5| Voltar ao Diretório Pai");
    //printf("\n6) Acessar Arquivo\n7) Criar Arquivo\n8) Renomear Arquivo\n9) Mover Arquivo \n10) Excluir Arquivo");
    printf("\n\nEscolha: ");
    scanf("%d", &opcao);

    //TODO tratar se opcao invalida

    return opcao;
}


int* menu() {
    static int escolhas[2];
    int opcao;

    printf("\n=================== MENU ===================\n");
    printf("\nQual tamanho da partição a ser gerenciada?");
    printf("\n1) 64\n2) 128\n3) 256");
    printf("\nEscolha: ");
    scanf("%d", &escolhas[0]);

    printf("\nQual tamanho do bloco?");
    printf("\n1) 4\n2) 8\n3) 16");
    printf("\nEscolha: ");
    scanf("%d", &escolhas[1]);

    return escolhas;
}

