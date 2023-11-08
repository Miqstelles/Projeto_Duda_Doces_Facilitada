#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

int obterProximoCodigo()
{
    FILE *pFile;
    ingredientes ing;
    int maiorCodigo = 0;

    pFile = fopen("estoque_ingredientes.txt", "r");

    if (pFile != NULL)
    {
        while (fread(&ing, sizeof(ingredientes), 1, pFile) == 1)
        {
            if (ing.codigo > maiorCodigo) maiorCodigo = ing.codigo;
        }

        fclose(pFile);
    }
    return maiorCodigo + 1;
}
