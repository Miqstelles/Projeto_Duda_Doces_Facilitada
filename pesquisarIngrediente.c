#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void pesquisarIngrediente()
{
    ingredientes ing1; // Declara a estrutura chamada ingredientes.
    FILE *pFile; // Declara um ponteiro de arquivo.

    pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo de estoque de ingredientes para leitura.

    int codigo, encontrou = 0;
    printf("Insira o código do ingrediente: ");
    scanf("%i", &codigo); // Solicita o código do ingrediente a ser pesquisado.

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            printf("\n=========================================================");
            printf("\nEstoque\n");
            printf("\nCódigo \t Nome \t\t   Quantidade");
            printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade); // Exibe os detalhes do ingrediente encontrado.
            printf("\n=========================================================\n");
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Ingrediente não encontrado!\n"); // Exibe uma mensagem se o ingrediente não for encontrado.

    fclose(pFile); // Fecha o arquivo de estoque de ingredientes.
}

