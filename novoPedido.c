#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

void novoPedido()
{
    FILE *pFile;
    FILE *pFile1;

    vendas *vnd;
    cardapio cardap;

    int n = 1, i;

    vnd = (vendas *)calloc(n, sizeof(vendas));
    pFile = fopen("vendas.txt", "a");
    pFile1 = fopen("cardapio.txt", "r");

    for (i = 0; i < n; i++)
    {
        vnd[i].codigo = obterProximoCodigoVenda();

        fflush(stdin);
        printf("Insira o nome do cliente: ");
        scanf("%[^\n]s", vnd[i].nomeCliente);

        vnd[i].qtdProdutos = 0;

        listarCardapio();
        while (1)
        {
            int codigoProduto;

            printf("Insira o código do produto a ser adicionado (0 para finalizar): ");
            scanf("%i", &codigoProduto);

            if (codigoProduto == 0) break;

            int produtoExiste = 0;

            rewind(pFile1);
            while (fread(&cardap, sizeof(cardapio), 1, pFile1))
            {
                if (cardap.codigo == codigoProduto)
                {
                    produtoExiste = 1;
                    vnd[i].pedido[vnd[i].qtdProdutos] = codigoProduto;
                    vnd[i].qtdProdutos++;
                    printf("Produto adicionado ao produto.\n");
                    break;
                }
            }

            if (!produtoExiste) printf("Código de produto inexistente. Tente novamente.\n");
        }

        fwrite(&vnd[i], sizeof(vendas), 1, pFile);
    }
    fclose(pFile);
}
