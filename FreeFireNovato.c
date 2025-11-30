#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOCHILA 5 // Capacidade máxima da mochila (slots)

// --- Definição das Estruturas ---

typedef struct {
    char nome[30];
    char tipo[20]; // Ex: Arma, Municao, Cura
    int quantidade;
} Item;

typedef struct {
    Item itens[MAX_MOCHILA]; // O vetor que armazena os itens
    int qtdAtual;            // Controla quantos itens estão ocupados
} Mochila;

// --- Protótipos das Funções ---
void inicializarMochila(Mochila *m);
int adicionarItem(Mochila *m);
void listarItens(Mochila *m);
void buscarItem(Mochila *m);
void removerItem(Mochila *m);
void limparBuffer();

// --- Função Principal ---
int main() {
    Mochila minhaMochila;
    inicializarMochila(&minhaMochila);
    int opcao;

    do {
        printf("\n=== MOCHILA DE LOOT [%d/%d] ===\n", minhaMochila.qtdAtual, MAX_MOCHILA);
        printf("1. Coletar Item (Adicionar)\n");
        printf("2. Verificar Mochila (Listar)\n");
        printf("3. Procurar Item (Buscar)\n");
        printf("4. Descartar Item (Remover)\n");
        printf("0. Sair\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o "enter" pendente

        switch (opcao) {
            case 1:
                adicionarItem(&minhaMochila);
                break;
            case 2:
                listarItens(&minhaMochila);
                break;
            case 3:
                buscarItem(&minhaMochila);
                break;
            case 4:
                removerItem(&minhaMochila);
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Acao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

void inicializarMochila(Mochila *m) {
    m->qtdAtual = 0;
}

// 1. ADICIONAR (Inserção no fim da lista)
int adicionarItem(Mochila *m) {
    if (m->qtdAtual >= MAX_MOCHILA) {
        printf("\n[!] Mochila cheia! Voce precisa descartar algo antes.\n");
        return 0;
    }

    Item novoItem;

    printf("\n--- Novo Loot ---\n");
    printf("Nome do item: ");
    scanf("%[^\n]", novoItem.nome);
    limparBuffer();

    printf("Tipo (Arma/Cura/Municao): ");
    scanf("%[^\n]", novoItem.tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();

    // Insere na posição livre (indicada por qtdAtual)
    m->itens[m->qtdAtual] = novoItem;
    m->qtdAtual++;

    printf("[+] Item '%s' adicionado a mochila!\n", novoItem.nome);
    return 1;
}

// 2. LISTAR (Percorrer o vetor)
void listarItens(Mochila *m) {
    if (m->qtdAtual == 0) {
        printf("\n[Vazio] A mochila esta vazia.\n");
        return;
    }

    printf("\n--- Conteudo da Mochila ---\n");
    printf("%-4s | %-20s | %-15s | %s\n", "ID", "Nome", "Tipo", "Qtd");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < m->qtdAtual; i++) {
        printf("%-4d | %-20s | %-15s | %d\n",
            i,
            m->itens[i].nome,
            m->itens[i].tipo,
            m->itens[i].quantidade
        );
    }
}

// 3. BUSCAR (Busca Sequencial por Nome)
void buscarItem(Mochila *m) {
    char termo[30];
    printf("Nome do item para buscar: ");
    scanf("%[^\n]", termo);
    limparBuffer();

    for (int i = 0; i < m->qtdAtual; i++) {
        // strcasecmp ou stricmp não são padrão ANSI C, usando strcmp
        // Para ignorar maiúsculas/minúsculas precisaria de lógica extra
        if (strcmp(m->itens[i].nome, termo) == 0) {
            printf("\n[Encontrado] Slot %d: %s (Qtd: %d)\n", i, m->itens[i].nome, m->itens[i].quantidade);
            return;
        }
    }
    printf("\n[!] Item nao encontrado.\n");
}

// 4. REMOVER (Remoção com deslocamento)
void removerItem(Mochila *m) {
    char nomeAlvo[30];
    int indice = -1;

    listarItens(m); // Mostra lista para ajudar o jogador
    if (m->qtdAtual == 0) return;

    printf("\nDigite o NOME do item para descartar: ");
    scanf("%[^\n]", nomeAlvo);
    limparBuffer();

    // Primeiro, encontramos o índice do item
    for (int i = 0; i < m->qtdAtual; i++) {
        if (strcmp(m->itens[i].nome, nomeAlvo) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("[!] Item nao existe na mochila.\n");
        return;
    }

    // Lógica de "Shift Left": Deslocar os itens da frente para trás
    // para cobrir o buraco deixado pelo item removido.
    for (int i = indice; i < m->qtdAtual - 1; i++) {
        m->itens[i] = m->itens[i + 1];
    }

    m->qtdAtual--; // Decrementa o tamanho lógico da lista
    printf("[-] Item '%s' descartado com sucesso.\n", nomeAlvo);
}

// Utilitário para limpar o buffer do teclado (evita erros no scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
