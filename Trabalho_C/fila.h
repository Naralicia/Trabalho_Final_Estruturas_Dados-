#ifndef FILA_H
#define FILA_H

#define MAX_NORMAL       100
#define MAX_PRIORITARIA  50
#define TAM_ARQUIVO      50

typedef struct {
    int  id;
    char arquivo[TAM_ARQUIVO];
    int  paginas;
    char tipo;
} Trabalho;

typedef struct {
    Trabalho dados[MAX_NORMAL];
    int inicio;
    int fim;
    int quantidade;
} FilaNormal;

typedef struct {
    Trabalho dados[MAX_PRIORITARIA];
    int inicio;
    int fim;
    int quantidade;
} FilaCircular;

extern FilaNormal   filaNormal;
extern FilaCircular filaPrioritaria;

void inicializarFilas();
int  filaNormalCheia();
int  filaNormalVazia();
int  filaCircularCheia();
int  filaCircularVazia();
int  idJaExiste(int id);
int  enfileirarNormal(Trabalho t);
int  enfileirarPrioritaria(Trabalho t);
int  desenfileirarNormal(Trabalho *t);
int  desenfileirarPrioritaria(Trabalho *t);
void exibirTrabalho(Trabalho t);

#endif
