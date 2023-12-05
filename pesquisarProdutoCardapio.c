#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void pesquisarProdutoCardapio(){
    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo.

    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo de cardápio para leitura.

    int codigo, encontrou = 0;
    codigo = verificacaoCodigo("Insira o código do produto: ", RED "ERRO INSIRA UM CÓDIGO VÁLIDO" RESET);

    char tipoProduto[3][80] = {"Bolo", "Doce", "Sobremesa"};

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            printf(GREEN "\nCódigo: " RESET "%i\n", cardap.codigo); // Exibe o código do produto.
            printf(RED "Nome: " RESET "%s\n", cardap.nome); // Exibe o nome do produto.
            printf(YELLOW "Tipo: " RESET "%s\n", tipoProduto[cardap.tipo - 1]); // Exibe o tipo do produto com base no valor numérico.
            printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes); // Exibe a quantidade de ingredientes no produto.

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
