
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOGADORES 30
#define ARQUIVO_DADOS "dados.txt" // Nome do arquivo para carregar/salvar dados

typedef struct {
    char nome[50];
    int golsMarcados;
    int assistencias;
} Jogador;

typedef struct {
    Jogador jogadores[MAX_JOGADORES];
    int numJogadores;
} Sistema;

// Função para carregar dados do arquivo
void carregarSistema(Sistema *sistema) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "rb");

    if (arquivo != NULL) {
        fread(sistema, sizeof(Sistema), 1, arquivo);
        fclose(arquivo);
    }
}

// Função para salvar dados no arquivo
void salvarSistema(Sistema *sistema) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "wb");

    if (arquivo != NULL) {
        fwrite(sistema, sizeof(Sistema), 1, arquivo);
        fclose(arquivo);
    }
}

// Função para adicionar um novo jogador
void adicionarJogador(Sistema *sistema) {
    if (sistema->numJogadores < MAX_JOGADORES) {
        printf("Digite o nome do jogador: ");
        scanf("%s", sistema->jogadores[sistema->numJogadores].nome);
        sistema->jogadores[sistema->numJogadores].golsMarcados = 0;
        sistema->jogadores[sistema->numJogadores].assistencias = 0;
        sistema->numJogadores++;
        printf("Jogador adicionado com sucesso!\n");
    } else {
        printf("Limite máximo de jogadores atingido!\n");
    }
}

// Função para listar jogadores com opções de visualização
void listarJogadores(Sistema *sistema, int opcaoListagem) {
    printf("\nListagem de Jogadores:\n");

    int inicio, fim;
    switch (opcaoListagem) {
        case 1: // Os 5 primeiros registros
            inicio = 0;
            fim = (sistema->numJogadores < 5) ? sistema->numJogadores : 5;
            break;
        case 2: // Os 5 últimos registros
            inicio = (sistema->numJogadores > 5) ? sistema->numJogadores - 5 : 0;
            fim = sistema->numJogadores;
            break;
        case 3: // Todos os registros
            inicio = 0;
            fim = sistema->numJogadores;
            break;
        default:
            printf("Opção inválida de listagem.\n");
            return;
    }

    for (int i = inicio; i < fim; i++) {
        printf("%d. %s\n", i + 1, sistema->jogadores[i].nome);
    }
}

// Função para buscar e exibir informações de um jogador
void buscarEExibirJogador(Sistema *sistema) {
    char nomeBusca[50];
    printf("Digite o nome do jogador a ser buscado: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < sistema->numJogadores; i++) {
        if (strcmp(nomeBusca, sistema->jogadores[i].nome) == 0) {
            printf("Estatísticas de %s:\n", sistema->jogadores[i].nome);
            printf("Gols Marcados: %d\n", sistema->jogadores[i].golsMarcados);
            printf("Assistências: %d\n", sistema->jogadores[i].assistencias);
            return;
        }
    }

    printf("Jogador não encontrado.\n");
}

// Função para atualizar informações de um jogador
void atualizarJogador(Sistema *sistema) {
    char nomeAtualizar[50];
    printf("Digite o nome do jogador a ser atualizado: ");
    scanf("%s", nomeAtualizar);

    for (int i = 0; i < sistema->numJogadores; i++) {
        if (strcmp(nomeAtualizar, sistema->jogadores[i].nome) == 0) {
            printf("Digite o novo número de gols marcados: ");
            scanf("%d", &sistema->jogadores[i].golsMarcados);
            printf("Digite o novo número de assistências: ");
            scanf("%d", &sistema->jogadores[i].assistencias);
            printf("Estatísticas de %s atualizadas com sucesso!\n", sistema->jogadores[i].nome);
            return;
        }
    }

    printf("Jogador não encontrado.\n");
}

// Função para remover um jogador
void removerJogador(Sistema *sistema) {
    char nomeRemover[50];
    printf("Digite o nome do jogador a ser removido: ");
    scanf("%s", nomeRemover);

    for (int i = 0; i < sistema->numJogadores; i++) {
        if (strcmp(nomeRemover, sistema->jogadores[i].nome) == 0) {
            // Desloca os elementos à frente do índice para trás para remover o jogador


            for (int j = i; j < sistema->numJogadores - 1; j++) {
                sistema->jogadores[j] = sistema->jogadores[j + 1];
            }
            sistema->numJogadores--;
            printf("Jogador removido com sucesso!\n");
            return;
        }
    }

    printf("Jogador não encontrado.\n");
}

int main() {
    Sistema sistema;
    carregarSistema(&sistema);

    while (1) {
        // Exibir menu de opções
        printf("\nOpções:\n");
        printf("1. Adicionar Jogador\n");
        printf("2. Listar Jogadores (5 primeiros)\n");
        printf("3. Listar Jogadores (5 últimos)\n");
        printf("4. Listar Todos os Jogadores\n");
        printf("5. Buscar e Exibir Jogador\n");
        printf("6. Atualizar Jogador\n");
        printf("7. Remover Jogador\n");
        printf("0. Sair\n");

        int escolha;
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                adicionarJogador(&sistema);
                salvarSistema(&sistema);
                break;
            case 2:
                listarJogadores(&sistema, 1);
                break;
            case 3:
                listarJogadores(&sistema, 2);
                break;
            case 4:
                listarJogadores(&sistema, 3);
                break;
            case 5:
                buscarEExibirJogador(&sistema);
                break;
            case 6:
                atualizarJogador(&sistema);
                salvarSistema(&sistema);
                break;
            case 7:
                removerJogador(&sistema);
                salvarSistema(&sistema);
                break;
            case 0:
                printf("Saindo do programa. Até mais!\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
