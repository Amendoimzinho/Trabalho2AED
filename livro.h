#ifndef LIVRO_H
#define LIVRO_H

#include "projeto.h"

#define ALOC_LIVRO ((Livro*)malloc(sizeof(Livro)))

typedef struct L {
    char titulo[151],
         autor[201],
         editora[51];
    int ano,
        edicao,
        exemplares,
        ID;
    float preco;

    int esquerda,
        direita,
        pai,
        posAtual;
}Livro;

void imprimirLivro(Livro* livro);

void copiarLivro(Livro* Origem, Livro* Destino);

Livro* novoLivro();

#endif