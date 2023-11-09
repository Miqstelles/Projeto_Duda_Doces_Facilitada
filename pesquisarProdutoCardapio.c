#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void pesquisarProdutoCardapio(){
    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo.

    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo de cardápio para leitura.

    int codigo, encontrou = 0;
    printf("Insira o código do produto: ");
    scanf("%i", &codigo); // Solicita o código do produto a ser pesquisado.

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            printf("\nCódigo: %i\n", cardap.codigo);
            printf("Nome: %s\n", cardap.nome);
            printf("Tipo: %s\n", cardap.tipo == 1 ? "Bolo" : cardap.tipo == 2 ? "Doce" : "Sobremesa");
            printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes);

            printf("Ingredientes:\n");

            for (int i = 0; i < cardap.qtdIngredientes; i++)
            {
                int codigoIngrediente = cardap.listaIngredientes[i];
                char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
                printf("  Nome: (%i)%s\n", cardap.listaIngredientes[i], nomeIngrediente);
            }

            printf("\nPreço: %.2f\n", cardap.preco);

            printf("------------------------------------------\n------------------------------------------");
            printf("\n\n");
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Produto não encontrado!\n"); // Exibe uma mensagem se o produto não for encontrado.

    fclose(pFile); // Fecha o arquivo de cardápio.
}
