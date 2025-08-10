#include "livro.h"
#include "projeto.h"

void imprimirLivro(Livro* livro) {
    printf("\n====== %s (%04d) ======", livro->titulo, livro->ano);
    printf("\nAutor: %s", livro->autor);
    printf("\nEditora: %s", livro->editora);
    printf("\nEdicao: %d", livro->edicao);
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

    return livro;
}

void novoLivroUsuario() {
    Livro* newLivro = novoLivro();
    if (!newLivro){ERRO_ALOC; return;}

    printf("====== Cadastrando Livro ======"
           "\n(digite apenas o pedido e cuidado com as quebras de linha!!)\n\n");

    printf("Digite o ID do Livro\n=> ");
    scanf("%d", &newLivro->ID); limparBuffer();
    printf("Digite o Titulo\n=> ");
    scanf("%150[^\n]", newLivro->titulo);limparBuffer();
    printf("Digite o nome do Autor:\n=> ");
    scanf("%200[^\n]", newLivro->autor);limparBuffer();
    printf("Digite o nome da Editora:\n=> ");
    scanf("%50[^\n]", newLivro->editora);limparBuffer();
    printf("Digite a Edicao:\n=> ");
    scanf("%d", &(newLivro->edicao));limparBuffer();
    printf("Digite o Ano:\n=> ");
    scanf("%d", &(newLivro->ano));limparBuffer();
    printf("Digite a quantidade de Exemplares:\n=> ");
    scanf("%d", &(newLivro->exemplares));limparBuffer();
    printf("Digite o preco (float):\n=> ");
    scanf("%f", &(newLivro->preco));limparBuffer();

    escreverNovoLivro(newLivro);
    free(newLivro);

    pedirEnter();
}