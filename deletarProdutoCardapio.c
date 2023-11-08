#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void deletarProdutoCardapio()
{
    listarCardapio();

    cardapio cardap;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("cardapio.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do produto a ser deletado: ");
    scanf("%i", &codigo);

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            encontrou = 1;
            printf("Produto: %s deletado com sucesso!\n", cardap.nome);
        }
        else fwrite(&cardap, sizeof(cardapio), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("cardapio.txt", "w");

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) fwrite(&cardap, sizeof(cardapio), 1, pFile);

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Produto não encontrado!\n");
}
