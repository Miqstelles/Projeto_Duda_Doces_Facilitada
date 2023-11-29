#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void listarCardapio()
{
    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    int escolha;
    do
    {
        system("cls");
        while (fread(&cardap, sizeof(cardapio), 1, pFile)) // L� um registro de cardapio do arquivo.
        {
            printf("\nC�digo: %i\n", cardap.codigo); // Exibe o c�digo do produto.
            printf("Nome: %s\n", cardap.nome); // Exibe o nome do produto.
            printf("Tipo: %s\n", cardap.tipo == 1 ? "Bolo" : cardap.tipo == 2 ? "Doce" : "Sobremesa"); // Exibe o tipo do produto com base no valor num�rico.
            printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes); // Exibe a quantidade de ingredientes no produto.

            printf("Ingredientes:\n");

            for (int i = 0; i < cardap.qtdIngredientes; i++)
            {
                int codigoIngrediente = cardap.listaIngredientes[i];
                char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente); // Obt�m o nome do ingrediente com base no c�digo.
                printf("  Nome: (%i)%s\n", cardap.listaIngredientes[i], nomeIngrediente); // Exibe o c�digo e nome do ingrediente.
            }

            printf("\nPre�o: %.2f\n", cardap.preco); // Exibe o pre�o do produto com duas casas decimais.

            printf("------------------------------------------\n------------------------------------------");
            printf("\n\n"); // Exibe linhas de separa��o entre os produtos.
        }

        fclose(pFile); // Fecha o arquivo ap�s a leitura.

        printf("\n0 - Sair: ");
        scanf("%d", &escolha);
    }
    while(escolha !=0);
    system("cls");
}
