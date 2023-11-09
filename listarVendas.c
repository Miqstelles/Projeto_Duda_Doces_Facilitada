#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

void listarVendas(){
    vendas vnd; // Declara a estrutura chamada vendas.
    int escolha;

    do
    {
        FILE *pFile = fopen("vendas.txt", "r"); // Abre o arquivo "vendas.txt" para leitura.

        while (fread(&vnd, sizeof(vendas), 1, pFile)) // L� um registro de vendas do arquivo.
        {
            printf("\nC�digo: %i\n", vnd.codigo); // Exibe o c�digo da venda.
            printf("Cliente: %s\n", vnd.nomeCliente); // Exibe o nome do cliente.

            printf("Produtos:\n");

            float valorPedido = 0;

            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto); // Obt�m informa��es do produto pelo c�digo.

                valorPedido += produto.preco; // Adiciona o pre�o do produto ao valor total do pedido.
                printf("  Nome: %s\n", produto.nome); // Exibe o nome do produto no pedido.
            }

            printf("\nPre�o Total do Pedido: %.2f\n", valorPedido); // Exibe o pre�o total do pedido com duas casas decimais.

            printf("------------------------------------------\n------------------------------------------");
            printf("\n\n"); // Exibe linhas de separa��o ap�s cada venda.
        }

        printf("\n1 - Detalhar pedido: ");
        printf("\n0 - Sair");

        int read = 0;

        while (read != 1)
        {
            printf("\n\nInsira uma op��o: ");
            read = scanf("%i", &escolha);

            if (read != 1)
            {
                printf("ERRO! Digite uma op��o v�lida");
                scanf("%*[^\n]"); // Limpa o buffer de entrada em caso de entrada inv�lida.
            }
        }

        if (escolha == 1)
        {
            int escolhaPedido;
            do
            {
                pesquisarPedido(); // Fun��o para pesquisar um pedido em detalhes.
                printf("\n0 - Voltar: ");
                scanf("%i", &escolhaPedido);
            } while (escolhaPedido != 0);
            system("cls"); // Limpa a tela ap�s visualizar o pedido em detalhes.
        }

        fclose(pFile); // Fecha o arquivo ap�s a leitura.

    } while (escolha != 0);

    system("cls"); // Limpa a tela antes de sair da fun��o.
}
