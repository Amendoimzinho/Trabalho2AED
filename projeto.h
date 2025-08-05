#ifndef PROJETO_H
#define PROJETO_H

#include <stdio.h>
#include <stdlib.h>
#include "livro.h"
#include "arqbin.h"
#include "arquivo.h"

#define ERRO_ARQ  (printf("\nErro ao abrir arquivo\n"))
#define ERRO_ALOC (printf("\nErro ao alocar\n"))
#define ERRO_ALOC_ARQ(f) {fclose(f); ERRO_ALOC;}
#define ERRO_ID (printf("\nID nao encontrado\n"))

void limparTerminal();

void tiraEspacos();

void limparBuffer();

void pedirEnter();

#endif