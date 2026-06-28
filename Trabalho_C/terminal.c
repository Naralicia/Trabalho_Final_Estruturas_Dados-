#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "terminal.h"

#define TAM_LINHA 46

void configurarTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut != INVALID_HANDLE_VALUE) {
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
}

void limparTela() {
    system("cls");
}

void pausar() {
    printf("\n  " COR_CINZA "Pressione Enter para continuar..." COR_RESET);
    while (getchar() != '\n');
}

static void linha(char c, const char *cor) {
    printf("  %s", cor);
    for (int i = 0; i < TAM_LINHA; i++) putchar(c);
    printf(COR_RESET "\n");
}

void cabecalho(const char *titulo) {
    printf("\n");
    linha('=', COR_AZUL);
    printf("  %s       %s       %s\n", COR_AZUL, titulo, COR_RESET);
    linha('=', COR_AZUL);
}

void subcabecalho(const char *titulo) {
    printf("\n  %s--- %s ---%s\n", COR_CIANO, titulo, COR_RESET);
}

void mensagemSucesso(const char *msg) {
    printf("  %s%s%s\n", COR_VERDE, msg, COR_RESET);
}

void mensagemErro(const char *msg) {
    printf("  %s%s%s\n", COR_VERMELHO, msg, COR_RESET);
}

void mensagemAviso(const char *msg) {
    printf("  %s%s%s\n", COR_AMARELO, msg, COR_RESET);
}

void mensagemDestaque(const char *msg) {
    printf("  %s%s%s\n", COR_MAGENTA, msg, COR_RESET);
}
