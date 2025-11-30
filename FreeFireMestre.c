#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPONENTES 10

// --- Estrutura do Componente ---
typedef struct {
    int id;
    char nome[30];
    int prioridade; // 1 (Máxima) a 100 (Mínima)
} Componente;

typedef struct {
    Componente lista[MAX_COMPONENTES];
    int qtd;
} Torre;

// Variável global para métrica de desempenho
long long comparacoes = 0;

// --- Protótipos ---
void carregarComponentes(Torre *t);
void listarComponentes(Torre *t);
void bubbleSortPorNome(Torre *t);
void quickSortPorPrioridade(Componente *vetor, int esquerda, int direita);
int buscaBinariaPrioridade(Torre *t, int prioridadeAlvo);

// --- Função Principal ---
int main() {
    Torre minhaTorre;
    carregarComponentes(&minhaTorre);
    int opcao, alvo, indice;

    do {
        printf("\n=== SISTEMA DE MONTAGEM DA TORRE ===\n");
        printf("1. Listar Componentes (Estado Atual)\n");
        printf("2. Ordenar por NOME (Bubble Sort - Lento)\n");
        printf("3. Ordenar por PRIORIDADE (Quick Sort - Rapido)\n");
        printf("4. Buscar Componente por Prioridade (Busca Binaria)\n");
        printf("5. Resetar Lista (Baguncar)\n");
        printf("0. Finalizar Missao\n");
        printf("Escolha a estrategia: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                listarComponentes(&minhaTorre);
                break;
            case 2:
                comparacoes = 0; // Reseta contador
                bubbleSortPorNome(&minhaTorre);
                printf("\n[Analise] Bubble Sort finalizado com %lld comparacoes.\n", comparacoes);
                listarComponentes(&minhaTorre);
                break;
            case 3:
                comparacoes = 0; // Reseta contador
                quickSortPorPrioridade(minhaTorre.lista, 0, minhaTorre.qtd - 1);
                printf("\n[Analise] Quick Sort finalizado com %lld comparacoes.\n", comparacoes);
                listarComponentes(&minhaTorre);
                break;
            case 4:
                // Busca Binária só funciona se estiver ordenado!
                printf("Digite a Prioridade do componente (ex: 1 para Antena Mestra): ");
                scanf("%d", &alvo);
                indice = buscaBinariaPrioridade(&minhaTorre, alvo);

                if (indice != -1) {
                    printf("\n[SUCESSO] Componente '%s' encontrado e ativado!\n", minhaTorre.lista[indice].nome);
                } else {
                    printf("\n[FALHA] Componente nao encontrado ou lista nao ordenada por prioridade.\n");
                }
                break;
            case 5:
                carregarComponentes(&minhaTorre);
                printf("\n[Sistema] Componentes desorganizados novamente.\n");
                break;
            case 0:
                printf("Decolagem autorizada. Ate a proxima!\n");
                break;
            default:
                printf("Comando invalido!\n");
        }
    } while(opcao != 0);

    return 0;
}

// --- Implementações ---

void carregarComponentes(Torre *t) {
    t->qtd = 0;
    // Simulando itens desordenados coletados na ilha
    Componente itens[] = {
        {101, "Cabo de Aco", 50},
        {102, "Gerador Diesel", 20},
        {103, "Antena Mestra", 1},
        {104, "Parafusos", 90},
        {105, "Transmissor", 5},
        {106, "Painel Solar", 25},
        {107, "Bateria Litio", 10},
        {108, "Refrigerador", 80},
        {109, "Chip IA", 2},
        {110, "Estrutura Base", 15}
    };

    for(int i=0; i<MAX_COMPONENTES; i++) {
        t->lista[i] = itens[i];
    }
    t->qtd = MAX_COMPONENTES;
}

void listarComponentes(Torre *t) {
    printf("\n%-20s | %s\n", "Nome", "Prioridade");
    printf("-------------------------------\n");
    for(int i=0; i<t->qtd; i++) {
        printf("%-20s | %d\n", t->lista[i].nome, t->lista[i].prioridade);
    }
}

// ALGORITMO 1: Bubble Sort (Ordena por NOME)
// Complexidade: O(n^2)
void bubbleSortPorNome(Torre *t) {
    int i, j;
    Componente temp;
    for (i = 0; i < t->qtd - 1; i++) {
        for (j = 0; j < t->qtd - i - 1; j++) {
            comparacoes++; // Contabiliza a comparação
            if (strcmp(t->lista[j].nome, t->lista[j+1].nome) > 0) {
                // Troca
                temp = t->lista[j];
                t->lista[j] = t->lista[j+1];
                t->lista[j+1] = temp;
            }
        }
    }
}

// ALGORITMO 2: Quick Sort (Ordena por PRIORIDADE)
// Complexidade: O(n log n)
void quickSortPorPrioridade(Componente *vetor, int esquerda, int direita) {
    int i, j, pivo;
    Componente temp;

    i = esquerda;
    j = direita;
    pivo = vetor[(esquerda + direita) / 2].prioridade;

    while(i <= j) {
        // Encontra elemento à esquerda que deveria estar à direita
        while(vetor[i].prioridade < pivo && i < direita) {
            i++;
            comparacoes++;
        }
        // Encontra elemento à direita que deveria estar à esquerda
        while(vetor[j].prioridade > pivo && j > esquerda) {
            j--;
            comparacoes++;
        }

        if(i <= j) {
            // Troca
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }
    }

    // Recursão
    if(j > esquerda)
        quickSortPorPrioridade(vetor, esquerda, j);
    if(i < direita)
        quickSortPorPrioridade(vetor, i, direita);
}

// ALGORITMO 3: Busca Binária
// Complexidade: O(log n) - Requer vetor ordenado
int buscaBinariaPrioridade(Torre *t, int prioridadeAlvo) {
    int inicio = 0;
    int fim = t->qtd - 1;
    int meio;
    int comparacoesBusca = 0;

    printf("\n[Busca] Rastreando componente de prioridade %d...\n", prioridadeAlvo);

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        comparacoesBusca++;

        if (t->lista[meio].prioridade == prioridadeAlvo) {
            printf("[Busca] Alvo localizado com apenas %d tentativas!\n", comparacoesBusca);
            return meio;
        }

        // Se a prioridade do meio é menor (numericamente) que o alvo
        // mas lembre-se: ordenamos crescente (1, 2, 5, 10...)
        if (t->lista[meio].prioridade < prioridadeAlvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}
