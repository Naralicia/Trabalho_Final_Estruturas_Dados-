#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "terminal.h"

FilaNormal   filaNormal;
FilaCircular filaPrioritaria;

/* ===================== INICIALIZAÇÃO ===================== */
void inicializarFilas() {
    filaNormal.inicio    = 0;
    filaNormal.fim       = 0;
    filaNormal.quantidade = 0;

    filaPrioritaria.inicio    = 0;
    filaPrioritaria.fim       = 0;
    filaPrioritaria.quantidade = 0;
}

/* ===================== VERIFICAÇÕES ===================== */
int filaNormalCheia()      { return filaNormal.quantidade == MAX_NORMAL; }
int filaNormalVazia()      { return filaNormal.quantidade == 0; }
int filaCircularCheia()    { return filaPrioritaria.quantidade == MAX_PRIORITARIA; }
int filaCircularVazia()    { return filaPrioritaria.quantidade == 0; }

/* ===================== BUSCA POR ID ===================== */
int idJaExiste(int id) {
    int i, idx;

    for (i = 0; i < filaNormal.quantidade; i++) {
        idx = filaNormal.inicio + i;
        if (filaNormal.dados[idx].id == id) return 1;
    }

    for (i = 0; i < filaPrioritaria.quantidade; i++) {
        idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
        if (filaPrioritaria.dados[idx].id == id) return 1;
    }

    return 0;
}

/* ===================== ENFILEIRAR ===================== */
int enfileirarNormal(Trabalho t) {
    if (filaNormalCheia()) {
        printf("  %sFila normal cheia!%s\n", COR_VERMELHO, COR_RESET);
        return 0;
    }
    filaNormal.dados[filaNormal.fim] = t;
    filaNormal.fim++;
    filaNormal.quantidade++;
    return 1;
}

int enfileirarPrioritaria(Trabalho t) {
    if (filaCircularCheia()) {
        printf("  %sFila prioritaria cheia!%s\n", COR_VERMELHO, COR_RESET);
        return 0;
    }
    filaPrioritaria.dados[filaPrioritaria.fim] = t;
    filaPrioritaria.fim = (filaPrioritaria.fim + 1) % MAX_PRIORITARIA;
    filaPrioritaria.quantidade++;
    return 1;
}

/* ===================== DESENFILEIRAR ===================== */
int desenfileirarNormal(Trabalho *t) {
    if (filaNormalVazia()) return 0;
    *t = filaNormal.dados[filaNormal.inicio];
    filaNormal.inicio++;
    filaNormal.quantidade--;
    if (filaNormal.quantidade == 0) {
        filaNormal.inicio = 0;
        filaNormal.fim    = 0;
    }
    return 1;
}

int desenfileirarPrioritaria(Trabalho *t) {
    if (filaCircularVazia()) return 0;
    *t = filaPrioritaria.dados[filaPrioritaria.inicio];
    filaPrioritaria.inicio = (filaPrioritaria.inicio + 1) % MAX_PRIORITARIA;
    filaPrioritaria.quantidade--;
    return 1;
}

/* ===================== EXIBIR ===================== */
void exibirTrabalho(Trabalho t) {
    printf("  ID: %s%d%s | Arquivo: %-30s | Paginas: %s%3d%s | Tipo: %s\n",
           COR_AMARELO, t.id, COR_RESET,
           t.arquivo,
           COR_CIANO, t.paginas, COR_RESET,
           t.tipo == 'P' ? "Prioritario" : "Normal");
}
