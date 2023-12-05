#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void listarCardapioPedido()
{
    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    char tipoProduto[3][80] = {"Bolo", "Doce", "Sobremesa"};

    while (fread(&cardap, sizeof(cardapio), 1, pFile)) // Lê um registro de cardapio do arquivo.
    {
        printf(GREEN "\nCódigo: " RESET "%i\n", cardap.codigo); // Exibe o código do produto.
        printf(RED "Nome: " RESET "%s\n", cardap.nome); // Exibe o nome do produto.
        printf(YELLOW "Tipo: " RESET "%s\n", tipoProduto[cardap.tipo - 1]); // Exibe o tipo do produto com base no valor numérico.
        printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes); // Exibe a quantidade de ingredientes no produto.

        printf("Ingredientes:\n");

        for (int i = 0; i < cardap.qtdIngredientes; i++)
        {
            int codigoIngrediente = cardap.listaIngredientes[i];
            char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente); // Obtém o nome do ingrediente com base no código.
            printf("  Nome: (%i)%s\n", cardap.listaIngredientes[i], nomeIngrediente); // Exibe o código e nome do ingrediente.
        }

        printf("\nPreço: %.2f\n", cardap.preco); // Exibe o preço do produto com duas casas decimais.

        printf("------------------------------------------\n------------------------------------------");
        printf("\n\n"); // Exibe linhas de separação entre os produtos.
    }

    fclose(pFile); // Fecha o arquivo após a leitura.

}

