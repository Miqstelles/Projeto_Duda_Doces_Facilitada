#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void deletarProdutoCardapio()
{
    listarCardapio(); // Chama a fun��o listarCardapio para mostrar os produtos dispon�veis no card�pio.

    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "temp.txt".
    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.
    pFile1 = fopen("temp.txt", "w"); // Abre o arquivo "temp.txt" para escrita.

    int codigo, encontrou = 0;
    printf("Insira o c�digo do produto a ser deletado: ");
    scanf("%i", &codigo); // L� o c�digo do produto a ser deletado.

    while (fread(&cardap, sizeof(cardapio), 1, pFile)) // L� um registro de cardapio do arquivo "cardapio.txt".
    {
        if (cardap.codigo == codigo)
        {
            encontrou = 1; // Define a flag para indicar que o produto foi encontrado e ser� deletado.
            printf("Produto: %s deletado com sucesso!\n", cardap.nome); // Exibe uma mensagem informando que o produto foi deletado com sucesso.
        }
        else fwrite(&cardap, sizeof(cardapio), 1, pFile1); // Escreve os produtos n�o deletados no arquivo "temp.txt".
    }

    fclose(pFile); // Fecha o arquivo "cardapio.txt" ap�s a leitura.
    fclose(pFile1); // Fecha o arquivo "temp.txt" ap�s a escrita.

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r"); // Abre o arquivo "temp.txt" para leitura.
        pFile = fopen("cardapio.txt", "w"); // Abre o arquivo "cardapio.txt" para escrita.

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) // L� um registro de cardapio do arquivo "temp.txt".
        {
            fwrite(&cardap, sizeof(cardapio), 1, pFile); // Escreve os produtos n�o deletados de volta no arquivo "cardapio.txt".
        }

        fclose(pFile1); // Fecha o arquivo "temp.txt" ap�s a leitura.
        fclose(pFile); // Fecha o arquivo "cardapio.txt" ap�s a escrita.
    }
    else printf("Produto n�o encontrado!\n"); // Exibe uma mensagem se o produto n�o for encontrado no arquivo.
}
