#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int protocolo;
    char local[100];
    char ocorrencia[100];
    char horario[10];
} Chamada;

Chamada pilha[MAX];
int topo = -1; // -1 indica que a pilha está vazia

// Validação de Protocolo Único
int protocoloExiste(int prot) {
    for (int i = 0; i <= topo; i++) {
        if (pilha[i].protocolo == prot) {
            return 1;
        }
    }
    return 0;
}

// 1. REGISTRAR CHAMADA (Empilhar - Push)
void registrarChamada() {
    if (topo == MAX - 1) {
        printf("\n[ERRO] A pilha de chamadas esta cheia!\n");
        return;
    }

    Chamada novaChamada;
    int prot;

    printf("\n--- REGISTRAR NOVA CHAMADA DE EMERGENCIA ---\n");
    printf("----------------------------------------------------------------------\n");
    printf(" DICAS DE PREENCHIMENTO:\n");
    printf("  -> Protocolo: Digite apenas numeros (Ex: 1001)\n");
    printf("  -> Local: Nome da rua, numero, ponto de referencia (Ex: Avenida ACM, em frente ao Shopping da Bahia)\n");
    printf("  -> Ocorrencia: Ex: Roubo (190), Incendio (193), Parada cardiaca (192)\n");
    printf("  -> Horario: Formato HH:MM (Ex: 13:16)\n");
    printf("----------------------------------------------------------------------\n");
    
    do {
        printf("Digite o numero do protocolo: ");
        scanf("%d", &prot);
        getchar();
        
        if (protocoloExiste(prot)) {
            printf("[AVISO] Este protocolo ja existe! Tente outro.\n");
        }
    } while (protocoloExiste(prot));
    
    novaChamada.protocolo = prot;

    printf("Digite o local da ocorrencia: ");
    fgets(novaChamada.local, 100, stdin);
    novaChamada.local[strcspn(novaChamada.local, "\n")] = 0;

    printf("Digite o tipo da ocorrencia: ");
    fgets(novaChamada.ocorrencia, 100, stdin);
    novaChamada.ocorrencia[strcspn(novaChamada.ocorrencia, "\n")] = 0;

    printf("Digite o horario (HH:MM): ");
    fgets(novaChamada.horario, 10, stdin);
    novaChamada.horario[strcspn(novaChamada.horario, "\n")] = 0;

    // Lógica LIFO: incrementa o topo e insere
    topo++;
    pilha[topo] = novaChamada;

    printf("\n[SUCESSO] Chamada registrada com sucesso no topo da pilha!\n");
}

// 2. ATENDER CHAMADA (Desempilhar - Pop)
void atenderChamada() {
    if (topo == -1) {
        printf("\n[AVISO] Nao ha chamadas na fila para serem atendidas.\n");
        return;
    }

    // O último que entrou é o primeiro que sai (LIFO)
    Chamada atendida = pilha[topo];
    
    printf("\n--- ATENDENDO CHAMADA (TOPO DA PILHA) ---\n");
    printf("Protocolo: %d\n", atendida.protocolo);
    printf("Local: %s\n", atendida.local);
    printf("Ocorrencia: %s\n", atendida.ocorrencia);
    printf("Horario: %s\n", atendida.horario);
    printf("----------------------------------------\n");

    topo--; // Remove o elemento do topo
    printf("[SUCESSO] Chamada atendida e removida da pilha.\n");
}

// 3. CONSULTAR ÚLTIMA CHAMADA (Verificar Topo - Peek)
void consultarUltimaChamada() {
    if (topo == -1) {
        printf("\n[AVISO] Nenhuma chamada registrada ate o momento.\n");
        return;
    }

    Chamada ultima = pilha[topo];
    printf("\n--- ULTIMA CHAMADA REGISTRADA (TOPO) ---\n");
    printf("Protocolo: %d\n", ultima.protocolo);
    printf("Local: %s\n", ultima.local);
    printf("Ocorrencia: %s\n", ultima.ocorrencia);
    printf("Horario: %s\n", ultima.horario);
}

// 4. LISTAR TODAS AS CHAMADAS (Do topo para a base)
void listarChamadas() {
    if (topo == -1) {
        printf("\n[AVISO] Nao ha chamadas para listar.\n");
        return;
    }

    printf("\n--- LISTAGEM DE TODAS AS CHAMADAS (DO TOPO DA PILHA PARA A BASE) ---\n");
    for (int i = topo; i >= 0; i--) {
        printf("[%d] Protocolo: %d | Local: %s | Ocorrencia: %s | Horario: %s\n", 
               i, pilha[i].protocolo, pilha[i].local, pilha[i].ocorrencia, pilha[i].horario);
    }
}

// 5. SALVAR EM ARQUIVO CSV
void salvarCSV() {
    FILE *arquivo = fopen("chamadas.csv", "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel criar o arquivo CSV.\n");
        return;
    }

    fprintf(arquivo, "Protocolo;Local;Ocorrencia;Horario\n");

    for (int i = 0; i <= topo; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n", 
                pilha[i].protocolo, pilha[i].local, pilha[i].ocorrencia, pilha[i].horario);
    }

    fclose(arquivo);
    printf("\n[SUCESSO] Dados salvos em 'chamadas.csv' com sucesso!\n");
}

// 6. CARREGAR DO ARQUIVO CSV
void carregarCSV() {
    FILE *arquivo = fopen("chamadas.csv", "r");
    if (arquivo == NULL) {
        printf("\n[AVISO] Arquivo 'chamadas.csv' nao encontrado. Iniciando pilha vazia.\n");
        return;
    }

    char linha[300];
    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    topo = -1;

    while (fgets(linha, sizeof(linha), arquivo) && topo < MAX - 1) {
        topo++;
        linha[strcspn(linha, "\n")] = 0;

        char *token = strtok(linha, ";");
        if (token != NULL) pilha[topo].protocolo = atoi(token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(pilha[topo].local, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(pilha[topo].ocorrencia, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(pilha[topo].horario, token);
    }

    fclose(arquivo);
    printf("\n[SUCESSO] Dados carregados do arquivo CSV com sucesso! Total de registros: %d\n", topo + 1);
}

int main() {
    int opcao;

    carregarCSV(); // Carrega os dados automaticamente ao abrir

    do {
        printf("\n======================================================================\n");
        printf("               SISTEMA DE CHAMADAS DE EMERGENCIA (PILHA)              \n");
        printf("======================================================================\n");
        printf(" GUIA RAPIDO DE REFERENCIA DE EMERGENCIAS:\n");
        printf("  * POLICIA MILITAR (190): Roubo, perturbacao do sossego, agressao.\n");
        printf("  * BOMBEIROS (193): Incendio, vazamento de gas, resgate de animais.\n");
        printf("  * SAMU (192): Parada cardiorrespiratoria, atropelamento, acidentes graves.\n");
        printf("----------------------------------------------------------------------\n");
        printf("1. Registrar Chamada (Empilhar)\n");
        printf("2. Atender Chamada (Desempilhar)\n");
        printf("3. Consultar Ultima Chamada (Topo)\n");
        printf("4. Listar Todas as Chamadas\n");
        printf("5. Salvar Dados (CSV)\n");
        printf("0. Sair do Programa\n");
        printf("======================================================================\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: registrarChamada(); break;
            case 2: atenderChamada(); break;
            case 3: consultarUltimaChamada(); break;
            case 4: listarChamadas(); break;
            case 5: salvarCSV(); break;
            case 0:
                printf("\nSalvando dados automaticamente antes de sair...\n");
                salvarCSV();
                printf("Saindo do sistema. Ate logo!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}