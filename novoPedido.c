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

    vnd = (vendas *)calloc(n, sizeof(vendas)); // Aloca memória para a estrutura vendas.
    pFile = fopen("vendas.txt", "a"); // Abre o arquivo "vendas.txt" em modo de apêndice.
    pFile1 = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.

    for (i = 0; i < n; i++)
    {
        vnd[i].codigo = obterProximoCodigoVenda(); // Obtém o próximo código para a venda.

        fflush(stdin);
        printf("Insira o nome do cliente: ");
        scanf("%[^\n]s", vnd[i].nomeCliente); // Lê o nome do cliente.

        vnd[i].qtdProdutos = 0; // Inicializa a quantidade de produtos no pedido.

        listarCardapio(); // Chama a função listarCardapio para mostrar os produtos disponíveis.
        while (1)
        {
            int codigoProduto;

            printf("Insira o código do produto a ser adicionado (0 para finalizar): ");
            scanf("%i", &codigoProduto);

            if (codigoProduto == 0) break; // Finaliza a adição de produtos quando o código é 0.

            int produtoExiste = 0;

            rewind(pFile1); // Volta ao início do arquivo de produtos.
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

            if (!produtoExiste) printf("Código de produto inexistente. Tente novamente.\n");
        }

        fwrite(&vnd[i], sizeof(vendas), 1, pFile); // Escreve os dados da venda no arquivo.
    }
    fclose(pFile); // Fecha o arquivo de vendas.
}

