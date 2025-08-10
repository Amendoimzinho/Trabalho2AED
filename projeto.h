#ifndef PROJETO_H
#define PROJETO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"
#include "arqbin.h"
#include "arquivo.h"

#define ERRO_ARQ  (printf("\nErro ao abrir arquivo\n"))
#define ERRO_ALOC (printf("\nErro ao alocar\n"))
#define ERRO_ALOC_ARQ(f) {fclose(f); ERRO_ALOC;}
#define ERRO_ID (printf("\nID nao encontrado\n"))
#define ERRO_LEITURA (printf("\nErro ao ler linha do arquivo\n"))
#define ERRO_OPCAO (printf("\nOpcao Invalida\n"))
#define DEBUG(n) (printf("\nDebug - %d\n", n))

/* Menu */

/// @brief Abre o menu principal
/// @return A operacao do usuario
int abrirMenuPrincipal();

/// @brief Abre o menu de livros
/// @return A opcao do usuario
int abrirMenuLivros();

/// @brief Abre o menu de outras opcoes
/// @return A opcao do usuario
int abrirMenuOutros();

/* Auxiliares */

/// @brief Limpa o buffer stdin
void limparBuffer();

/// @brief Limpa o terminal
void limparTerminal();

/// @brief Tira os espacos inuteis antes e depois de uma string
/// @param str Uma string qualquer
/// @return A string sem os espacos
char* tiraEspacos(char* str);

/// @brief Pausa o sistema e pede um enter para o usuario
void pedirEnter();

#endif