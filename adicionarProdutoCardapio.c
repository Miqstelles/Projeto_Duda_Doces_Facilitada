#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void adicionarProdutoCardapio()
{
    cardapio *cardap;
    ingredientes ing1;

    FILE *pFile;
    FILE *pFile1;
    int n = 1, i, codigo = 1;

    cardap = (cardapio *)calloc(n, sizeof(cardapio));
    pFile = fopen("cardapio.txt", "a");
    pFile1 = fopen("estoque_ingredientes.txt", "r");

    for (i = 0; i < n; i++)
    {
        cardap[i].qtdIngredientes = 0;

        cardap[i].codigo = obterProximoCodigoCardapio();

        printf("Insira o tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
        scanf("%i", &cardap[i].tipo);

        fflush(stdin);
        printf("Insira o nome do produto: ");
        scanf("%[^\n]s", cardap[i].nome);

        listarIngrediente();
        while (1)
        {
            int codigoIngrediente;

            printf("Insira o código do ingrediente a ser adicionado (0 para finalizar): ");
            scanf("%i", &codigoIngrediente);

            if (codigoIngrediente == 0) break;

            int ingredienteExiste = 0;

            rewind(pFile1);
            while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
            {
                if (ing1.codigo == codigoIngrediente)
                {
                    ingredienteExiste = 1;
                    cardap[i].listaIngredientes[cardap[i].qtdIngredientes] = codigoIngrediente;
                    cardap[i].qtdIngredientes++;
                    printf("Ingrediente adicionado ao produto.\n");
                    break;
                }
            }

            if (!ingredienteExiste) printf("Código de ingrediente inexistente. Tente novamente.\n");
        }

        printf("Insira o valor do produto: ");
        scanf("%f", &cardap[i].preco);

        fwrite(&cardap[i], sizeof(cardapio), 1, pFile);
    }

    free(cardap);
    fclose(pFile);
    fclose(pFile1);
}
