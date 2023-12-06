#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void listarCardapio()
{
    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    char tipoProduto[3][80] = {"Bolo", "Doce", "Sobremesa"};

    system("cls");
    while (fread(&cardap, sizeof(cardapio), 1, pFile)) // Lê um registro de cardapio do arquivo.
    {
        printf(GREEN "\nCódigo: " RESET "%i\n", cardap.codigo); // Exibe o código do produto.
        printf(RED "Nome: " RESET "%s\n", cardap.nome); // Exibe o nome do produto.
        printf(YELLOW "Tipo: " RESET "%s\n", tipoProduto[cardap.tipo - 1]); // Exibe o tipo do produto com base no valor numérico.
        printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes); // Exibe a quantidade de ingredientes no produto.

        printf(YELLOW "Ingredientes:\n" RESET);

        for (int i = 0; i < cardap.qtdIngredientes; i++)
        {
            int codigoIngrediente = cardap.listaIngredientes[i];

            // Obtém o nome do ingrediente com base no código.
            char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);

            // Verifica se o ingrediente não está desativado antes de imprimir suas informações
            if (strstr(nomeIngrediente, "(DESATIVADO)") == NULL)
            {
                printf(GREEN "  ID:" RESET " %i " GREEN "Nome: " RESET "%s\n", codigoIngrediente, nomeIngrediente); // Exibe o código e nome do ingrediente.
            }
        }

        printf("\nPreço: " GREEN "R$ %.2f\n" RESET, cardap.preco); // Exibe o preço do produto com duas casas decimais.

        printf("------------------------------------------\n------------------------------------------");
        printf("\n\n"); // Exibe linhas de separação entre os produtos.
    }

    fclose(pFile); // Fecha o arquivo após a leitura.
}
