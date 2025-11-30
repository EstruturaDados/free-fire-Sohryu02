#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição do Item (Payload)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Definição do NÓ da Lista
typedef struct Node {
    Item dado;
    struct Node *proximo; // Ponteiro para o próximo item
} Node;

// Função para criar um novo nó
Node* criarNode() {
    Node* novo = (Node*)malloc(sizeof(Node));
    if(novo) {
        printf("Nome: "); scanf(" %[^\n]", novo->dado.nome);
        printf("Tipo: "); scanf(" %[^\n]", novo->dado.tipo);
        printf("Qtd: "); scanf("%d", &novo->dado.quantidade);
        novo->proximo = NULL;
    }
    return novo;
}

// 1. ADICIONAR (No início - O(1) - Muito rápido!)
void adicionarLista(Node **cabeca) {
    Node *novo = criarNode();
    if(novo) {
        novo->proximo = *cabeca; // O novo aponta para o antigo primeiro
        *cabeca = novo;          // O novo se torna o primeiro
        printf("[+] Item adicionado (Topo da pilha)!\n");
    }
}

// 2. LISTAR
void listarLista(Node *cabeca) {
    printf("\n--- Mochila Encadeada ---\n");
    Node *atual = cabeca;
    while(atual != NULL) {
        printf("-> [%s] (%s) - x%d\n", atual->dado.nome, atual->dado.tipo, atual->dado.quantidade);
        atual = atual->proximo;
    }
}

// 3. REMOVER (Sem deslocamento de memória)
void removerLista(Node **cabeca, char *nomeAlvo) {
    Node *atual = *cabeca;
    Node *anterior = NULL;

    while (atual != NULL && strcmp(atual->dado.nome, nomeAlvo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("[!] Item nao encontrado.\n");
        return;
    }

    // Se for o primeiro da lista
    if (anterior == NULL) {
        *cabeca = atual->proximo;
    } else {
        anterior->proximo = atual->proximo; // "Pula" o item removido
    } // [Imagem do ponteiro anterior ligando ao próximo do atual]

    free(atual); // Libera a memória RAM
    printf("[-] Item removido da memoria.\n");
}

int main() {
    Node *mochila = NULL; // Lista começa vazia
    // Exemplo de uso:
    adicionarLista(&mochila);
    adicionarLista(&mochila);
    listarLista(mochila);
    char busca[30];
    printf("Remover qual? ");
    scanf(" %[^\n]", busca);
    removerLista(&mochila, busca);
    listarLista(mochila);
    return 0;
}
