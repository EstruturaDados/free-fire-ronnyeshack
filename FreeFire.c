#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// ===============================================
// Struct Item
// Representa um item coletado na ilha
// ===============================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// ===============================================
// Enum para definir critérios de ordenação
// ===============================================
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila e variáveis de controle
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;  // Necessário para busca binária
int comparacoes = 0;

// ===============================================
// Função utilitária para limpar a tela
// ===============================================
void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

// ===============================================
// Função para exibir o menu principal
// ===============================================
int exibirMenu() {
    printf("======= MOCHILA DA ILHA – FREE FIRE EDITION =======\n");
    printf("Itens na mochila: %d\n", numItens);
    printf("Ordenada por nome? %s\n\n", ordenadaPorNome ? "SIM" : "NÃO");

    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens\n");
    printf("5. Buscar item por nome (Busca Binária)\n");
    printf("0. Sair\n");

    printf("\nEscolha uma opção: ");
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

// ===============================================
// Inserir um item na mochila
// ===============================================
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\nDigite o nome do item: ");
    scanf("%s", novo.nome);

    printf("Digite o tipo do item: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens] = novo;
    numItens++;

    ordenadaPorNome = false;

    printf("\nItem adicionado com sucesso!\n");
}

// ===============================================
// Remover item pelo nome
// ===============================================
void removerItem() {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para remover: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            // Desloca itens para esquerda
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            numItens--;
            ordenadaPorNome = false;

            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}

// ===============================================
// Listar todos os itens da mochila
// ===============================================
void listarItens() {
    if (numItens == 0) {
        printf("\nNenhum item na mochila.\n");
        return;
    }

    printf("\n=========== LISTA DE ITENS ===========\n");

    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }

    printf("======================================\n");
}

// ===============================================
// Função de ordenação (Insertion Sort)
// ===============================================
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;

            bool condicao = false;

            if (criterio == ORDENAR_NOME)
                condicao = strcmp(chave.nome, mochila[j].nome) < 0;

            else if (criterio == ORDENAR_TIPO)
                condicao = strcmp(chave.tipo, mochila[j].tipo) < 0;

            else if (criterio == ORDENAR_PRIORIDADE)
                condicao = chave.prioridade > mochila[j].prioridade;

            if (!condicao)
                break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }
}

// ===============================================
// Menu de ordenação
// ===============================================
void menuOrdenacao() {
    printf("\nEscolha o critério de ordenação:\n");
    printf("1. Nome\n");
    printf("2. Tipo\n");
    printf("3. Prioridade (maior para menor)\n");
    printf("Opção: ");

    int c;
    scanf("%d", &c);

    insertionSort(c);

    if (c == ORDENAR_NOME)
        ordenadaPorNome = true;
    else
        ordenadaPorNome = false;

    printf("\nItens ordenados!\n");
    printf("Comparações feitas: %d\n", comparacoes);
}

// ===============================================
// Busca binária por nome
// ===============================================
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("\nA mochila precisa estar ordenada por NOME para busca binária!\n");
        return;
    }

    char alvo[30];
    printf("\nNome do item para buscar: ");
    scanf("%s", alvo);

    int ini = 0, fim = numItens - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;

        int cmp = strcmp(alvo, mochila[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                   mochila[meio].nome,
                   mochila[meio].tipo,
                   mochila[meio].quantidade,
                   mochila[meio].prioridade);
            return;
        }
        else if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }

    printf("\nItem não encontrado!\n");
}

// ===============================================
// Função principal
// ===============================================
int main() {
    int opcao;

    do {
        opcao = exibirMenu();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n");
        }

        printf("\n");

    } while (opcao != 0);

    return 0;
}
