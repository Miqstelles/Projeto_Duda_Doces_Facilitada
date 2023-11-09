#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

int codigoJaExiste(int codigo)
{
    FILE *file = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.

    if (file){
        ingredientes temp; // Declara uma estrutura temporária chamada ingredientes.

        while (fread(&temp, sizeof(ingredientes), 1, file))
        {
            if (temp.codigo == codigo) // Verifica se o código fornecido corresponde a um código existente no arquivo.
            {
                fclose(file); // Fecha o arquivo após encontrar o código correspondente.
                return 1; // Retorna 1 para indicar que o código já existe.
            }
        }

        fclose(file); // Fecha o arquivo após a busca.
    }

    return 0; // Retorna 0 para indicar que o código não foi encontrado no arquivo.
}
