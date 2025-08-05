#include "livro.h"
#include "projeto.h"

void imprimirLivro(Livro* livro) {
    printf("\n====== %s (%04d) ======\n", livro->titulo, livro->ano);
    printf("\nAutor: %s", livro->autor);
    printf("\nEditora: %s", livro->editora);
    printf("\nEdicao: %d", livro->editora);
    printf("\nQuantidade de Exemplares: %d", livro->exemplares);
    printf("\nPreco: R$ %.02lf", livro->preco);
    printf("\n====== (ID: %d) ======\n", livro->ID);
}

void copiarLivro(Livro* Origem, Livro* Destino) {
    strcpy(Destino->titulo, Origem->titulo);
    strcpy(Destino->autor, Origem->autor);
    strcpy(Destino->editora, Origem->editora);
    Destino->ano = Origem->ano;
    Destino->edicao = Origem->edicao;
    Destino->exemplares = Origem->exemplares;
    Destino->ID = Origem->ID;
    Destino->preco = Origem->preco;
}

Livro* novoLivro() {
    Livro* livro = ALOC_LIVRO;
    memset(livro->titulo, 0, sizeof(livro->titulo));
    memset(livro->autor, 0, sizeof(livro->autor));
    memset(livro->editora, 0, sizeof(livro->editora));
    livro->ano = 0;
    livro->edicao = 0;
    livro->exemplares = 0;
    livro->ID = 0;
    livro->preco = 0;

    livro->esquerda = -1;
    livro->direita = -1;
    livro->pai = -1;
    livro->posAtual = -1;
}