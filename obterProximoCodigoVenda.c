#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

int obterProximoCodigoVenda()
{
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo de vendas.
    vendas vnd; // Declara a estrutura chamada vendas.
    int maiorCodigo = 0;

    pFile = fopen("vendas.txt", "r"); // Abre o arquivo de vendas para leitura.

    if (pFile != NULL)
    {
        while (fread(&vnd, sizeof(vendas), 1, pFile) == 1)
        {
            if (vnd.codigo > maiorCodigo) maiorCodigo = vnd.codigo; // Encontra o maior código existente no arquivo.
        }

        fclose(pFile); // Fecha o arquivo de vendas.
    }

    return maiorCodigo + 1; // Retorna o próximo código disponível (maior código + 1).
}
