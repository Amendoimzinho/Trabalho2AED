#ifndef LIVRO_H
#define LIVRO_H

#include "projeto.h"

#define ALOC_LIVRO ((Livro*)malloc(sizeof(Livro)))

typedef struct L {
    char titulo[150],
         autor[200],
         editora[50];
    int ano,
        edicao,
        exemplares,
        ID;
    double preco;

    int esquerda,
        direita,
        pai,
        posAtual;
}Livro;

void imprimirLivro();

void copiarLivro(Livro* Origem, Livro* Destino);

#endif