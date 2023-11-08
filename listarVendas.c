#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

void listarVendas()
{
    vendas vnd;

    int escolha;

    do
    {

        FILE *pFile = fopen("vendas.txt", "r");

        while (fread(&vnd, sizeof(vendas), 1, pFile))
        {
            printf("\nCódigo: %i\n", vnd.codigo);
            printf("Cliente: %s\n", vnd.nomeCliente);

            printf("Produtos:\n");

            float valorPedido = 0;

            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto);

                valorPedido += produto.preco;
                printf("  Nome: %s\n", produto.nome);
            }

            printf("\nPreço Total do Pedido: %.2f\n", valorPedido);

            printf("------------------------------------------\n------------------------------------------");
            printf("\n\n");
        }

        printf("\n1 - Detalhar pedido: ");
        printf("\n0 - Sair");

        int read = 0;

        while (read != 1)
        {
            printf("\n\nInsira uma opção: ");
            read = scanf("%i", &escolha);

            if (read != 1)
            {
                printf("ERRO! Digite uma opção valida");
                scanf("%*[^\n]");
            }
        }

        if(escolha == 1){
            int escolhaPedido;
            do{
                pesquisarPedido();
                printf("\n0 - Voltar: ");
                scanf("%i", &escolhaPedido);
            }while(escolhaPedido != 0);
            system("cls");
        }

        fclose(pFile);

    } while(escolha !=0);

    system("cls");

}
