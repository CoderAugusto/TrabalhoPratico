#include "disco.h"
#include "arquivo.h" //?
// Diretorio
void criarDiretorio(Disco* disco, Diretorio* diretorioAtual);
void navegarDiretorio(Disco* disco, Diretorio** diretorioAtual, char* caminhoAtual);
void renomearDiretorio(Diretorio* diretorio, char* nomeAntigo, char* nomeNovo);
int apagarDiretorioAtual(Disco *disco, Diretorio **dirAtual, char *caminhoAtual);
void listarConteudoDiretorio(Diretorio* diretorioAtual);
Diretorio* encontrarDiretorioPai(Disco* disco, Diretorio* diretorioAtual, char* caminhoAtual, int silencioso); // silencioso para não imprimir mensagens quando já estiver no diretório raiz

// Arquivo
//void criarArquivo();
File* criarArquivo(Disco* disco, Diretorio* diretorioAtual);
//void renomearArquivo();
//void apagarArquivo();
//void listarConteudoArquivo();
//void moverArquivo();