#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

int obterProximoCodigoCardapio(){
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo do cardápio.
    cardapio cardap; // Declara a estrutura chamada cardapio.
    int maiorCodigo = 0;

    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo do cardápio para leitura.

    if (pFile != NULL)
    {
        while (fread(&cardap, sizeof(cardapio), 1, pFile) == 1)
        {
            if (cardap.codigo > maiorCodigo) maiorCodigo = cardap.codigo; // Encontra o maior código existente no arquivo.
        }

        fclose(pFile); // Fecha o arquivo do cardápio.
    }

    return maiorCodigo + 1; // Retorna o próximo código disponível (maior código + 1).
}

