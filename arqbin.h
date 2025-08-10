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

/// @brief Pede um ID para o usuario, para remover
void removerLivro();

/// @brief Remove um livro, comeca a busca a partir do inicio
/// @param id ID a ser removido
/// @param inicio Posicao inicial da busca
/// @param cab Cabecalho do arquivo
void removerLivroAux(int id, int inicio, Cabecalho* cab);

/// @brief Remove um livro do arquivo e atualiza seu pai
/// @param aux Livro a ser removido
/// @param cab Cabecalho a ser atualizado
void deletarLivro(Livro* aux, Cabecalho* cab);

/// @brief Lista todos os livros da arvore (inOrder)
void listarLivros();

/// @brief Funcao recursiva que imprime livro por livro
/// @param pos Posicao do livro que vai ser printado
void listarLivrosAux(int pos);

/// @brief Imprime o total de livros cadastrados
void totalLivros();

/// @brief Imprime as posicoes disponiveis
void listarRegistrosLivres();

/// @brief Imprime os IDs cadastrados por nivel
void imprimirArvorePorNivel();

/* Funcoes de Arquivo */

/// @brief Adiciona um novo livro no arquivo
/// @param livro Livro a ser adicionado
void escreverNovoLivro(Livro* livro);

/// @brief Funcao auxiliar, ela ve se consegue adicionar na lista livre
/// @param livro Livro a ser adicionado
/// @param cab cabecalho do arquivo
/// @return A posicao na qual o livro foi adicionado
int guardarNovoLivro(Livro* livro, Cabecalho* cab);

/// @brief Escreve o livro na posicao dele
/// @param livro Livro a ser escrito
void escreverLivro(Livro* livro);

/// @brief Cria/Reseta o arquivo binario
void criarArquivo();

/// @brief Pega um livro na posicao enviada (sem error-warning!)
/// @param pos Posicao do livro
/// @return O ponteiro do livro encontrado
Livro* pegarLivro(int pos);

/// @brief Pega o cabecalho do arquivo
/// @return O ponteiro do cabecalho lido
Cabecalho* pegarCabecalho();

/// @brief Escreve o cabecalho no arquivo
/// @param cab Cabecalho a ser escrito
void escreverCabecalho(Cabecalho* cab);

/* Arvore */

/// @brief Pega o maior ID a partir da posicao enviada (sem error-warning!)
/// @param pos Posicao inicial
/// @return O ponteiro do livro com maior ID
Livro* pegarMax(int pos);

/// @brief Pega o menor ID a partir da posicao enviada (sem error-warning!)
/// @param pos Posicao inicial
/// @return O ponteiro do livro com menor ID
Livro* pegarMin(int pos);

/// @brief Procura o ID no arquivo
/// @param id ID a ser encontrado
/// @param inicio Posicao de inicio da busca
/// @return O livro encontrado ou NULL
Livro* pegarID(int id, int inicio);

/* DEBUG */

void debugArquivoBinario();

#endif