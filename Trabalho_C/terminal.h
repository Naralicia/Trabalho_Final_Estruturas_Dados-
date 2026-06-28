#ifndef TERMINAL_H
#define TERMINAL_H

#define COR_RESET    "\033[0m"
#define COR_VERMELHO "\033[1;31m"
#define COR_VERDE    "\033[1;32m"
#define COR_AMARELO  "\033[1;33m"
#define COR_AZUL     "\033[1;34m"
#define COR_MAGENTA  "\033[1;35m"
#define COR_CIANO    "\033[1;36m"
#define COR_BRANCO   "\033[1;37m"
#define COR_CINZA    "\033[0;37m"

void configurarTerminal();
void limparTela();
void pausar();
void cabecalho(const char *titulo);
void subcabecalho(const char *titulo);
void mensagemSucesso(const char *msg);
void mensagemErro(const char *msg);
void mensagemAviso(const char *msg);
void mensagemDestaque(const char *msg);

#endif
