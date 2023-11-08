#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void adicionarIngrediente()
{
    FILE *pFile;
    ingredientes *ing;

    ing = (ingredientes *)calloc(1, sizeof(ingredientes));
    pFile = fopen("estoque_ingredientes.txt", "a");

    ing[0].codigo = obterProximoCodigo();

    fflush(stdin);
    printf("Insira o nome do ingrediente: ");
    scanf("%[^\n]s", ing[0].nome);

    printf("Insira a quantidade em estoque: ");
    scanf("%i", &ing[0].quantidade);

    fwrite(&ing[0], sizeof(ingredientes), 1, pFile);

    fclose(pFile);
}
