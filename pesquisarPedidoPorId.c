#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cores.h"

void pesquisarPedidoPorID(int codigoPedido) {
    system("cls");
    FILE *pFile = fopen("vendas.txt", "r");
    vendas vnd;

    int encontrado = 0;
    char status[3][80] = {YELLOW "Em andamento" RESET, RED "Cancelado" RESET, GREEN "Concluido" RESET};

    while (fread(&vnd, sizeof(vendas), 1, pFile) == 1) {
        if (vnd.codigo == codigoPedido) {
            encontrado = 1;

            printf("\n  Detalhes do Pedido:\n");
            printf("\n-----------------------------------");
            printf(GREEN "\n  Código: " RESET "%i \n  Status: %s\n", vnd.codigo, status[vnd.status -1]);
            printf(YELLOW"  Cliente: " RESET "%s", vnd.nomeCliente);
            printf("\n-----------------------------------");

            printf(GREEN"\n  Pedidos\n" RESET);

            float valorPedido = 0;
            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto); // Obtém informações do produto pelo código.

                valorPedido += produto.preco; // Adiciona o preço do produto ao valor total do pedido.
                printf(RED"    Nome: " RESET "%s\n", produto.nome); // Exibe o nome do produto no pedido.
            }

            printf("-----------------------------------");
            printf("\n  Preço Total do Pedido: "YELLOW "R$ %.2f" RESET, valorPedido); // Exibe o preço total do pedido com duas casas decimais.
            printf("\n-----------------------------------\n\n");

            break;
        }
    }

    if (!encontrado) printf("  Pedido não encontrado.\n");



    fclose(pFile);
}

