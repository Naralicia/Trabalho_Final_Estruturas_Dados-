#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX 100
#define ARQUIVO "playlist.csv"

typedef struct {
    int id;
    char titulo[50];
    char artista[50];
    int duracao; // armazenada em segundos
    char genero[30];
} Musica;

Musica playlist[MAX];
int qtd = 0;

// lê duração no formato MM:SS e retorna total em segundos
// Retorna -1 se o formato for inválido
int ler_duracao() {
    int m, s;
    char buf[20];
    fgets(buf, sizeof(buf), stdin);
    if (sscanf(buf, "%d:%d", &m, &s) != 2 ||
        m < 0 || s < 0 || s > 59) {
        return -1;
    }
    return m * 60 + s;
}

// Exibe segundos no formato MM:SS
void formatar_duracao(int segundos) {
    int m = segundos / 60;
    int s = segundos % 60;
    printf("%02d:%02d", m, s);
}

void cadastrar() {
    if (qtd >= MAX) {
        printf("Playlist cheia!\n");
        return;
    }
    Musica m;
    printf("ID: ");
    scanf("%d", &m.id);

    for (int i = 0; i < qtd; i++) {
        if (playlist[i].id == m.id) {
            printf("ID já cadastrado!\n");
            return;
        }
    }

    printf("Título: ");
    getchar();
    fgets(m.titulo, 50, stdin);
    m.titulo[strcspn(m.titulo, "\n")] = 0;
    if (strlen(m.titulo) == 0) {
        printf("Título não pode ser vazio!\n");
        return;
    }

    printf("Artista: ");
    fgets(m.artista, 50, stdin);
    m.artista[strcspn(m.artista, "\n")] = 0;
    if (strlen(m.artista) == 0) {
        printf("Artista não pode ser vazio!\n");
        return;
    }

    printf("Duração (MM:SS): ");
    m.duracao = ler_duracao();
    if (m.duracao < 0) {
        printf("Formato de duração inválido! Use MM:SS.\n");
        return;
    }

    printf("Gênero: ");
    fgets(m.genero, 30, stdin);
    m.genero[strcspn(m.genero, "\n")] = 0;
    if (strlen(m.genero) == 0) {
        printf("Gênero não pode ser vazio!\n");
        return;
    }

    playlist[qtd++] = m;
    printf("Música cadastrada com sucesso!\n");
}

void listar() {
    if (qtd == 0) {
        printf("Nenhuma música cadastrada.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("\nID: %d\nTítulo: %s\nArtista: %s\nDuração: ",
               playlist[i].id, playlist[i].titulo, playlist[i].artista);
        formatar_duracao(playlist[i].duracao);
        printf("\nGênero: %s\n", playlist[i].genero);
    }
}

void buscar() {
    if (qtd == 0) {
        printf("Nenhuma música cadastrada.\n");
        return;
    }
    int id;
    printf("Digite o ID da música: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd; i++) {
        if (playlist[i].id == id) {
                 printf("Encontrada: %s - %s | Duração: ",
                     playlist[i].titulo, playlist[i].artista);
            formatar_duracao(playlist[i].duracao);
            printf("\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

void editar() {
    if (qtd == 0) {
        printf("Nenhuma música cadastrada.\n");
        return;
    }
    int id;
    printf("Digite o ID da música para editar: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd; i++) {
        if (playlist[i].id == id) {
            printf("Novo título: ");
            getchar();
            fgets(playlist[i].titulo, 50, stdin);
            playlist[i].titulo[strcspn(playlist[i].titulo, "\n")] = 0;

            printf("Novo artista: ");
            fgets(playlist[i].artista, 50, stdin);
            playlist[i].artista[strcspn(playlist[i].artista, "\n")] = 0;

            printf("Nova duração (MM:SS): ");
            int nova = ler_duracao();
            if (nova < 0) {
                printf("Formato inválido! Duração não alterada.\n");
            } else {
                playlist[i].duracao = nova;
            }

            printf("Novo gênero: ");
            fgets(playlist[i].genero, 30, stdin);
            playlist[i].genero[strcspn(playlist[i].genero, "\n")] = 0;

            printf("Música atualizada!\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

void excluir() {
    if (qtd == 0) {
        printf("Nenhuma música cadastrada.\n");
        return;
    }
    int id;
    printf("Digite o ID da música para excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd; i++) {
        if (playlist[i].id == id) {
            for (int j = i; j < qtd - 1; j++) {
                playlist[j] = playlist[j + 1];
            }
            qtd--;
            printf("Música excluída!\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

// Função para salvar playlist em arquivo CSV
void salvarCSV() {
    FILE *fp = fopen(ARQUIVO, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    // Escrever BOM UTF-8 para garantir que programas (ex: Excel) detectem UTF-8
    unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    fwrite(bom, 1, 3, fp);

    // Cabeçalho do CSV
    fprintf(fp, "id,titulo,artista,duracao,genero\n");

    for (int i = 0; i < qtd; i++) {
       fprintf(fp, "%d,%s,%s,%d,%s\n",
                playlist[i].id,
                playlist[i].titulo,
                playlist[i].artista,
                playlist[i].duracao,
                playlist[i].genero);
    }

    fclose(fp);
    printf("Playlist salva em \"%s\" com sucesso! (%d música(s))\n", ARQUIVO, qtd);
}

// Função para carregar playlist de arquivo CSV
void carregarCSV() {
    FILE *fp = fopen(ARQUIVO, "r");
    if (fp == NULL) {
        printf("Arquivo \"%s\" não encontrado. Nenhum dado carregado.\n", ARQUIVO);
        return;
    }

    char linha[200];

    // Pular linha do cabeçalho
    if (fgets(linha, sizeof(linha), fp) == NULL) {
        printf("Arquivo vazio ou inválido.\n");
        fclose(fp);
        return;
    }

    // Remover BOM UTF-8 do início da linha do cabeçalho, se presente
    if (strncmp(linha, "\xEF\xBB\xBF", 3) == 0) {
        memmove(linha, linha + 3, strlen(linha + 3) + 1);
    }

    int carregadas = 0;
    int ignoradas = 0;
    qtd = 0; // Reinicia o vetor antes de carregar

    while (fgets(linha, sizeof(linha), fp) != NULL && qtd < MAX) {
        Musica m;
        char titulo_tmp[50], artista_tmp[50], genero_tmp[30];

        int campos = sscanf(linha, "%d,%49[^,],%49[^,],%d,%29[^\n]",
                            &m.id, titulo_tmp, artista_tmp,
                            &m.duracao, genero_tmp);

        if (campos != 5) {
            ignoradas++;
            continue; // linha malformada, ignora
        }

        // Verifica duplicidade de ID
        int duplicado = 0;
        for (int i = 0; i < qtd; i++) {
            if (playlist[i].id == m.id) {
                duplicado = 1;
                break;
            }
        }
        if (duplicado) {
            ignoradas++;
            continue;
        }

        strncpy(m.titulo,  titulo_tmp,  49); m.titulo[49]  = 0;
        strncpy(m.artista, artista_tmp, 49); m.artista[49] = 0;
        strncpy(m.genero,  genero_tmp,  29); m.genero[29]  = 0;

        playlist[qtd++] = m;
        carregadas++;
    }

    fclose(fp);
    printf("Carregamento concluído: %d música(s) importada(s)", carregadas);
    if (ignoradas > 0)
        printf(", %d linha(s) ignorada(s) (duplicadas ou inválidas)", ignoradas);
    printf(".\n");
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    printf("Verificando arquivo salvo...\n");
    carregarCSV();

    int opcao;
    do {
        printf("\n--- NKC PLAYLIST ---\n\n");
        printf("Sua música, sua vibe, sua sintonia!\n\n");
        printf("O que você quer fazer hoje?\n\n");
        printf("1. Cadastrar Música\n");
        printf("2. Listar Música\n");
        printf("3. Buscar Música\n");
        printf("4. Editar Música\n");
        printf("5. Excluir Música\n");
        printf("6. Salvar em CSV\n");
        printf("7. Carregar de CSV\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar();   break;
            case 2: listar();      break;
            case 3: buscar();      break;
            case 4: editar();      break;
            case 5: excluir();     break;
            case 6: salvarCSV();   break;
            case 7: carregarCSV(); break;
            case 0: printf("Encerrando a NKC PLAYLIST.\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}