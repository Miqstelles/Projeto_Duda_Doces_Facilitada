#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

cardapio getProdutoPorCodigo(int codigo)
{
    FILE *pFile = fopen("cardapio.txt", "r");
    cardapio cardap;
    cardapio produtoEncontrado;

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            produtoEncontrado = cardap;
            break;
        }
    }

    fclose(pFile);

    return produtoEncontrado;
}
