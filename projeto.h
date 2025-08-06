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

/// @brief 
/// @return 
int abrirMenuPrincipal();

/// @brief 
/// @return 
int abrirMenuLivros();

/// @brief 
/// @return 
int abrirMenuOutros();

/* Auxiliares */

/// @brief 
void limparBuffer();

/// @brief 
void limparTerminal();

/// @brief 
/// @param str 
/// @return 
char* tiraEspacos(char* str);

/// @brief 
void pedirEnter();

#endif