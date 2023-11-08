#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void listarCardapio()
{
    cardapio cardap;
    FILE *pFile = fopen("cardapio.txt", "r");

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
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
    }

    fclose(pFile);
}
