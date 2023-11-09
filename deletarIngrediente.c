#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void deletarIngrediente()
{
    listarIngrediente(); // Chama a fun��o listarIngrediente para mostrar os ingredientes dispon�veis.

    ingredientes ing1; // Declara a estrutura chamada ingredientes.
    FILE *pFile; // Declara um ponteiro de arquivo para "estoque_ingredientes.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "temp.txt".
    pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.
    pFile1 = fopen("temp.txt", "w"); // Abre o arquivo "temp.txt" para escrita.

    int codigo, encontrou = 0;
    printf("Insira o c�digo do ingrediente a ser deletado: ");
    scanf("%i", &codigo); // L� o c�digo do ingrediente a ser deletado.

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo) encontrou = 1; // Define a flag para indicar que o ingrediente foi encontrado e ser� deletado.

        else fwrite(&ing1, sizeof(ingredientes), 1, pFile1); // Escreve os ingredientes n�o deletados no arquivo "temp.txt".
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r"); // Abre o arquivo "temp.txt" para leitura.
        pFile = fopen("estoque_ingredientes.txt", "w"); // Abre o arquivo "estoque_ingredientes.txt" para escrita.

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1)) fwrite(&ing1, sizeof(ingredientes), 1, pFile); // Escreve os ingredientes n�o deletados de volta no arquivo "estoque_ingredientes.txt".

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Ingrediente n�o encontrado!\n"); // Exibe uma mensagem se o ingrediente n�o for encontrado no arquivo.
}

