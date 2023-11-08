#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void listarIngrediente()
{
    ingredientes ing1;
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");

    printf("\n=========================================================");
    printf("\nEstoque\n");
    printf("\nCódigo \t Nome \t\t   Quantidade");

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade);
    }

    printf("\n=========================================================\n");
    fclose(pFile);
}
