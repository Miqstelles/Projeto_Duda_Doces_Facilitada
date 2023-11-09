#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void deletarProdutoCardapio()
{
    listarCardapio(); // Chama a função listarCardapio para mostrar os produtos disponíveis no cardápio.

    cardapio cardap; // Declara a estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "temp.txt".
    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.
    pFile1 = fopen("temp.txt", "w"); // Abre o arquivo "temp.txt" para escrita.

    int codigo, encontrou = 0;
    printf("Insira o código do produto a ser deletado: ");
    scanf("%i", &codigo); // Lê o código do produto a ser deletado.

    while (fread(&cardap, sizeof(cardapio), 1, pFile)) // Lê um registro de cardapio do arquivo "cardapio.txt".
    {
        if (cardap.codigo == codigo)
        {
            encontrou = 1; // Define a flag para indicar que o produto foi encontrado e será deletado.
            printf("Produto: %s deletado com sucesso!\n", cardap.nome); // Exibe uma mensagem informando que o produto foi deletado com sucesso.
        }
        else fwrite(&cardap, sizeof(cardapio), 1, pFile1); // Escreve os produtos não deletados no arquivo "temp.txt".
    }

    fclose(pFile); // Fecha o arquivo "cardapio.txt" após a leitura.
    fclose(pFile1); // Fecha o arquivo "temp.txt" após a escrita.

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r"); // Abre o arquivo "temp.txt" para leitura.
        pFile = fopen("cardapio.txt", "w"); // Abre o arquivo "cardapio.txt" para escrita.

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) // Lê um registro de cardapio do arquivo "temp.txt".
        {
            fwrite(&cardap, sizeof(cardapio), 1, pFile); // Escreve os produtos não deletados de volta no arquivo "cardapio.txt".
        }

        fclose(pFile1); // Fecha o arquivo "temp.txt" após a leitura.
        fclose(pFile); // Fecha o arquivo "cardapio.txt" após a escrita.
    }
    else printf("Produto não encontrado!\n"); // Exibe uma mensagem se o produto não for encontrado no arquivo.
}
