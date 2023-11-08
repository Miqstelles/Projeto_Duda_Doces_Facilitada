#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void qtdIngredientes()
{
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");
    fseek(pFile, 0, SEEK_END);
    int n = ftell(pFile) / sizeof(ingredientes);
    printf("\nQuantidade de ingredientes em estoque é de: %i\n", n);
}
