#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 4096

typedef struct {            
    char name[100];
    char nomeNovo[20];
    char** blocks;
    char** content;
    int num_blocks;
} File;

typedef struct {
    File* files[100];
    int num_files;
} FileSystem;

File* inicializarArquivo(FileSystem* fs, const char* name, const char* nomeNovo);

#endif