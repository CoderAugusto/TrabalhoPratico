all:
	gcc main.c funcionalidades.c disco.c bloco.c iNode.c lista.c diretorio.c arquivo.c -o main.exe
	./main.exe
