#include "projeto.h"

int abrirMenuPrincipal() {
    limparTerminal();
    printf("\n======= Menu Principal =======\n"
           "1 - Menu de Livros\n"
           "2 - Outros\n"
           "0 - Encerrar\n"
           "==============================\n"
           "=> ");
           
    int op;
    scanf("%d", &op); ; limparBuffer();

    switch (op) {
        case 1 : while(abrirMenuLivros()); break;
        case 2 : while(abrirMenuOutros()); break;
        case 0 : break;
        default : ERRO_OPCAO;
    }

    return op;
}

int abrirMenuLivros() {
    limparTerminal();
    printf("\n======= Menu Livros =======\n"
           "1 - Remover livro\n"
           "2 - Listar livros\n"
           "3 - Listar registros livres\n"
           "4 - Total de livros\n"
           "0 - Voltar\n"
           "===========================\n"
           "=> ");

    int op;
    scanf("%d", &op); ; limparBuffer();

    switch (op) {
        case 1 : removerLivro(); break;
        case 2 : listarLivros(); break;
        case 3 : listarRegistrosLivres(); break;
        case 4 : totalLivros(); break;
        case 5 : novoLivroUsuario(); break;
        case 0 : break;
        default : ERRO_OPCAO;
    }
    
    return op;
}

int abrirMenuOutros() {
    limparTerminal();
    printf("\n======= Menu Outros =======\n"
           "1 - Criar arquivo de dados\n"
           "2 - Ler arquivo de texto\n"
           "3 - Imprimir niveis\n"
           "0 - Voltar\n"
           "===========================\n"
           "=> ");
           
    int op;
    scanf("%d", &op); ; limparBuffer();

    switch (op) {
        case 1 : criarArquivo(); break;
        case 2 : lerArquivo(); break;
        case 3 : imprimirArvorePorNivel(); break;
        case 123 : debugArquivoBinario(); break;
        case 0 : break;
        default : ERRO_OPCAO;
    }

    return op;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

char* tiraEspacos(char* str) {
    char *ini;
    ini = str;
    while(*ini == ' ') ini++;
    memmove(str, ini, strlen(ini) + 1);

    char* end;
    end = str + strlen(str) - 1;
    while(end >= str && *end == ' ')end--;
    *(end + 1) = '\0';

    return str; 
}

void pedirEnter() {
    printf("\nPressione ENTER para voltar...");
    while (getchar() != '\n');
}