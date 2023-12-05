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
    int escolha;

    system("cls");
    while (fread(&cardap, sizeof(cardapio), 1, pFile)) // L� um registro de cardapio do arquivo.
    {
        printf(GREEN "\nC�digo: " RESET "%i\n", cardap.codigo); // Exibe o c�digo do produto.
        printf(RED "Nome: " RESET "%s\n", cardap.nome); // Exibe o nome do produto.
        printf(YELLOW "Tipo: " RESET "%s\n", tipoProduto[cardap.tipo - 1]); // Exibe o tipo do produto com base no valor num�rico.
        printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes); // Exibe a quantidade de ingredientes no produto.

        printf(YELLOW "Ingredientes:\n" RESET);

        for (int i = 0; i < cardap.qtdIngredientes; i++)
        {
            int codigoIngrediente = cardap.listaIngredientes[i];

            // Obt�m o nome do ingrediente com base no c�digo.
            char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);

            // Verifica se o ingrediente n�o est� desativado antes de imprimir suas informa��es
            if (strstr(nomeIngrediente, "(DESATIVADO)") == NULL)
            {
                printf(GREEN "  ID:" RESET " %i " GREEN "Nome: " RESET "%s\n", codigoIngrediente, nomeIngrediente); // Exibe o c�digo e nome do ingrediente.
            }
        }

        printf("\nPre�o: " GREEN "R$ %.2f\n" RESET, cardap.preco); // Exibe o pre�o do produto com duas casas decimais.

        printf("\n0 - Sair: ");
        scanf("%d", &escolha);
    }
    while(escolha !=0);
    system("cls");
}
