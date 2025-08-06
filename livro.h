#ifndef LIVRO_H
#define LIVRO_H

#include "projeto.h"

#define ALOC_LIVRO ((Livro*)malloc(sizeof(Livro)))

/// @brief 
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

/// @brief 
/// @param livro 
void imprimirLivro(Livro* livro);

/// @brief 
/// @param Origem 
/// @param Destino 
void copiarLivro(Livro* Origem, Livro* Destino);

/// @brief 
/// @return 
Livro* novoLivro();

#endif