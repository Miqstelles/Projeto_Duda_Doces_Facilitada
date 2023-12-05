#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "clientes.h"
#include "cores.h"
#define MAX_LEN 128

void pesquisarCliente()
{

    do
    {
        cliente clnt;
        FILE *pFile;
        pFile = fopen("clientes.txt", "r");

        int escolha, codigo = 0;
        char nome[MAX_LEN] = {' '};

        int read = 0;

        escolha = verificacaoCodigo("\nDeseja pesquisar o cliente pelo nome ou codigo? (1 - Nome, 2 - Codigo, 0 - Sair): ",  RED "\nInsira um op��o v�lida. Tente novamente." RESET);
        if(escolha == 0) break;

        while(escolha < 0 || escolha > 2){
            printf(RED "\nERRO INSIRA UMA ESCOLHA V�LIDA" RESET);
            escolha = verificacaoCodigo("\nDeseja pesquisar o cliente pelo nome ou codigo? (1 - Nome, 2 - Codigo, 0 - Sair): ",  RED "\nInsira um op��o v�lida. Tente novamente." RESET);
        }

        if (escolha == 1)
        {
            printf("\nInsira o nome do cliente: ");
            fflush(stdin);
            scanf("%[^\n]s", nome);
        }
        else if(escolha == 2)
            codigo = verificacaoCodigo("\nInsira o c�digo do cliente: ", RED "\nInsira um c�digo v�lido. Tente novamente." RESET);

        printf("\n=========================================================");
        printf("\nCliente\n");
        printf(GREEN "\nC�digo " RESET RED "\t Nome " RESET "\t\t");

        int clienteEncontrado = 0;

        while (fread(&clnt, sizeof(cliente), 1, pFile) == 1)
        {
            if (escolha == 1 || escolha == 2)
            {
                if (strcasecmp(nome, clnt.nome) == 0 || clnt.codigo == codigo)
                {
                    clienteEncontrado = 1;
                    printf("\n%-9i%-20s", clnt.codigo, clnt.nome);
                    break;
                }
            }
        }

        int escolhaPedido;
        int escolhaFuncao;

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

                escolhaFuncao = verificacaoCodigo("Digite o ID do pedido a ser detalhado (0 para voltar): ", RED "\nInsira um c�digo v�lido. Tente novamente.\n" RESET);

                if(escolhaFuncao == 0)
                {
                    system("cls");
                    break;
                }

                while(!pedidoPertenceAoCliente(escolhaFuncao, clnt) && escolhaFuncao !=0)
                    escolhaFuncao = verificacaoCodigo(RED " \nPedido n�o encontrado, insira um novo ID de pedido(0 para voltar): " RESET, RED "\nERRO! Digite um ID de cliente v�lido\n" RESET);

                if(escolhaFuncao == 0)
                {
                    system("cls");
                    break;
                }

                if (escolhaFuncao != 0) pesquisarPedidoPorID(escolhaFuncao);

                escolhaPedido = verificacao('1', "Pesquisar outro pedido pelo id(0 - Voltar, 1 - Continuar): ", RED "\nERRO! Digite uma op��o v�lida\n" RESET);
            }
            else
            {
                printf(RED "CLIENTE N�O ECONTRADO!!!" RESET);
                escolhaPedido = verificacao('0', "\n0 - Voltar: ", RED "\nERRO! Digite uma op��o v�lida\n" RESET);
                system("cls");
            }
        }
        while(escolhaPedido != '0');

        fclose(pFile);
    }
    while (1);

    system("cls");
}
