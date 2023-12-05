#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "cores.h"

void telaVendas()
{
    int escolha;

    do
    {
        printf(YELLOW "\n\t-----------------------------------------\n\t|\t\t\t\t\t|");
        printf("\n\t|\t   *------------*\t\t|"  );
        printf("\n\t|\t   |   Vendas   |    \t\t|\n");
        printf("\t|");
        printf("\t   *------------*\t\t|\n\t|\t\t\t\t\t|" RESET);

        printf(YELLOW "\n\t|" RESET RED "\t1 - " RESET "Novo Pedido\t\t "  YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t2 - " RESET "Listar Pedidos" YELLOW "\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t3 - " RESET "Pesquisar Pedido" YELLOW "\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t0 - " RESET "Sair" YELLOW "\t\t\t|\n");
        printf(YELLOW "\t| \t\t\t\t\t|");
        printf("\n\t-----------------------------------------\n" RESET);

        escolha = verificacao('3', GREEN "\n\n\tDigite sua escolha: " RESET, RED "\n\tOp��o inv�lida !!!\n" RESET);

        switch(escolha)
        {
        case '1':
            system("cls");
            novoPedido();
            break;
        case '2':
            system("cls");
            listarVendas();
            break;
        case '3':
            system("cls");
            pesquisarPedido();
            break;
        default:
            system("cls");
        }
    }
    while(escolha != '0');

    system("cls");
}

