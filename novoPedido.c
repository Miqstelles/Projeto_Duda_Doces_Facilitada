#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "clientes.h"

void novoPedido()
{
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo de vendas.
    FILE *pFile1;   // Declara um ponteiro de arquivo para o arquivo de produtos.
    FILE *pFile2;  // Declara um ponteiro de arquivo para o arquivo de clientes.

    vendas *vnd; // Declara um ponteiro para a estrutura chamada vendas.
    cardapio cardap;
    cliente clnt;

    vnd = (vendas *)calloc(1, sizeof(vendas)); // Aloca mem�ria para a estrutura vendas.
    pFile = fopen("vendas.txt", "a"); // Abre o arquivo "vendas.txt" em modo de ap�ndice.
    pFile1 = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.
    pFile2 = fopen("clientes.txt", "r+"); // Abre o arquivo "cardapio.txt" para leitura.

    vnd[0].codigo = obterProximoCodigoVenda(); // Obt�m o pr�ximo c�digo para a venda.

    int codigo;
    listarClientesPedido();


    printf("Insira o codigo do cliente que esta realizando o pedido: ");
    scanf("%d", &codigo);

    while (fread(&clnt, sizeof(cliente), 1, pFile2))
    {
        if(clnt.codigo == codigo)
        {
            strcpy(vnd[0].nomeCliente, clnt.nome);
            // Encontra o pr�ximo �ndice dispon�vel no array de pedidos
            int i;
            for (i = 0; i < 200; i++)
            {
                if (clnt.pedidos[i] == 0)
                {
                    clnt.pedidos[i] = vnd[0].codigo;
                    break;
                }
            }

            fseek(pFile2, -sizeof(cliente), SEEK_CUR);
            fwrite(&clnt, sizeof(cliente), 1, pFile2);
            fflush(pFile2);

            break;
        }
    }

    vnd[0].qtdProdutos = 0; // Inicializa a quantidade de produtos no pedido.

    listarCardapioPedido(); // Chama a fun��o listarCardapio para mostrar os produtos dispon�veis.
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
                vnd[0].pedido[vnd[0].qtdProdutos] = codigoProduto;
                vnd[0].qtdProdutos++;
                printf("Produto adicionado ao pedido.\n");
                break;
            }
        }

        if (!produtoExiste) printf("C�digo de produto inexistente. Tente novamente.\n");
    }

    fwrite(&vnd[0], sizeof(vendas), 1, pFile); // Escreve os dados da venda no arquivo.

    fclose(pFile); // Fecha o arquivo de vendas.
}
