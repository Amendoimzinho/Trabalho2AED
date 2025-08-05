#include "arqbin.h"
#include "projeto.h"

void escreverNovoLivro(Livro* livro) {
    Cabecalho* cab = pegarCabecalho();
    Livro* L = pegarLivro(cab->raizArvore);

    Livro* aux = NULL;

    while (existe(L)) { 
        if(livro->ID >= L->ID){
            if(existe(L->direita)){
                aux = L;
                L = pegarLivro(L->direita);
                free(aux); aux = NULL;
            }
            else {
                livro->pai = L->posAtual;
                L->direita = guardarNovoLivro(livro, cab);
                escreverLivro(L);
                free(L); break;
            }
        }
        else if (livro->ID < L->ID){
            if(existe(L->esquerda)) {
                aux = L;
                L = pegarLivro(L->esquerda);
                free(aux); aux = NULL; 
            }
            else {
                livro->pai = L->posAtual;
                L->esquerda = guardarNovoLivro(livro, cab);
                escreverLivro(L);
                free(L); break;
            }
        }
    }

    escreverCabecalho(cab);

    free(cab); free(L); if(aux) free(aux);
}

void removerLivro(int id) {
    Cabecalho* cab = pegarCabecalho();
    Livro* livro = pegarID(id, cab);
    Livro* aux = NULL;

    if(!livro) {ERRO_ID; free(cab); return;}

    if(vazio(livro)) { // Se for uma "folha"
        aux = pegarLivro(livro->pai); // pega o pai de 'livro'
        if(livro->ID >= aux->ID) aux->direita = -1; // se livro>pai muda a direita
        else aux->esquerda = -1;                    // senao muda a esquerda
        free(aux); // Libera o pai
        livro->esquerda = cab->cabecaLivre; // Atualiza a lista de livres
        cab->cabecaLivre = livro->posAtual; // Atualiza a cabeca
        cab->qntLivros--; // Atualiza a quantidade de livros
        escreverLivro(livro); // Atualiza o livro no arquivo
        escreverCabecalho(cab); // Atualiza o cabecalho
        free(cab); free(livro); // libera tudo
    }
    else if(!existe(livro->esquerda)) { // Se nao tiver esquerda
        aux = pegarMin(livro->direita); // pega o minimo da direita
        copiarLivro(aux, livro); // Copia - menos os filhos
        removerLivro(aux->ID); // Remove a Folha encontrada
        free(aux); // libera o auxiliar
        escreverLivro(livro); // Atualiza no arquivo DEPOIS de ter deletado a folha
        free(cab); free(livro); // Libera tudo
    }
    else { // Se tiver esquerda 
        aux = pegarMax(livro->esquerda); // Pega o maximo da esquerda
        copiarLivro(aux, livro); // Copia
        removerLivro(aux->ID); // Remove a folha
        free(aux); // Libera o aux
        escreverLivro(livro); // Atualiza o livro
        free(cab); free(livro); // Libera
    }
}

void listarLivros() {
    Cabecalho* cab = pegarCabecalho();
    Livro* L = pegarLivro(cab->raizArvore);
    listarLivrosAux(L->ID, cab);
    free(L); free(cab);
}

void listarLivrosAux(int ID, Cabecalho* cab) {
    Livro* L = pegarID(ID, cab); free(cab);

    if(!L) return;

    Livro* aux = existe(L->esquerda) ? pegarLivro(L->esquerda) : NULL;
    if(aux) listarLivrosAux(aux->ID, cab); free(aux);

    imprimirLivro(L);

    aux = existe(L->direita) ? pegarLivro(L->direita) : NULL;
    if(aux) listarLivrosAux(aux->ID, cab); free(aux); free(L);
}

void totalLivros();

void listarRegistrosLivres();

/* Arvore */

int guardarNovoLivro(Livro* livro, Cabecalho* cab) {
    Livro* aux = NULL;

    if(existe(cab->cabecaLivre)) {
        livro->posAtual = cab->cabecaLivre;
        aux = pegarLivro(cab->cabecaLivre);
        cab->cabecaLivre = aux->esquerda;
        free(aux);
        escreverLivro(livro);
        cab->qntLivros++;
    }
    else {
        livro->posAtual = cab->topo++;
        escreverLivro(livro);
        cab->qntLivros++;
    }

    return livro->posAtual;
}

void escreverLivro(Livro* livro) {
    FILE* f = fopen(ARQUIVO, "r+b");
    if(!f) {ERRO_ARQ; return;}

    fseek(f, sizeof(Cabecalho) + sizeof(Livro)*livro->posAtual, SEEK_SET);
    fwrite(livro, sizeof(Livro), 1, f);

    fclose(f);
}

/* Auxiliares */

void criarArquivo() {
    FILE* f = fopen("livros.bin", "wb");
    fclose(f);

    Cabecalho cab;

    cab.raizArvore = -1;
    cab.cabecaLivre = -1;
    cab.qntLivros = 0;
    cab.topo = 0;

    escreverCabecalho(&cab);
}

Livro* pegarLivro(int pos) {
    FILE* f = fopen(ARQUIVO, "rb");
    if(!f) {ERRO_ARQ; return NULL;}

    Livro* livro = ALOC_LIVRO;
    if (!livro) {ERRO_ALOC_ARQ(f); return NULL;}

    fseek(f, sizeof(Cabecalho) + sizeof(Livro)*pos, SEEK_SET);
    fread(livro, sizeof(Livro), 1, f);

    fclose(f);

    return livro;
}

void escreverCabecalho(Cabecalho* cab) {
    FILE* f = fopen(ARQUIVO, "r+b");
    if(!f) ERRO_ARQ;

    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(Livro), 1, f);

    fclose(f);
}

Cabecalho* pegarCabecalho() {
    FILE* f = fopen(ARQUIVO, "rb");
    if(!f) ERRO_ARQ;

    Cabecalho* cab = ALOC_CABECALHO;
    if (!cab) ERRO_ALOC_ARQ(f);

    fseek(f, 0 , SEEK_SET);
    fread(cab, sizeof(Cabecalho), 1, f);

    fclose(f);

    return cab;
}

/* - Arvore */

Livro* pegarMax(Livro* livro) {
    Livro* L = livro;
    Livro* aux = NULL;
    while(existe(L->direita)) {
        aux = L;
        L = pegarLivro(L->direita);
        free(aux);
    }
    return L;
}

Livro* pegarMin(Livro* livro) {
    Livro* L = livro;
    Livro* aux = NULL;
    while(existe(L->esquerda)) {
        aux = L;
        L = pegarLivro(L->esquerda);
        free(aux);
    }
    return L;
}

Livro* pegarID(int id, Cabecalho* cab) {
    Livro* L = pegarLivro(cab->raizArvore);
    Livro* aux = NULL;
    while(existe(L)) {
        if(L->ID == id) return L;
        if(id > L->ID) {
            aux = L;
            L = existe(L->direita) ? pegarLivro(L->direita) : NULL;
            free(aux);
        }
        else {
            aux = L;
            L = existe(L->esquerda) ? pegarLivro(L->esquerda) : NULL;
            free(aux);
        }
    }
    return NULL;
}