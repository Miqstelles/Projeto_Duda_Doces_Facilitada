#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

int codigoJaExisteCardapio(int codigo){
    FILE *file = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    if (file)
    {
        cardapio temp; // Declara uma estrutura temporária chamada cardapio.

        while (fread(&temp, sizeof(cardapio), 1, file))
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
