#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

int obterProximoCodigoCardapio(){
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo do card�pio.
    cardapio cardap; // Declara a estrutura chamada cardapio.
    int maiorCodigo = 0;

    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo do card�pio para leitura.

    if (pFile != NULL)
    {
        while (fread(&cardap, sizeof(cardapio), 1, pFile) == 1)
        {
            if (cardap.codigo > maiorCodigo) maiorCodigo = cardap.codigo; // Encontra o maior c�digo existente no arquivo.
        }

        fclose(pFile); // Fecha o arquivo do card�pio.
    }

    return maiorCodigo + 1; // Retorna o pr�ximo c�digo dispon�vel (maior c�digo + 1).
}

