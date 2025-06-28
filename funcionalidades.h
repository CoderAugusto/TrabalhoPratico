#include "disco.h"
#include "arquivo.h" //?
// Diretorio
void criarDiretorio(Disco* disco, Diretorio* diretorioAtual);
void navegarDiretorio(Disco* disco, Diretorio** diretorioAtual, char* caminhoAtual);
Diretorio* encontrarDiretorioPai(Disco* disco, Diretorio* diretorioAtual, char* caminhoAtual); 
//void renomearDiretorio();
//void apagarDiretorio();
void listarConteudoDiretorio(Diretorio* diretorioAtual);

// Arquivo
//void criarArquivo();
File* criarArquivo(Disco* disco, Diretorio* diretorioAtual);
//void renomearArquivo();
//void apagarArquivo();
//void listarConteudoArquivo();
//void moverArquivo();