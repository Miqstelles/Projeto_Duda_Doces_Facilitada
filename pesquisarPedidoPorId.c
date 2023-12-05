#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cores.h"

void pesquisarPedidoPorID(int codigoPedido) {
    system("cls");
    FILE *pFile = fopen("vendas.txt", "r");
    vendas vnd;

    int encontrado = 0;

    while (fread(&vnd, sizeof(vendas), 1, pFile) == 1) {
        if (vnd.codigo == codigoPedido) {
            encontrado = 1;

            printf("\n  Detalhes do Pedido:\n");
            printf("\n-----------------------------------");
            printf(YELLOW "\n  C�digo: " RESET "%i\n", vnd.codigo);
            printf(YELLOW"  Cliente: " RESET "%s", vnd.nomeCliente);
            printf("\n-----------------------------------");

            printf(GREEN"\n  Pedidos\n" RESET);

            float valorPedido = 0;
            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto); // Obt�m informa��es do produto pelo c�digo.

                valorPedido += produto.preco; // Adiciona o pre�o do produto ao valor total do pedido.
                printf(RED"    Nome: " RESET "%s\n", produto.nome); // Exibe o nome do produto no pedido.
            }

            printf("-----------------------------------");
            printf("\n  Pre�o Total do Pedido: "YELLOW "R$ %.2f" RESET, valorPedido); // Exibe o pre�o total do pedido com duas casas decimais.
            printf("\n-----------------------------------\n\n");

            break;
        }
    }

    if (!encontrado) printf("  Pedido n�o encontrado.\n");



    fclose(pFile);
}

