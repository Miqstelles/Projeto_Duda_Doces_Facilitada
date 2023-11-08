#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void pesquisarIngrediente()
{
    ingredientes ing1;
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");

    int codigo, encontrou = 0;
    printf("Insira o codigo do ingrediente: ");
    scanf("%i", &codigo);

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            printf("\n=========================================================");
            printf("\nEstoque\n");
            printf("\nCódigo \t Nome \t\t   Quantidade");
            printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade);
            printf("\n=========================================================\n");
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Ingrediente não encontrado!\n");

    fclose(pFile);
}
