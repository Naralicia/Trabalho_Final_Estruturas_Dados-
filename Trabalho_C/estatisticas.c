#include <stdio.h>
#include "fila.h"
#include "estatisticas.h"
#include "terminal.h"

/* ===================== ESTATÍSTICAS ===================== */
static int totalTrabalhos() {
    return filaNormal.quantidade + filaPrioritaria.quantidade;
}

static int totalPaginas() {
    int total = 0, i, idx;

    for (i = 0; i < filaPrioritaria.quantidade; i++) {
        idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
        total += filaPrioritaria.dados[idx].paginas;
    }

    for (i = 0; i < filaNormal.quantidade; i++) {
        idx = filaNormal.inicio + i;
        total += filaNormal.dados[idx].paginas;
    }

    return total;
}

static void maiorMenorTrabalho(Trabalho *maior, Trabalho *menor) {
    int i, idx, primeiro = 1;

    for (i = 0; i < filaPrioritaria.quantidade; i++) {
        idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
        if (primeiro || filaPrioritaria.dados[idx].paginas > maior->paginas)
            *maior = filaPrioritaria.dados[idx];
        if (primeiro || filaPrioritaria.dados[idx].paginas < menor->paginas)
            *menor = filaPrioritaria.dados[idx];
        primeiro = 0;
    }

    for (i = 0; i < filaNormal.quantidade; i++) {
        idx = filaNormal.inicio + i;
        if (primeiro || filaNormal.dados[idx].paginas > maior->paginas)
            *maior = filaNormal.dados[idx];
        if (primeiro || filaNormal.dados[idx].paginas < menor->paginas)
            *menor = filaNormal.dados[idx];
        primeiro = 0;
    }
}

/* ===================== RELATÓRIOS ===================== */
static void relatorioCompleto() {
    int total = totalTrabalhos();
    int paginas = totalPaginas();

    printf("\n");
    cabecalho("RELATORIO COMPLETO");

    printf("  %sTotal de trabalhos:%s %d\n", COR_BRANCO, COR_RESET, total);
    printf("  %sTotal de paginas:%s  %d\n", COR_BRANCO, COR_RESET, paginas);

    if (total > 0) {
        printf("  %sMedia de paginas:%s   %.1f\n", COR_BRANCO, COR_RESET, (double)paginas / total);

        Trabalho maior, menor;
        maiorMenorTrabalho(&maior, &menor);

        printf("\n  %s--- Maior trabalho ---%s\n", COR_VERDE, COR_RESET);
        exibirTrabalho(maior);
        printf("\n  %s--- Menor trabalho ---%s\n", COR_AMARELO, COR_RESET);
        exibirTrabalho(menor);
    }

    printf("\n  %sOcupacao das Filas:%s\n", COR_BRANCO, COR_RESET);
    printf("  Prioritaria: %s%d/%d%s (%.0f%%)\n",
           COR_CIANO, filaPrioritaria.quantidade, MAX_PRIORITARIA, COR_RESET,
           (double)filaPrioritaria.quantidade / MAX_PRIORITARIA * 100);
    printf("  Normal:      %s%d/%d%s (%.0f%%)\n",
           COR_CIANO, filaNormal.quantidade, MAX_NORMAL, COR_RESET,
           (double)filaNormal.quantidade / MAX_NORMAL * 100);

    printf("\n  %sDistribuicao por Tipo:%s\n", COR_BRANCO, COR_RESET);
    printf("  Prioritarios: %s%d%s (%.0f%%)\n",
           COR_MAGENTA, filaPrioritaria.quantidade, COR_RESET,
           total > 0 ? (double)filaPrioritaria.quantidade / total * 100 : 0);
    printf("  Normais:      %s%d%s (%.0f%%)\n",
           COR_AZUL, filaNormal.quantidade, COR_RESET,
           total > 0 ? (double)filaNormal.quantidade / total * 100 : 0);

    printf("  %s", COR_AZUL);
    for (int i = 0; i < 46; i++) putchar('=');
    printf("%s\n", COR_RESET);
}

static void relatorioResumido() {
    int total = totalTrabalhos();
    int paginas = totalPaginas();

    printf("\n");
    subcabecalho("Relatorio Resumido");
    printf("  %sTrabalhos:%s %d  %sPaginas:%s %d",
           COR_BRANCO, COR_RESET, total,
           COR_BRANCO, COR_RESET, paginas);
    if (total > 0)
        printf("  %sMedia:%s %.1f", COR_BRANCO, COR_RESET, (double)paginas / total);
    printf("\n");
    printf("  %sPrioritarios:%s %d  %sNormais:%s %d\n",
           COR_MAGENTA, COR_RESET, filaPrioritaria.quantidade,
           COR_AZUL, COR_RESET, filaNormal.quantidade);
    printf("  %sOcupacao:%s P=%d/%d  N=%d/%d\n",
           COR_CINZA, COR_RESET,
           filaPrioritaria.quantidade, MAX_PRIORITARIA,
           filaNormal.quantidade, MAX_NORMAL);
}

/* ===================== MENU DE RELATÓRIOS ===================== */
void operacaoRelatorios() {
    int opcao;

    do {
        limparTela();
        cabecalho("RELATORIOS E ESTATISTICAS");
        printf("  %s 1.%s Relatorio completo\n", COR_AMARELO, COR_RESET);
        printf("  %s 2.%s Relatorio resumido\n", COR_AMARELO, COR_RESET);
        printf("  %s 0.%s Voltar\n", COR_VERMELHO, COR_RESET);
        printf("  Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            mensagemErro("Entrada invalida.");
            while (getchar() != '\n');
            opcao = -1;
            pausar();
            continue;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                limparTela();
                relatorioCompleto();
                pausar();
                break;
            case 2:
                limparTela();
                relatorioResumido();
                pausar();
                break;
            case 0:
                break;
            default:
                mensagemErro("Opcao invalida.");
                pausar();
        }
    } while (opcao != 0);
}
