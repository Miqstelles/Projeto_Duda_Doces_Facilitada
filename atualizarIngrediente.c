#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void atualizarIngrediente()
{
    listarIngrediente();

    ingredientes ing1;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("estoque_ingredientes.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do ingrediente a ser atualizado: ");
    scanf("%i", &codigo);

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            encontrou = 1;
            fflush(stdin);
            printf("Insira o novo nome do ingrediente: ");
            scanf("%[^\n]s", ing1.nome);

            printf("Insira a nova quantidade em estoque: ");
            scanf("%i", &ing1.quantidade);

            printf("\nIngrediente %s atualizado com sucesso!\n", ing1.nome);
        }
        fwrite(&ing1, sizeof(ingredientes), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("estoque_ingredientes.txt", "w");

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
        {
            fwrite(&ing1, sizeof(ingredientes), 1, pFile);
        }

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Ingrediente não encontrado!\n");
}
