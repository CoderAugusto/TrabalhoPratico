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

├── main.c # Ponto de entrada com menus e interação do usuário
├── funcionalidades.c/.h # Funções auxiliares, menus e lógica de alto nível
├── disco.c/.h # Inicialização e gerenciamento do "disco virtual"
├── diretorio.c/.h # Criação, navegação, renomeação e remoção de diretórios
├── arquivo.c/.h # Criação, leitura e estrutura dos arquivos simulados
├── iNode.c/.h # Inicialização e controle dos i-nodes
├── bloco.c/.h # Blocos de dados com conteúdo de arquivos
├── lista.c/.h # Listas encadeadas para gerenciar blocos e i-nodes livres
├── makefile # Facilita a compilação
└── README.md # Este arquivo

---

## 🛠️ Compilação

