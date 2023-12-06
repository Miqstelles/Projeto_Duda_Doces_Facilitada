#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

char* getNomeIngredientePorCodigo(int codigo)
{
    FILE *pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.
    ingredientes ing1; // Declara a estrutura chamada ingredientes.
    char *nomeIngrediente = NULL; // Inicializa um ponteiro para char como NULL.

    while (fread(&ing1, sizeof(ingredientes), 1, pFile)) // L� um registro de ingredientes do arquivo.
    {
        if (ing1.codigo == codigo) // Verifica se o c�digo do ingrediente corresponde ao c�digo fornecido.
        {
            nomeIngrediente = strdup(ing1.nome); // Aloca mem�ria e copia o nome do ingrediente correspondente.
            break; // Sai do loop, pois o ingrediente foi encontrado.
        }
    }

    fclose(pFile); // Fecha o arquivo ap�s a leitura.

    return nomeIngrediente; // Retorna o ponteiro para o nome do ingrediente ou NULL se o ingrediente n�o for encontrado.
}
