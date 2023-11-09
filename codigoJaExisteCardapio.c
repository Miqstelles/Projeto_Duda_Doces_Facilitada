#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

int codigoJaExisteCardapio(int codigo){
    FILE *file = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    if (file)
    {
        cardapio temp; // Declara uma estrutura tempor�ria chamada cardapio.

        while (fread(&temp, sizeof(cardapio), 1, file))
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
