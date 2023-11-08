#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

int obterProximoCodigoVenda()
{
    FILE *pFile;
    vendas vnd;
    int maiorCodigo = 0;

    pFile = fopen("vendas.txt", "r");

    if (pFile != NULL)
    {
        while (fread(&vnd, sizeof(vendas), 1, pFile) == 1)
        {
            if (vnd.codigo > maiorCodigo) maiorCodigo = vnd.codigo;
        }

        fclose(pFile);
    }

    return maiorCodigo + 1;
}
