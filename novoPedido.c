#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

void novoPedido()
{
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo de vendas.
    FILE *pFile1; // Declara um ponteiro de arquivo para o arquivo de produtos.
    vendas *vnd; // Declara um ponteiro para a estrutura chamada vendas.
    cardapio cardap; // Declara a estrutura chamada cardapio.

    int n = 1, i;

    vnd = (vendas *)calloc(n, sizeof(vendas)); // Aloca mem�ria para a estrutura vendas.
    pFile = fopen("vendas.txt", "a"); // Abre o arquivo "vendas.txt" em modo de ap�ndice.
    pFile1 = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    for (i = 0; i < n; i++)
    {
        vnd[i].codigo = obterProximoCodigoVenda(); // Obt�m o pr�ximo c�digo para a venda.

        fflush(stdin);
        printf("Insira o nome do cliente: ");
        scanf("%[^\n]s", vnd[i].nomeCliente); // L� o nome do cliente.

        vnd[i].qtdProdutos = 0; // Inicializa a quantidade de produtos no pedido.

        listarCardapio(); // Chama a fun��o listarCardapio para mostrar os produtos dispon�veis.
        while (1)
        {
            int codigoProduto;

            printf("Insira o c�digo do produto a ser adicionado (0 para finalizar): ");
            scanf("%i", &codigoProduto);

            if (codigoProduto == 0) break; // Finaliza a adi��o de produtos quando o c�digo � 0.

            int produtoExiste = 0;

            rewind(pFile1); // Volta ao in�cio do arquivo de produtos.
            while (fread(&cardap, sizeof(cardapio), 1, pFile1))
            {
                if (cardap.codigo == codigoProduto)
                {
                    produtoExiste = 1;
                    vnd[i].pedido[vnd[i].qtdProdutos] = codigoProduto;
                    vnd[i].qtdProdutos++;
                    printf("Produto adicionado ao pedido.\n");
                    break;
                }
            }

            if (!produtoExiste) printf("C�digo de produto inexistente. Tente novamente.\n");
        }

        fwrite(&vnd[i], sizeof(vendas), 1, pFile); // Escreve os dados da venda no arquivo.
    }
    fclose(pFile); // Fecha o arquivo de vendas.
}

