#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "verificacao.h"
#include "cores.h"

void listarClientes()
{
    cliente clnt;
    char escolha;
    do
    {
        FILE *pFile;
        pFile = fopen("clientes.txt", "r");

        printf("\n ========================================================================");
        printf("\n \tClientes \n");
        printf("\n \t" GREEN "Código " RESET RED "\t Nome " RESET YELLOW "\t\t Pedidos" RESET);

        while (fread(&clnt, sizeof(cliente), 1, pFile) == 1)
        {
            printf("\n \t%-9i%-16s", clnt.codigo, clnt.nome);

            int numPedidos = 0;
            printf("[");
            for (int i = sizeof(clnt.pedidos) / sizeof(clnt.pedidos[0]) - 1; i >= 0; i--)
            {
                if (clnt.pedidos[i] == 0) continue;
                printf("%i", clnt.pedidos[i]);

                if (i > 0 && clnt.pedidos[i - 1] != 0) printf(", ");
                numPedidos++;

                if (numPedidos >= 5)
                {
                    printf("...");
                    break;
                }
            }
            printf("]");
        }
        printf("\n ========================================================================\n");


        escolha = verificacaoCodigo("\n  " RED "1 -" RESET " Detalhar Pedido" "\n  " RED "0 -" RESET " Sair" "\n\n Insira uma opção: ", RED "\n ERRO! Digite uma opção válida\n" RESET);

        int codigoCliente;

        if(escolha == 1)
        {
            codigoCliente = verificacaoCodigo("\n Insira o ID do cliente para detalhar pedidos(0 - Voltar): ", RED "\n  ERRO! Digite um ID de cliente válido\n" RESET);
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
        int codigoPedido = 1;

        if (clienteEncontrado)
        {
            do
            {
                printf("\n  Pedidos do cliente %s: ", clnt.nome);

                printf("[");

                int ultimoIndice = 0;
                while (ultimoIndice < sizeof(clnt.pedidos) / sizeof(clnt.pedidos[0]) && clnt.pedidos[ultimoIndice] != 0) ultimoIndice++;

                for (int i = ultimoIndice - 1; i >= 0; i--)
                {
                    printf("%i", clnt.pedidos[i]);

                    if (i > 0) printf(", ");
                }

                printf("]\n");
                codigoPedido = verificacaoCodigo("\n\n  Insira uma opção(0 - Voltar): ", RED "\n\  ERRO! Digite uma opção válida\n" RESET);

                if(codigoPedido == 0)
                {
                    system("cls");
                    break;
                }

                while(!pedidoPertenceAoCliente(codigoPedido, clnt) && codigoPedido !=0)
                    codigoPedido = verificacaoCodigo(RED " \n Pedido não encontrado, insira um novo ID de pedido(0 - Sair): " RESET,  RED "\nERRO! Digite um ID de cliente válido\n" RESET);

                if(codigoPedido == 0)
                {
                    system("cls");
                    break;
                }

                pesquisarPedidoPorID(codigoPedido);

                escolhaPedido = verificacaoCodigo("Pesquisar outro pedido pelo id(0 - Voltar, 1 - Continuar): ", RED "\nERRO! Digite um ID de cliente válido\n" RESET);

                system("cls");
            }
            while(escolhaPedido !=0);
        }
        else if(codigoCliente != 0)
        {
            if(codigoPedido == 0) break;
            printf(RED "\n  Cliente com o ID %i não encontrado.\n" RESET, codigoCliente);
        }

        fclose(pFile);
    }
    while (escolha != 0);
    system("cls");
}
