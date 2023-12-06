#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

cardapio getProdutoPorCodigo(int codigo)
{
    FILE *pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.
    cardapio cardap; // Declara a estrutura chamada cardapio.
    cardapio produtoEncontrado; // Declara uma estrutura para armazenar o produto encontrado.

    while (fread(&cardap, sizeof(cardapio), 1, pFile)) // L� um registro de cardapio do arquivo.
    {
        if (cardap.codigo == codigo) // Verifica se o c�digo do produto corresponde ao c�digo fornecido.
        {
            produtoEncontrado = cardap; // Copia os dados do produto encontrado para a estrutura produtoEncontrado.
            break; // Sai do loop, pois o produto foi encontrado.
        }
    }
    fclose(pFile); // Fecha o arquivo ap�s a leitura.

    return produtoEncontrado; // Retorna a estrutura do produto encontrado ou uma estrutura vazia se o produto n�o for encontrado.
}
