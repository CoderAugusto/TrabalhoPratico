# 💾 Simulador de Sistema de Arquivos em Memória

Este projeto é um **simulador de sistema de arquivos** desenvolvido para a disciplina **CCF451 - Sistemas Operacionais**, com o objetivo de aplicar na prática os conceitos de gerenciamento de arquivos, blocos, i-nodes e diretórios dentro de um ambiente controlado, totalmente em memória.

---

## 🧠 Motivação

O trabalho busca reforçar o entendimento dos seguintes conceitos:

- Estrutura de diretórios e arquivos
- Gerenciamento de i-nodes e blocos de dados
- Alocação e liberação de espaço
- Navegação entre diretórios
- Simulação de operações típicas de um sistema de arquivos (sem acessar o disco real)

---

## 🚀 Funcionalidades

- ✅ Criar diretório
- ✅ Navegar entre diretórios
- ✅ Voltar ao diretório pai
- ✅ Listar conteúdo de um diretório
- ✅ Renomear diretório atual
- ✅ Criar arquivo a partir de um arquivo real do sistema
- ✅ Armazenar o conteúdo do arquivo em blocos simulados
- ✅ Apagar diretório atual (se estiver vazio)
- 🛠️ Acessar e manipular arquivos (em desenvolvimento)

---

## ⚙️ Tecnologias e Conceitos Usados

- Linguagem C (padrão C99)
- Alocação dinâmica de memória (`malloc`, `free`)
- Estruturas de dados: listas encadeadas, vetores, structs
- Simulação de i-nodes e blocos
- Simulação de sistema de arquivos FAT-like

---

## 🗃️ Estrutura do Projeto

- **main.c**: Ponto de entrada do programa, contém o loop principal de interação com o usuário.
- **disco.c / disco.h**: Simula o "disco" onde os blocos de dados são armazenados em memória.
- **bloco.c / bloco.h**: Gerencia a alocação e liberação de blocos de dados simulados.
- **iNode.c / iNode.h**: Implementa a estrutura de i-nodes, responsável por armazenar metadados de arquivos e diretórios.
- **diretorio.c / diretorio.h**: Lógica de criação, navegação e remoção de diretórios.
- **arquivo.c / arquivo.h**: Responsável pela criação de arquivos simulados a partir de arquivos reais do sistema.
- **lista.c / lista.h**: Implementação de lista encadeada usada para organizar diretórios e arquivos.
- **funcionalidades.c / funcionalidades.h**: Reúne as funções de alto nível que implementam as operações disponíveis ao usuário (criar, listar, navegar, apagar, etc.).
- **makefile**: Automatiza a compilação do projeto.

---

## 🛠️ Compilação

Para compilar o projeto, use o `make` na raiz do repositório:

\`\`\`bash
make
\`\`\`

Isso vai gerar o executável `main.exe` (ou `a.out`, dependendo do sistema). Para rodar:

\`\`\`bash
./main.exe
\`\`\`

Para limpar os arquivos gerados pela compilação:

\`\`\`bash
make clean
\`\`\`

