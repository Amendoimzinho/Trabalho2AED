#ifndef ARQBIN_H
#define ARQBIN_H

typedef struct L Livro;

#include "projeto.h"
#include "livro.h"


#define ARQUIVO "livros.bin"

#define ALOC_CABECALHO ((Cabecalho*)malloc(sizeof(Cabecalho)))

#define folha(Livro_ptr) ((Livro_ptr->esquerda==-1)&&(Livro_ptr->direita==-1))
#define existe(r) (r!=-1)

typedef struct {
    int raizArvore,
        cabecaLivre,
        topo,
        qntLivros;
}Cabecalho;

void escreverNovoLivro(Livro* livro);

void removerLivro();

void listarLivros();

void listarRegistrosLivres();

void totalLivros();

/* Auxiliares */

void criarArquivo();

/* Exclusivas de arqbin */

void removerLivroAux(int id);

int guardarNovoLivro(Livro* livro, Cabecalho* cab);

void escreverLivro(Livro* livro);

void listarLivrosSet();

void listarLivrosAux(int ID, Cabecalho* cab);

Livro* pegarLivro(int pos);

void escreverCabecalho(Cabecalho* cab);

Cabecalho* pegarCabecalho();

Livro* pegarMax(int pos);

Livro* pegarMin(int pos);

Livro* pegarID(int id, Cabecalho* cab);

#endif