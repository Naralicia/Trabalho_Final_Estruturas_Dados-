#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"
#include "persistencia.h"
#include "terminal.h"

#define CSV_FILE "fila_impressao.csv"

void salvarCSV() {
    FILE *f = fopen(CSV_FILE, "w");
    int i, idx;

    if (!f) {
        mensagemErro("Erro ao abrir arquivo para escrita.");
        return;
    }

    fprintf(f, "id;arquivo;paginas;tipo\n");

    for (i = 0; i < filaPrioritaria.quantidade; i++) {
        idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
        fprintf(f, "%d;%s;%d;%c\n",
                filaPrioritaria.dados[idx].id,
                filaPrioritaria.dados[idx].arquivo,
                filaPrioritaria.dados[idx].paginas,
                filaPrioritaria.dados[idx].tipo);
    }

    for (i = 0; i < filaNormal.quantidade; i++) {
        idx = filaNormal.inicio + i;
        fprintf(f, "%d;%s;%d;%c\n",
                filaNormal.dados[idx].id,
                filaNormal.dados[idx].arquivo,
                filaNormal.dados[idx].paginas,
                filaNormal.dados[idx].tipo);
    }

    fclose(f);
    mensagemSucesso("Dados salvos com sucesso!");
}

void carregarCSV() {
    FILE *f = fopen(CSV_FILE, "r");
    char linha[200];
    int linhaNum = 0;
    int carregados = 0;

    if (!f) {
        mensagemAviso("Nenhum arquivo anterior encontrado. Iniciando vazio.");
        return;
    }

    while (fgets(linha, sizeof(linha), f)) {
        linhaNum++;
        linha[strcspn(linha, "\n")] = '\0';

        if (linhaNum == 1) continue;
        if (strlen(linha) == 0) continue;

        char *campoId      = strtok(linha, ";");
        char *campoArquivo = strtok(NULL, ";");
        char *campoPaginas = strtok(NULL, ";");
        char *campoTipo    = strtok(NULL, ";");

        if (!campoId || !campoArquivo || !campoPaginas || !campoTipo) {
            mensagemAviso("Linha invalida ignorada.");
            continue;
        }

        Trabalho t;
        t.id      = atoi(campoId);
        t.paginas = atoi(campoPaginas);
        t.tipo    = campoTipo[0];
        strncpy(t.arquivo, campoArquivo, TAM_ARQUIVO - 1);
        t.arquivo[TAM_ARQUIVO - 1] = '\0';

        if (t.tipo != 'N' && t.tipo != 'P') continue;
        if (t.paginas <= 0) continue;
        if (idJaExiste(t.id)) continue;

        if (t.tipo == 'P') {
            if (!enfileirarPrioritaria(t))
                mensagemErro("Fila prioritaria cheia ao carregar dados.");
            else carregados++;
        } else {
            if (!enfileirarNormal(t))
                mensagemErro("Fila normal cheia ao carregar dados.");
            else carregados++;
        }
    }

    fclose(f);
    printf("\n  %s%d trabalho(s) carregados.%s\n", COR_VERDE, carregados, COR_RESET);
}
