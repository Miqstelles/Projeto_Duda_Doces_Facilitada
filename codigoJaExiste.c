#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

int codigoJaExiste(int codigo)
{
    FILE *file = fopen("estoque_ingredientes.txt", "r");

    if (file)
    {
        ingredientes temp;

        while (fread(&temp, sizeof(ingredientes), 1, file))
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
