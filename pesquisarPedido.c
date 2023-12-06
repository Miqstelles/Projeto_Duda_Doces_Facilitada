#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "cores.h"

void pesquisarPedido()
{
    while(1)
    {
        system("cls");
        vendas vnd; // Declara a estrutura chamada vendas.
        FILE *pFile; // Declara um ponteiro de arquivo.

        pFile = fopen("vendas.txt", "r"); // Abre o arquivo de vendas para leitura.

        int codigo, encontrou = 0;

        codigo = verificacaoCodigo("\nInsira o c�digo do pedido(0 - Sair): ", RED "\nERRO INSIRA UM C�DIGO V�LIDO\n" RESET);
        if(codigo == 0) break;

        char tipoProduto[3][80] = {"Bolo", "Doce", "Sobremesa"};

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

                    printf(GREEN "\nC�digo: " RESET "%i\n", produto.codigo); // Exibe o c�digo do produto.
                    printf(RED "Nome: " RESET "%s\n", produto.nome); // Exibe o nome do produto.
                    printf(YELLOW "Tipo: " RESET "%s\n", tipoProduto[produto.tipo - 1]); // Exibe o tipo do produto com base no valor num�rico.
                    printf("\nQuantidade de Ingredientes: %i\n", produto.qtdIngredientes); // Exibe a quantidade de ingredientes no produto.

                    printf(YELLOW"\nIngredientes:\n" RESET);
                    for (int j = 0; j < produto.qtdIngredientes; j++)
                    {
                        int codigoIngrediente = produto.listaIngredientes[j];
                        char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
                        if (strstr(nomeIngrediente, "(DESATIVADO)") == NULL)
                        {
                            printf(GREEN "  ID:" RESET " %i " GREEN "Nome: " RESET "%s\n", codigoIngrediente, nomeIngrediente); // Exibe o c�digo e nome do ingrediente.
                        }
                    }
                    printf("\n  -------------------\n");
                    printf("\n");
                }

                printf("Pre�o Total do Pedido: " GREEN "R$ %.2f\n" RESET, valorPedido);

                printf("------------------------------------------");
                printf("\n\n");

                encontrou = 1;
            }
        }
        if (!encontrou) printf(RED "Pedido n�o encontrado!\n" RESET); // Exibe uma mensagem se o pedido n�o for encontrado.

        int escolha;

        escolha = verificacaoCodigo("\n1 - Continuar \n0 - Sair \nInsira uma op��o: ", RED "\nERRO INSIRA UMA OP��O V�LIDA\n" RESET);
        if(escolha == 0) break;

        fclose(pFile); // Fecha o arquivo de vendas.
    }
    system("cls");
}
