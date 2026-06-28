#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "fila.h"
#include "persistencia.h"
#include "estatisticas.h"
#include "terminal.h"

/* ===================== OPERAÇÃO: ENFILEIRAR ===================== */
void operacaoEnfileirar() {
    Trabalho t;
    char tipoStr[10];

    limparTela();
    cabecalho("ENFILEIRAR TRABALHO");

    printf("  ID: ");
    if (scanf("%d", &t.id) != 1) {
        mensagemErro("ID invalido.");
        while (getchar() != '\n');
        pausar();
        return;
    }
    while (getchar() != '\n');

    if (idJaExiste(t.id)) {
        mensagemErro("ID ja existe na fila.");
        pausar();
        return;
    }

    printf("  Nome do arquivo: ");
    fgets(t.arquivo, TAM_ARQUIVO, stdin);
    t.arquivo[strcspn(t.arquivo, "\n")] = '\0';

    if (strlen(t.arquivo) == 0) {
        mensagemErro("Nome do arquivo nao pode ser vazio.");
        pausar();
        return;
    }

    printf("  Paginas: ");
    if (scanf("%d", &t.paginas) != 1 || t.paginas <= 0) {
        mensagemErro("Numero de paginas invalido.");
        while (getchar() != '\n');
        pausar();
        return;
    }
    while (getchar() != '\n');

    printf("  Tipo (N=Normal / P=Prioritario): ");
    fgets(tipoStr, sizeof(tipoStr), stdin);
    t.tipo = tipoStr[0];

    if (t.tipo != 'N' && t.tipo != 'P' && t.tipo != 'n' && t.tipo != 'p') {
        mensagemErro("Tipo invalido. Use N ou P.");
        pausar();
        return;
    }
    t.tipo = (t.tipo == 'n') ? 'N' : (t.tipo == 'p') ? 'P' : t.tipo;

    if (t.tipo == 'P') {
        if (enfileirarPrioritaria(t))
            mensagemSucesso("Trabalho adicionado a fila PRIORITARIA!");
    } else {
        if (enfileirarNormal(t))
            mensagemSucesso("Trabalho adicionado a fila NORMAL!");
    }
    pausar();
}

/* ===================== OPERAÇÃO: PROCESSAR ===================== */
void operacaoProcessar() {
    Trabalho t;
    int ok = 0;

    limparTela();
    cabecalho("PROCESSAR TRABALHO");

    if (!filaCircularVazia()) {
        ok = desenfileirarPrioritaria(&t);
        mensagemDestaque("[PRIORITARIO] Processando:");
    } else if (!filaNormalVazia()) {
        ok = desenfileirarNormal(&t);
        mensagemDestaque("[NORMAL] Processando:");
    }

    if (ok) {
        exibirTrabalho(t);
        mensagemSucesso("Trabalho concluido e removido da fila.");
    } else {
        mensagemAviso("Nenhum trabalho nas filas.");
    }
    pausar();
}

/* ===================== OPERAÇÃO: LISTAR ===================== */
void operacaoListar() {
    int i, idx;

    limparTela();
    cabecalho("LISTAR FILAS");

    subcabecalho("Fila Prioritaria (Circular)");
    printf("  %s%d trabalho(s)%s\n", COR_CIANO, filaPrioritaria.quantidade, COR_RESET);
    if (filaCircularVazia()) {
        mensagemAviso("(vazia)");
    } else {
        for (i = 0; i < filaPrioritaria.quantidade; i++) {
            idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
            printf("  %s[%d]%s ", COR_AMARELO, i + 1, COR_RESET);
            exibirTrabalho(filaPrioritaria.dados[idx]);
        }
    }

    subcabecalho("Fila Normal");
    printf("  %s%d trabalho(s)%s\n", COR_CIANO, filaNormal.quantidade, COR_RESET);
    if (filaNormalVazia()) {
        mensagemAviso("(vazia)");
    } else {
        for (i = 0; i < filaNormal.quantidade; i++) {
            idx = filaNormal.inicio + i;
            printf("  %s[%d]%s ", COR_AMARELO, i + 1, COR_RESET);
            exibirTrabalho(filaNormal.dados[idx]);
        }
    }
    pausar();
}

/* ===================== OPERAÇÃO: BUSCAR ===================== */
void operacaoBuscar() {
    int id, i, idx, encontrado = 0;

    limparTela();
    cabecalho("BUSCAR TRABALHO");
    printf("  ID: ");
    if (scanf("%d", &id) != 1) {
        mensagemErro("ID invalido.");
        while (getchar() != '\n');
        pausar();
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < filaPrioritaria.quantidade; i++) {
        idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
        if (filaPrioritaria.dados[idx].id == id) {
            printf("  %sEncontrado na fila PRIORITARIA (posicao %d):%s\n", COR_VERDE, i + 1, COR_RESET);
            exibirTrabalho(filaPrioritaria.dados[idx]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        for (i = 0; i < filaNormal.quantidade; i++) {
            idx = filaNormal.inicio + i;
            if (filaNormal.dados[idx].id == id) {
                printf("  %sEncontrado na fila NORMAL (posicao %d):%s\n", COR_VERDE, i + 1, COR_RESET);
                exibirTrabalho(filaNormal.dados[idx]);
                encontrado = 1;
                break;
            }
        }
    }

    if (!encontrado)
        mensagemErro("Trabalho nao encontrado.");
    pausar();
}

/* ===================== OPERAÇÃO: CANCELAR ===================== */
void operacaoCancelar() {
    int id, i, idx, encontrado = 0;

    limparTela();
    cabecalho("CANCELAR TRABALHO");
    printf("  ID: ");
    if (scanf("%d", &id) != 1) {
        mensagemErro("ID invalido.");
        while (getchar() != '\n');
        pausar();
        return;
    }
    while (getchar() != '\n');

    for (i = 0; i < filaPrioritaria.quantidade && !encontrado; i++) {
        idx = (filaPrioritaria.inicio + i) % MAX_PRIORITARIA;
        if (filaPrioritaria.dados[idx].id == id) {
            printf("  Cancelando da fila PRIORITARIA: %s\n",
                   filaPrioritaria.dados[idx].arquivo);
            int j;
            for (j = i; j < filaPrioritaria.quantidade - 1; j++) {
                int cur  = (filaPrioritaria.inicio + j)     % MAX_PRIORITARIA;
                int prox = (filaPrioritaria.inicio + j + 1) % MAX_PRIORITARIA;
                filaPrioritaria.dados[cur] = filaPrioritaria.dados[prox];
            }
            filaPrioritaria.fim = (filaPrioritaria.fim - 1 + MAX_PRIORITARIA) % MAX_PRIORITARIA;
            filaPrioritaria.quantidade--;
            encontrado = 1;
        }
    }

    if (!encontrado) {
        for (i = 0; i < filaNormal.quantidade && !encontrado; i++) {
            idx = filaNormal.inicio + i;
            if (filaNormal.dados[idx].id == id) {
                printf("  Cancelando da fila NORMAL: %s\n",
                       filaNormal.dados[idx].arquivo);
                int j;
                for (j = idx; j < filaNormal.fim - 1; j++) {
                    filaNormal.dados[j] = filaNormal.dados[j + 1];
                }
                filaNormal.fim--;
                filaNormal.quantidade--;
                if (filaNormal.quantidade == 0) {
                    filaNormal.inicio = 0;
                    filaNormal.fim    = 0;
                }
                encontrado = 1;
            }
        }
    }

    if (encontrado)
        mensagemSucesso("Trabalho cancelado com sucesso.");
    else
        mensagemErro("Trabalho nao encontrado.");
    pausar();
}

/* ===================== MENU ===================== */
void exibirMenu() {
    limparTela();
    printf("\n");
    printf("  %s========================================%s\n", COR_AZUL, COR_RESET);
    printf("  %s     SISTEMA DE FILA DE IMPRESSAO%s\n", COR_BRANCO, COR_RESET);
    printf("  %s========================================%s\n", COR_AZUL, COR_RESET);
    printf("  %s 1.%s Enfileirar trabalho\n", COR_AMARELO, COR_RESET);
    printf("  %s 2.%s Processar proximo\n", COR_AMARELO, COR_RESET);
    printf("  %s 3.%s Listar filas\n", COR_AMARELO, COR_RESET);
    printf("  %s 4.%s Buscar trabalho por ID\n", COR_AMARELO, COR_RESET);
    printf("  %s 5.%s Cancelar trabalho por ID\n", COR_AMARELO, COR_RESET);
    printf("  %s 6.%s Salvar dados (CSV)\n", COR_AMARELO, COR_RESET);
    printf("  %s 7.%s Relatorios e Estatisticas\n", COR_MAGENTA, COR_RESET);
    printf("  %s 0.%s Sair\n", COR_VERMELHO, COR_RESET);
    printf("  %s========================================%s\n", COR_AZUL, COR_RESET);
    printf("  Opcao: ");
}

/* ===================== MAIN ===================== */
int main() {
    int opcao;

    configurarTerminal();
    setlocale(LC_ALL, "");
    inicializarFilas();

    limparTela();
    cabecalho("SISTEMA DE FILA DE IMPRESSAO");
    mensagemDestaque("Bem-vindo ao sistema de gerenciamento de filas!");
    carregarCSV();
    pausar();

    do {
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            mensagemErro("Entrada invalida.");
            while (getchar() != '\n');
            opcao = -1;
            pausar();
            continue;
        }
        while (getchar() != '\n');

        switch (opcao) {
            case 1: operacaoEnfileirar(); break;
            case 2: operacaoProcessar();  break;
            case 3: operacaoListar();     break;
            case 4: operacaoBuscar();     break;
            case 5: operacaoCancelar();   break;
            case 6:
                limparTela();
                cabecalho("SALVAR DADOS");
                salvarCSV();
                pausar();
                break;
            case 7: operacaoRelatorios(); break;
            case 0:
                limparTela();
                cabecalho("ENCERRANDO");
                mensagemAviso("Salvando dados antes de sair...");
                salvarCSV();
                mensagemSucesso("Ate logo!");
                pausar();
                break;
            default:
                mensagemErro("Opcao invalida.");
                pausar();
        }
    } while (opcao != 0);

    return 0;
}
