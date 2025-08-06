#include "arquivo.h"
#include "projeto.h"

void lerArquivo() {
    limparTerminal();
    printf("\nDigite o diretorio do arquivo:\n=> ");
    
    char arq[301];
    scanf("%300[^\n]", arq);
    limparBuffer();

    FILE* input = fopen(arq, "r");
    if (!input) { ERRO_ARQ; pedirEnter(); return; }

    char buffer[500];
    
    while (fgets(buffer, sizeof(buffer), input)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';  // Remove \r e \n
        
        Livro* livro = novoLivro();
        if (!livro) { ERRO_ALOC; continue; }

        // Substitui vírgula por ponto no preço
        char* p = buffer;
        while (*p) {
            if (*p == ',') *p = '.';
            p++;
        }

        if (sscanf(buffer, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%f", 
                  &livro->ID, livro->titulo, livro->autor, livro->editora,
                  &livro->edicao, &livro->ano, &livro->exemplares, &livro->preco) != 8) {
            ERRO_LEITURA;
            free(livro);
            continue;
        }

        strcpy(livro->titulo, tiraEspacos(livro->titulo));
        strcpy(livro->autor, tiraEspacos(livro->autor));
        strcpy(livro->editora, tiraEspacos(livro->editora));

        escreverNovoLivro(livro);
        free(livro);
    }

    fclose(input);
    pedirEnter();
}