#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

int codigoJaExiste(int codigo)
{
    FILE *file = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.

    if (file){
        ingredientes temp; // Declara uma estrutura tempor�ria chamada ingredientes.

        while (fread(&temp, sizeof(ingredientes), 1, file))
        {
            if (temp.codigo == codigo) // Verifica se o c�digo fornecido corresponde a um c�digo existente no arquivo.
            {
                fclose(file); // Fecha o arquivo ap�s encontrar o c�digo correspondente.
                return 1; // Retorna 1 para indicar que o c�digo j� existe.
            }
        }

        fclose(file); // Fecha o arquivo ap�s a busca.
    }

    return 0; // Retorna 0 para indicar que o c�digo n�o foi encontrado no arquivo.
}
