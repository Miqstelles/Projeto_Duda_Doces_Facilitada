#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

void pesquisarPedido()
{
    vendas vnd; // Declara a estrutura chamada vendas.
    FILE *pFile; // Declara um ponteiro de arquivo.

    pFile = fopen("vendas.txt", "r"); // Abre o arquivo de vendas para leitura.

    int codigo, encontrou = 0;
    printf("Insira o c�digo do pedido: ");
    scanf("%i", &codigo); // Solicita o c�digo do pedido a ser pesquisado.

    while (fread(&vnd, sizeof(vendas), 1, pFile))
    {
        if (vnd.codigo == codigo)
        {
            system("cls"); // Limpa a tela (usando "cls" no Windows).

            printf("\nC�digo do Pedido: %i\n", vnd.codigo);
            printf("Cliente: %s\n\n", vnd.nomeCliente);

            printf("Produtos:\n");

            float valorPedido = 0;

            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto);

                valorPedido += produto.preco;

                printf("  Nome: %s\n", produto.nome);
                printf("  Tipo: %s\n", (produto.tipo == 1) ? "Bolo" : (produto.tipo == 2) ? "Doce" : "Sobremesa");
                printf("  Pre�o: %.2f\n\n", produto.preco);

                printf("  Ingredientes:\n");
                for (int j = 0; j < produto.qtdIngredientes; j++)
                {
                    int codigoIngrediente = produto.listaIngredientes[j];
                    char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
                    printf("    %s\n", nomeIngrediente);
                }
                printf("\n  -------------------\n");
                printf("\n");
            }

            printf("Pre�o Total do Pedido: %.2f\n", valorPedido);

            printf("------------------------------------------");
            printf("\n\n");

            encontrou = 1;
        }
    }
    if (!encontrou) printf("Pedido n�o encontrado!\n"); // Exibe uma mensagem se o pedido n�o for encontrado.

    fclose(pFile); // Fecha o arquivo de vendas.
}
