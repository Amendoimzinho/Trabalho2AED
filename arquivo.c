#include "arquivo.h"
#include "projeto.h"

void lerArquivo() {
    limparTerminal();
    printf("\nDigite o diretorio do arquivo:\n=> ");
    
    char arq[301];
    scanf("%300[^\n]", arq);
    limparBuffer();

    FILE* input = fopen(arq, "r");
    if (!input) { ERRO_ARQ; return; }

    char buffer[500];
    
    while (fscanf(input, " %[^\n]", buffer) != EOF) {
        Livro* livro = novoLivro();
        
        if (sscanf(buffer, "%d;%150[^;];%200[^;];%51[^;];%d;%d;%d;%lf", &livro->ID ,
                                                                        livro->titulo,
                                                                        livro->autor, 
                                                                        livro->editora,
                                                                        &livro->edicao,
                                                                        &livro->exemplares, 
                                                                        &livro->ano, 
                                                                        &livro->preco) != 8) {
            ERRO_LEITURA;
            free(livro);
            continue;  // Pula linha inválida
        }

        strcpy(livro->titulo, tiraEspacos(livro->titulo));
        strcpy(livro->autor, tiraEspacos(livro->autor));
        strcpy(livro->editora , tiraEspacos(livro->editora));

        escreverNovoLivro(livro);
    }

    fclose(input);
}