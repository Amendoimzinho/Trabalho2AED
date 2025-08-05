#ifndef ARQBIN_H
#define ARQBIN_H

#include "projeto.h"

#define ARQUIVO "livros.bin"

#define ALOC_CABECALHO ((Cabecalho*)malloc(sizeof(Cabecalho)))

#define vazio(Livro_ptr) ((Livro_ptr->esquerda==-1)&&(Livro_ptr->direita==-1))
#define existe(r) (r!=-1)

typedef struct {
    int raizArvore,
        cabecaLivre,
        topo,
        qntLivros;
}Cabecalho;

void escreverLivro(Livro* livro);

void removerLivro(int pos);

void listarLivros();

void totalLivros();

void listarRegistrosLivres();

/* Auxiliares */

void criarArquivo();

Livro* pegarLivro(int pos);

void escreverCabecalho(Cabecalho* cab);

Cabecalho* pegarCabecalho();

/* - Arvore */

Livro* pegarMax(Livro* livro);

Livro* pegarMin(Livro* livro);


#endif