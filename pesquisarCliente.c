#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "clientes.h"
#include "cores.h"

void pesquisarCliente()
{
    cliente clnt;
    int escolhaFuncao;

    do
    {
        FILE *pFile;
        pFile = fopen("clientes.txt", "r");

        int escolha, codigo;
        char nome[80];

        printf("\nDeseja pesquisar o cliente pelo nome ou codigo? (1 - Nome, 2 - Codigo, 0 - Sair): ");
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            printf("\nInsira o nome do cliente: ");
            fflush(stdin);
            scanf("%[^\n]s", nome);
        }
        else if(escolha == 2)
        {
            printf("\nInsira o codigo do cliente: ");
            scanf("%d", &codigo);
        }

        printf("\n=========================================================");
        printf("\nCliente\n");
        printf(GREEN "\nCódigo " RESET RED "\t Nome " RESET "\t\t");

        int clienteEncontrado = 0;

        while (fread(&clnt, sizeof(cliente), 1, pFile) == 1)
        {
            if (escolha == 1)
            {
                if (strcasecmp(nome, clnt.nome) == 0)
                {
                    clienteEncontrado = 1;
                    printf("\n%-9i%-20s", clnt.codigo, clnt.nome);
                    break;
                }
            }
            else if (escolha == 2)
            {
                if (clnt.codigo == codigo)
                {
                    clienteEncontrado = 1;
                    printf("\n%-9i%-20s", clnt.codigo, clnt.nome);
                    break;
                }
            }
        }

        if(escolha == 0) break;

        int escolhaPedido;

        do
        {
            if (clienteEncontrado)
            {
                printf("\n\nPedidos do cliente %s:\n[", clnt.nome);

                for (int i = 0; i < 200 && clnt.pedidos[i] != 0; i++)
                {
                    printf("%i", clnt.pedidos[i]);

                    if (clnt.pedidos[i + 1] != 0) printf(", ");
                }

                printf("]\n");

                printf("Digite o ID do pedido a ser detalhado (0 para voltar): ");
                scanf("%i", &escolhaFuncao);

                if(escolhaFuncao == 0) {
                    system("cls");
                    break;
                }

                if (escolhaFuncao != 0)
                {
                    pesquisarPedidoPorID(escolhaFuncao);
                }

                printf("Pesquisar outro pedido pelo id(0 - Voltar, 1 - Continuar): ");
                scanf("%d", &escolhaPedido);
            }
            else
            {
                system("cls");
                printf("\n\n!!!CLIENTE NÃO ENCONTRADO!!!\n");
            }
        }
        while(escolhaPedido != 0);



        fclose(pFile);
    }
    while (1);

    system("cls");
}
