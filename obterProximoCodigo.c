#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

int obterProximoCodigo(){
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo de ingredientes.
    ingredientes ing;
    int maiorCodigo = 0;

    pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo de ingredientes para leitura.

    if (pFile != NULL)
    {
        while (fread(&ing, sizeof(ingredientes), 1, pFile) == 1)
        {
            if (ing.codigo > maiorCodigo) maiorCodigo = ing.codigo; // Encontra o maior código existente no arquivo.
        }

        fclose(pFile); // Fecha o arquivo de ingredientes.
    }
    return maiorCodigo + 1; // Retorna o próximo código disponível (maior código + 1).
}

