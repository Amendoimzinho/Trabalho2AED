#ifndef ARQBIN_H
#define ARQBIN_H

typedef struct L Livro;

#include "projeto.h"
#include "livro.h"


#define ARQUIVO "livros.bin"

#define ALOC_CABECALHO ((Cabecalho*)malloc(sizeof(Cabecalho)))

#define folha(Livro_ptr) ((Livro_ptr->esquerda==-1)&&(Livro_ptr->direita==-1))
#define existe(r) (r!=-1)

/// @brief 
typedef struct {
    int raizArvore,
        cabecaLivre,
        topo,
        qntLivros;
}Cabecalho;

/// @brief 
void removerLivro();

/// @brief 
/// @param id 
/// @param inicio 
/// @param cab 
void removerLivroAux(int id, int inicio, Cabecalho* cab);

/// @brief 
/// @param aux 
/// @param cab 
void erradicar(Livro* aux, Cabecalho* cab);

/// @brief 
void listarLivros();

/// @brief 
void listarLivrosSet();

/// @brief 
/// @param ID 
/// @param cab 
void listarLivrosAux(int ID, Cabecalho* cab);

/// @brief 
void totalLivros();

/// @brief 
void listarRegistrosLivres();

/// @brief 
void imprimirArvorePorNivel();

/* Funcoes de Arquivo */

/// @brief 
/// @param livro 
void escreverNovoLivro(Livro* livro);

/// @brief 
/// @param livro 
/// @param cab 
/// @return 
int guardarNovoLivro(Livro* livro, Cabecalho* cab);

/// @brief 
/// @param livro 
void escreverLivro(Livro* livro);

/// @brief 
void criarArquivo();

/// @brief 
/// @param pos 
/// @return 
Livro* pegarLivro(int pos);

/// @brief 
/// @return 
Cabecalho* pegarCabecalho();

/// @brief 
/// @param cab 
void escreverCabecalho(Cabecalho* cab);

/* Arvore */

/// @brief 
/// @param pos 
/// @return 
Livro* pegarMax(int pos);

/// @brief 
/// @param pos 
/// @return 
Livro* pegarMin(int pos);

/// @brief 
/// @param id 
/// @param inicio 
/// @return 
Livro* pegarID(int id, int inicio);

/* DEBUG */

void debugArquivoBinario();

void percorreArvore(int pos);



#endif