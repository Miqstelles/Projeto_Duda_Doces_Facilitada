#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "verificacao.h"
#include "cores.h"

void listarClientes()
{
    cliente clnt;
    int escolha;

    do
    {
        FILE *pFile;
        pFile = fopen("clientes.txt", "r");

        printf("\n ========================================================================");
        printf("\n \tClientes \n");
        printf("\n \t" GREEN "C�digo " RESET RED "\t Nome " RESET YELLOW "\t\t Pedidos" RESET);

        while (fread(&clnt, sizeof(cliente), 1, pFile) == 1)
        {
            printf("\n \t%-9i%-16s", clnt.codigo, clnt.nome);

            int numPedidos = 0;
            printf("[");
            for (int i = 0; i < 5 && clnt.pedidos[i] != 0; i++)
            {
                printf("%i", clnt.pedidos[i]);

                if (clnt.pedidos[i + 1] != 0) printf(", ");

                numPedidos++;

                if (numPedidos >= 5 && clnt.pedidos[numPedidos] != 0) printf("...");
            }
            printf("]");
        }
        printf("\n ========================================================================\n");

        int readCliente = 0;
        int codigoCliente;
        int read;

        printf("\n  " RED "1 -" RESET " Detalhar Pedido" );
        printf("\n  " RED "0 -" RESET " Sair" );

        while (read != 1)
        {
            printf("\n\n  Insira uma op��o: ");
            read = scanf("%i", &escolha);

            if (read != 1)
            {
                printf("ERRO! Digite uma op��o v�lida");
                scanf("%*[^\n]"); // Limpa o buffer de entrada em caso de entrada inv�lida.
            }
        }

        read = 0;

        if(escolha == 1)
        {
            while (readCliente != 1)
            {
                printf("\n\n  Insira o ID do cliente para detalhar pedidos(0 - Voltar): ");
                readCliente = scanf("%i", &codigoCliente);

                if (readCliente != 1)
                {
                    printf("ERRO! Digite um ID de cliente v�lido");
                    scanf("%*[^\n]"); // Limpa o buffer de entrada em caso de entrada inv�lida.
                }
            }
            system("cls");
        }
        else if(escolha == 0) break;


        fclose(pFile);
        pFile = fopen("clientes.txt", "r");

        int clienteEncontrado = 0;


        while (fread(&clnt, sizeof(cliente), 1, pFile) == 1)
        {
            if(codigoCliente == 0)
            {
                clienteEncontrado = 0;
                break;
            }
            if (clnt.codigo == codigoCliente)
            {
                clienteEncontrado = 1;
                break;
            }
        }

        int escolhaPedido;

        if (clienteEncontrado)
        {
            do
            {
                int codigoPedido;

                printf("\n  Pedidos do cliente %s: ", clnt.nome);

                printf("[");
                for (int i = 0; i < 200 && clnt.pedidos[i] != 0; i++)
                {
                    printf("%i", clnt.pedidos[i]);

                    if (clnt.pedidos[i + 1] != 0) printf(", ");
                }
                printf("]\n");

                printf("  Digite o ID do pedido a ser detalhado: ");
                scanf("%i", &codigoPedido);

                pesquisarPedidoPorID(codigoPedido);

                printf("Pesquisar outro pedido pelo id(0 - Voltar, 1 - Continuar): ");
                scanf("%d", &escolhaPedido);

                system("cls");
            }
            while(escolhaPedido !=0);
        }
        else if(codigoCliente != 0) printf("\n  Cliente com o ID %i n�o encontrado.\n", codigoCliente);


        fclose(pFile);
    }
    while (escolha != 0);
    system("cls");
}
