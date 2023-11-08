#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

int codigoJaExisteCardapio(int codigo)
{
    FILE *file = fopen("cardapio.txt", "r");

    if (file)
    {
        cardapio temp;

        while (fread(&temp, sizeof(cardapio), 1, file))
        {
            if (temp.codigo == codigo)
            {
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    }

    return 0;
}
