#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "cores.h"

void listarVendas(){
    vendas vnd; // Declara a estrutura chamada vendas.
    int escolha;

    do
    {
        FILE *pFile = fopen("vendas.txt", "r"); // Abre o arquivo "vendas.txt" para leitura.

        while (fread(&vnd, sizeof(vendas), 1, pFile)) // L� um registro de vendas do arquivo.
        {
            printf(GREEN "\nC�digo: " RESET "%i\n", vnd.codigo); // Exibe o c�digo da venda.
            printf(RED "Cliente: "RESET "%s\n" , vnd.nomeCliente); // Exibe o nome do cliente.

            printf(YELLOW "\nProdutos:\n" RESET);

            float valorPedido = 0;

            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto); // Obt�m informa��es do produto pelo c�digo.

                valorPedido += produto.preco; // Adiciona o pre�o do produto ao valor total do pedido.
                printf(GREEN "  Nome: " RESET "%s\n" , produto.nome); // Exibe o nome do produto no pedido.
            }

            printf("\nPre�o Total do Pedido: " GREEN "R$ %.2f\n" RESET, valorPedido); // Exibe o pre�o total do pedido com duas casas decimais.

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
        system("cls");
    } while (escolha != 0);

    system("cls"); // Limpa a tela antes de sair da fun��o.
}
