#include "arquivo.h"

File* inicializarArquivo(FileSystem* fs, const char* name, const char* nomeNovo) {
    File* file = (File*)malloc(sizeof(File));
    strncpy(file->name, name, sizeof(file->name));
    strncpy(file->nomeNovo, nomeNovo, sizeof(file->nomeNovo));
    file->num_blocks = 0;
    file->blocks = NULL;
    file->content = NULL;
    
    fs->files[fs->num_files++] = file;

    return file;
}