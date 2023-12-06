#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void qtdIngredientes()
{
    FILE *pFile; // Declara um ponteiro de arquivo.
    pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo de estoque de ingredientes para leitura.

    fseek(pFile, 0, SEEK_END); // Move o cursor do arquivo para o final (fim do arquivo).
    int n = ftell(pFile) / sizeof(ingredientes); // Calcula o número de registros (ingredientes) no arquivo.

    printf("\nQuantidade de ingredientes em estoque é de: %i\n", n); // Exibe a quantidade de ingredientes.

    fclose(pFile); // Fecha o arquivo de estoque de ingredientes.
}

