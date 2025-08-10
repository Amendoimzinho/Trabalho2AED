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

/// @brief Copia as informacoes de um livro par outro (menos as informacoes da arvore)
/// @param Origem Livro de origem das informacoes
/// @param Destino Livro de destino para as informacoes
void copiarLivro(Livro* Origem, Livro* Destino);

/// @brief Aloca e inicia um novo livro
/// @return O ponteiro alocado
Livro* novoLivro();

/// @brief Imprime um livro
/// @param livro Um livro valido
void imprimirLivro(Livro* livro);

/// @brief Pede informacoes para o usuario para criar um novo livro
void novoLivroUsuario();

#endif