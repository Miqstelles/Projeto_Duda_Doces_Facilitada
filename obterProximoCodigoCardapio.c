#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

int obterProximoCodigoCardapio()
{
    FILE *pFile;
    cardapio cardap;
    int maiorCodigo = 0;

    pFile = fopen("cardapio.txt", "r");

    if (pFile != NULL)
    {
        while (fread(&cardap, sizeof(cardapio), 1, pFile) == 1)
        {
            if (cardap.codigo > maiorCodigo) maiorCodigo = cardap.codigo;
        }

        fclose(pFile);
    }

    return maiorCodigo + 1;
}
