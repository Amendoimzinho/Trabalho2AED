#include "arqbin.h"
#include "projeto.h"

void removerLivro() {
    printf("\n======= Remover Livro =======\n"
           "Digite o ID a ser removido\n"
           "=> ");
    int ID;
    scanf("%d", &ID); limparBuffer();

    Cabecalho* cab = pegarCabecalho();
    removerLivroAux(ID, cab->raizArvore ,cab);
    escreverCabecalho(cab); free(cab);

    printf("\nLivro removido\n");

    pedirEnter();
}

void removerLivroAux(int id, int inicio, Cabecalho* cab) {

    Livro* livro = pegarID(id, inicio);
    Livro* aux = NULL;

    if(!livro) {ERRO_ID; return;}

    if(folha(livro)) { // Se for uma "folha"
        erradicar(livro, cab);
        return;
    }

    if(!existe(livro->esquerda)) { // Se nao tiver esquerda
        aux = pegarMin(livro->direita); // Pega o maximo da esquerda
    }
    else { // Se tiver esquerda 
        aux = pegarMax(livro->esquerda); // Pega o maximo da esquerda
    }
    copiarLivro(aux, livro); // Copia
    escreverLivro(livro); // Atualiza o livro

    removerLivroAux(aux->ID, aux->posAtual, cab);

    free(aux); // Libera o aux
    free(livro); // Libera
}

void erradicar(Livro* aux, Cabecalho* cab){
    if(existe(aux->pai)){
        Livro* P = pegarLivro(aux->pai);
        if(P->esquerda == aux->posAtual) P->esquerda = -1;
        else P->direita = -1;
        escreverLivro(P); free(P);
    } 
    aux->esquerda = cab->cabecaLivre;
    cab->cabecaLivre = aux->posAtual;
    cab->qntLivros--;
    escreverLivro(aux);
}

void listarLivros() {
    printf("\n======= Livros Cadastrados =======\n");
    listarLivrosSet();
    pedirEnter();
}

void listarLivrosSet() {
    Cabecalho* cab = pegarCabecalho();
    Livro* L = pegarLivro(cab->raizArvore);
    listarLivrosAux(L->ID, cab);
    free(L); free(cab);
}

void listarLivrosAux(int ID, Cabecalho* cab) {
    Livro* L = pegarID(ID, cab->raizArvore);

    if(!L) return;

    Livro* aux = existe(L->esquerda) ? pegarLivro(L->esquerda) : NULL;
    if(aux) listarLivrosAux(aux->ID, cab); free(aux);

    imprimirLivro(L);

    aux = existe(L->direita) ? pegarLivro(L->direita) : NULL;
    if(aux) listarLivrosAux(aux->ID, cab); free(aux); free(L);
}

void totalLivros() {
    Cabecalho* cab = pegarCabecalho();
    printf("\nExistem (%d) livros cadastrados\n", cab->qntLivros);
    free(cab);
    pedirEnter();
}

void listarRegistrosLivres() {
    Cabecalho* cab = pegarCabecalho();
    int pos = cab->cabecaLivre;

    Livro* aux = NULL;

    printf("\n====== Registros Livres ======\n");
    
    while(existe(pos)) {
        free(aux);
        printf("-> %d\n", pos);
        aux = pegarLivro(pos);
        pos = aux->esquerda;
    }
    
    printf("\n==============================\n");
    
    free(aux); free(cab);

    pedirEnter();
}

void imprimirArvorePorNivel() {
    Cabecalho* cab = pegarCabecalho();
    if (!existe(cab->raizArvore)) {
        printf("\nArvore vazia!\n");
        free(cab);
        return;
    }

    // Cria uma fila simples
    int* fila = malloc(cab->qntLivros * sizeof(int));
    int inicio = 0, fim = 0;
    
    fila[fim++] = cab->raizArvore;  // Enfileira a raiz
    int nodesNoNivel = 1;
    int nodesProxNivel = 0;

    printf("\nArvore por niveis:\n");
    
    while (inicio < fim) {
        Livro* atual = pegarLivro(fila[inicio++]);
        nodesNoNivel--;
        
        printf("%d ", atual->ID);

        // Enfileira filhos
        if (existe(atual->esquerda)) {
            fila[fim++] = atual->esquerda;
            nodesProxNivel++;
        }
        if (existe(atual->direita)) {
            fila[fim++] = atual->direita;
            nodesProxNivel++;
        }

        // Quebra de linha quando termina um nível
        if (nodesNoNivel == 0) {
            printf("\n");
            nodesNoNivel = nodesProxNivel;
            nodesProxNivel = 0;
        }
        
        free(atual);
    }
    
    free(fila);
    free(cab);

    pedirEnter();
}

/* Funcoes de Arquivo */

void escreverNovoLivro(Livro* livro) {
    Cabecalho* cab = pegarCabecalho();

     if (!existe(cab->raizArvore)) {
        livro->pai = -1;  // Raiz não tem pai
        livro->posAtual = guardarNovoLivro(livro, cab);
        cab->raizArvore = livro->posAtual;
        escreverLivro(livro);
        escreverCabecalho(cab);
        free(cab);
        return;
    }

    Livro* L = pegarLivro(cab->raizArvore);
    Livro* aux = NULL;

    while (L) { 
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

void escreverCabecalho(Cabecalho* cab) {
    FILE* f = fopen(ARQUIVO, "r+b");
    if(!f) ERRO_ARQ;

    fseek(f, 0, SEEK_SET);
    fwrite(cab, sizeof(Cabecalho), 1, f);

    fclose(f);
}

/* Arvore */

Livro* pegarMax(int pos) {
    Livro* L = pegarLivro(pos);
    Livro* aux = NULL;
    while(existe(L->direita)) {
        aux = L;
        L = pegarLivro(L->direita);
        free(aux);
    }
    return L;
}

Livro* pegarMin(int pos) {
    Livro* L = pegarLivro(pos);
    Livro* aux = NULL;
    while(existe(L->esquerda)) {
        aux = L;
        L = pegarLivro(L->esquerda);
        free(aux);
    }
    return L;
}

Livro* pegarID(int id, int inicio) {
    Livro* L = existe(inicio) ? pegarLivro(inicio) : NULL;
    Livro* aux = NULL;
    while(L) {
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

/* DEBUG */

void debugArquivoBinario() {
    Cabecalho* cab = pegarCabecalho();
    if (!cab) return;

    printf("\n=== DEBUG ARQUIVO BINARIO ===\n");
    printf("Raiz: %d\n", cab->raizArvore);
    printf("Topo: %d\n", cab->topo);
    printf("Qtd Livros: %d\n", cab->qntLivros);
    printf("Cabeça Livre: %d\n", cab->cabecaLivre);

    printf("\n\n=== ESTRUTURA DA ARVORE ===");
    percorreArvore(cab->raizArvore);

    printf("\n\n=== REGISTROS LIVRES ===");
    int pos = cab->cabecaLivre;
    while (existe(pos)) {
        Livro* l = pegarLivro(pos);
        printf("\nPos %d (proximo: %d)", pos, l->esquerda);
        pos = l->esquerda;
        free(l);
    }

    printf("\n\n============================");
    free(cab);
    pedirEnter();
}

void percorreArvore(int pos) {
    if (!existe(pos)) return;
        
    Livro* l = pegarLivro(pos);
    if (!l) return;
        
    printf("\nPos %d: ID %d - %s", pos, l->ID, l->titulo);
    printf("\n  Esquerda: %d, Direita: %d, Pai: %d", l->esquerda, l->direita, l->pai);
        
    percorreArvore(l->esquerda);
    percorreArvore(l->direita);
        
    free(l);
}