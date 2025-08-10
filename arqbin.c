#include "arqbin.h"
#include "projeto.h"

void removerLivro() {
    printf("\n======= Remover Livro =======\n"
           "Digite o ID a ser removido\n"
           "=> ");
    int ID;
    scanf("%d", &ID); limparBuffer(); // Pede o ID a ser removido

    // Configura a recursao
    Cabecalho* cab = pegarCabecalho();
    removerLivroAux(ID, cab->raizArvore ,cab);
    escreverCabecalho(cab); free(cab);

    pedirEnter();
}

void removerLivroAux(int id, int inicio, Cabecalho* cab) { // Recursao que remove o livro

    Livro* livro = pegarID(id, inicio); // Pega o livro com o ID 
    Livro* aux = NULL;

    if(!livro) {ERRO_ID; return;} // Se nao encontrar avisa e retorna

    if(folha(livro)) { // Se for uma "folha"
        deletarLivro(livro, cab);
        printf("\nLivro removido!\n");
        return;
    }

    if(!existe(livro->esquerda)) { // Se nao tiver esquerda
        aux = pegarMin(livro->direita); // Pega o minimo da direita
    }
    else { // Se tiver esquerda 
        aux = pegarMax(livro->esquerda); // Pega o maximo da esquerda
    }
    copiarLivro(aux, livro); // Copia
    escreverLivro(livro); // Atualiza o livro

    removerLivroAux(aux->ID, aux->posAtual, cab); // Manda remover o livro copiado

    free(aux); // Libera o aux
    free(livro); // Libera
}

void deletarLivro(Livro* aux, Cabecalho* cab){
    if(existe(aux->pai)){ // Se tiver pai (nao eh raiz)
        Livro* P = pegarLivro(aux->pai); // Pega o pai
        if(P->esquerda == aux->posAtual) P->esquerda = -1; // Deleta a ligacao
        else P->direita = -1;
        escreverLivro(P); free(P); // Atualiza o pai
    } 
    aux->esquerda = cab->cabecaLivre; // Encadei na lista livre
    cab->cabecaLivre = aux->posAtual; // Atualiza lista livre
    cab->qntLivros--; // Remove um livro
    strcpy(aux->titulo, "DELETADO"); // Atualiza o titulo (para DEBUG)
    escreverLivro(aux); // Atualiza o livro (agora parte da lista livre) 
}

void listarLivros() {
    printf("\n======= Livros Cadastrados =======\n");

    // Configura a recursao
    Cabecalho* cab = pegarCabecalho();
    Livro* L = pegarLivro(cab->raizArvore);
    free(cab);
    listarLivrosAux(L->posAtual);
    free(L);

    pedirEnter();
}

void listarLivrosAux(int pos) {
    Livro* L = pegarLivro(pos); // Pega o livro

    if(!L) return; // Se de erro sai

    if(existe(L->esquerda)) listarLivrosAux(L->esquerda); // Se tiver esquerda imprime a esquerda

    imprimirLivro(L); // Imprime o atual

    if(existe(L->direita)) listarLivrosAux(L->direita); // Se tiver direita imprime a direita

    free(L);
}

void totalLivros() {
    Cabecalho* cab = pegarCabecalho(); // Pega o cabecalho
    printf("\nExistem (%d) livros cadastrados\n", cab->qntLivros); // Imprime a quantidade de Livros
    free(cab);
    pedirEnter();
}

void listarRegistrosLivres() {
    Cabecalho* cab = pegarCabecalho();// Pega o cabecalho
    int pos = cab->cabecaLivre; // Entao pega a cabeca da lista livre

    Livro* aux = NULL;

    printf("\n====== Registros Livres ======\n");
    
    while(existe(pos)) { // Enquanto existe a posicao (!= -1)
        free(aux);
        printf("-> %d ", pos); // Imprime a posicao
        aux = pegarLivro(pos); // Pega o novo livro
        pos = aux->esquerda; // Pega a nova posicao
    }
    
    printf("-> NULL"
           "\n==============================\n");
    
    free(aux); free(cab);

    pedirEnter();
}

void imprimirArvorePorNivel() {
    Cabecalho* cab = pegarCabecalho();
    
    // Verifica se a árvore está vazia
    if (!existe(cab->raizArvore)) {
        printf("\nArvore vazia!\n");
        free(cab);
        return;
    }

    int* fila = malloc(cab->qntLivros * sizeof(int)); // Fila para armazenar as posições dos nós a serem visitados
    int inicio = 0;  // Índice do início da fila
    int fim = 0;     // Índice do fim da fila
    
    // Inicia pela raiz da árvore
    fila[fim++] = cab->raizArvore;
    
    // Contadores para controlar a mudança de nível
    int nodesNoNivel = 1;     // Nós no nível atual
    int nodesProxNivel = 0;   // Nós no próximo nível

    printf("\nArvore por niveis:\n");
    
    // Processa enquanto houver nós na fila
    while (inicio < fim) {
        // Pega o próximo nó da fila
        Livro* atual = pegarLivro(fila[inicio++]);
        nodesNoNivel--;
        
        // Imprime o ID do nó atual
        printf("%d ", atual->ID);

        // Adiciona filho esquerdo na fila se existir
        if (existe(atual->esquerda)) {
            fila[fim++] = atual->esquerda;
            nodesProxNivel++;
        }
        
        // Adiciona filho direito na fila se existir
        if (existe(atual->direita)) {
            fila[fim++] = atual->direita;
            nodesProxNivel++;
        }

        // Quando terminar todos os nós do nível atual
        if (nodesNoNivel == 0) {
            printf("\n");  // Quebra de linha para novo nível
            nodesNoNivel = nodesProxNivel;  // Prepara próximo nível
            nodesProxNivel = 0;
        }
        
        free(atual);  // Libera memória do nó processado
    }
    
    free(fila);
    free(cab);

    pedirEnter();
}

/* Funcoes de Arquivo */

void escreverNovoLivro(Livro* livro) {
    Cabecalho* cab = pegarCabecalho(); // Pega o cabecalho

    if (!existe(cab->raizArvore)) { // Se a arvore estiver vazia
        livro->pai = -1;  // Raiz não tem pai
        cab->raizArvore = guardarNovoLivro(livro, cab); // Usa a funcao pq a lista livre pode ter espaco!!! e coloca a posicao como raiz
        escreverCabecalho(cab); // Atualiza o cabecalho
        free(cab);
        free(livro);
        return;
    }

    // Se nao tiver vazia

    Livro* L = pegarLivro(cab->raizArvore); // Pega a raiz
    Livro* aux = NULL;

    while (L) { 
        if(livro->ID >= L->ID){ // Se o ID for MAIOR que o no atual
            if(existe(L->direita)){ // Se tiver um no na direita
                aux = L; // Pega o ponteiro
                L = pegarLivro(L->direita); // Pega o proximo no
                free(aux); aux = NULL; // Libera o no antigo
            }
            else { // Se nao tiver ninguem tem que adicionar
                livro->pai = L->posAtual; // O pai do livro eh o no atual
                L->direita = guardarNovoLivro(livro, cab); // A direita desse no eh o livro adicionado
                escreverLivro(L); // Atualiza esse no
                free(L); break; // quebra o loop
            }
        }
        else if (livro->ID < L->ID){ // Se o ID for MENOR que o no atual | faz as mesmas coisas so q pra esquerda :)
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

    escreverCabecalho(cab); // Atualiza o cabecalho

    free(cab); free(L); if(aux) free(aux);
}

int guardarNovoLivro(Livro* livro, Cabecalho* cab) {
    Livro* aux = NULL;

    if(existe(cab->cabecaLivre)) { // Se tiver uma posicao livre
        livro->posAtual = cab->cabecaLivre; // A posicao desse livro vai ser a posicao livre
        aux = pegarLivro(cab->cabecaLivre); // Pega o no "livre"
        cab->cabecaLivre = aux->esquerda; // Atualiza a lista livre
        free(aux);
        escreverLivro(livro); // Escreve o novo livro
        cab->qntLivros++; // Aumenta a quantidade de livros
    }
    else { // Se nao tiver uma posicao livre
        livro->posAtual = cab->topo++; // A posicao sera o topo
        escreverLivro(livro); // Escreve no topo
        cab->qntLivros++;
    }

    return livro->posAtual; // Retorna a posicao onde o livro foi adicionado
}

void escreverLivro(Livro* livro) {
    FILE* f = fopen(ARQUIVO, "r+b"); // Abre o arquivo
    if(!f) {ERRO_ARQ; return;} // Verifica erro

    fseek(f, sizeof(Cabecalho) + sizeof(Livro)*livro->posAtual, SEEK_SET); // Encontra a posicao
    fwrite(livro, sizeof(Livro), 1, f); // Escreve

    fclose(f); // Fecha o arquivo
}

void criarArquivo() {
    FILE* f = fopen("livros.bin", "wb"); // Cria/Reseta o arquivo
    fclose(f); // Fecha o arquivo

    Cabecalho cab;

    // Inicia os campos com valores genericos
    cab.raizArvore = -1;
    cab.cabecaLivre = -1;
    cab.qntLivros = 0;
    cab.topo = 0;

    escreverCabecalho(&cab); // Escreve o novo cabecalho
}

Livro* pegarLivro(int pos) {
    FILE* f = fopen(ARQUIVO, "rb"); // Abre o arquivo
    if(!f) {ERRO_ARQ; return NULL;} // Se der erro avisa e sai

    Livro* livro = ALOC_LIVRO; // Aloca o livro
    if (!livro) {ERRO_ALOC_ARQ(f); return NULL;} // Se der erro sai

    fseek(f, sizeof(Cabecalho) + sizeof(Livro)*pos, SEEK_SET); // Encontra a posicao
    fread(livro, sizeof(Livro), 1, f); // Le o livro

    fclose(f); // Fecha o arquivo

    return livro; // Retorna o livro lido
}

Cabecalho* pegarCabecalho() {
    FILE* f = fopen(ARQUIVO, "rb"); // Abre o arquivo
    if(!f) {ERRO_ARQ; return NULL;} // Ser der erro avisa e sai

    Cabecalho* cab = ALOC_CABECALHO; // Aloca um cabecalho
    if (!cab) ERRO_ALOC_ARQ(f); // Se der erro avisa e sai

    fseek(f, 0 , SEEK_SET); // Vai pro inicio
    fread(cab, sizeof(Cabecalho), 1, f); // Le o cabecalho

    fclose(f); // Fecha o arquivo

    return cab; // Retorna o cabecalho
}

void escreverCabecalho(Cabecalho* cab) {
    FILE* f = fopen(ARQUIVO, "r+b"); // Abre o arquivo
    if(!f) {ERRO_ARQ; return;}

    fseek(f, 0, SEEK_SET); // Vai pro inicio
    fwrite(cab, sizeof(Cabecalho), 1, f); // Escreve o cabecalho

    fclose(f);
}

/* Arvore */

Livro* pegarMax(int pos) {
    Livro* L = pegarLivro(pos); // Pega o livro na posicao inicial da busca
    Livro* aux = NULL;
    while(existe(L->direita)) { // Se tiver como ir pra direita
        aux = L;
        L = pegarLivro(L->direita); // Vai pra direita
        free(aux);
    }
    return L; // Retorna o que encontrou
}

Livro* pegarMin(int pos) { // Mesma cois so que pra esquerda
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
    Livro* L = existe(inicio) ? pegarLivro(inicio) : NULL; // Se existir a posicao pega o livro
    Livro* aux = NULL;
    while(L) { // Enquanto o tiver um livro
        if(L->ID == id) return L; // Se encontrar retorna o que encontrou
        if(id > L->ID) { // Se estiver para direita
            aux = L;
            L = existe(L->direita) ? pegarLivro(L->direita) : NULL; // Se tiver como ir para direita vai para a direita ou NULL
            free(aux);
        }
        else { // Mesma coisa para a esquerda
            aux = L;
            L = existe(L->esquerda) ? pegarLivro(L->esquerda) : NULL;
            free(aux);
        }
    }
    return NULL; // Se nao encontrar retorna NULL
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

    printf("\n\n=== ESTRUTURA DA ARVORE ===\n");
    int pos = 0;
    Livro* aux = NULL;
    while(pos != cab->topo) {
        aux = pegarLivro(pos++);
        printf("Pos - (%d) | ID - (%d) | esq - (%d) | dir - (%d) | Titulo - %s\n", aux->posAtual, aux->ID, aux->esquerda, aux->direita, aux->titulo);
        free(aux);
    }

    printf("\n\n=== REGISTROS LIVRES ===");
    pos = cab->cabecaLivre;
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