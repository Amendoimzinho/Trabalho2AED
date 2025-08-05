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
#define DEBUG (printf("\nDebug\n"))

/* Menu */

int abrirMenuPrincipal();

int abrirMenuLivros();

int abrirMenuOutros();

/* Auxiliares */

void limparBuffer();

void limparTerminal();

char* tiraEspacos(char* str);

void pedirEnter();

#endif