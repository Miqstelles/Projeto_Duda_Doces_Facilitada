#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

char* getNomeIngredientePorCodigo(int codigo)
{
    FILE *pFile = fopen("estoque_ingredientes.txt", "r");
    ingredientes ing1;
    char *nomeIngrediente = NULL;

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            nomeIngrediente = strdup(ing1.nome);
            break;
        }
    }

    fclose(pFile);

    return nomeIngrediente;
}
