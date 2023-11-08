#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"

void telaVendas()
{
    int escolha;

    do
    {
        printf("\nVENDAS");
        printf("\n1 - Novo Pedido");
        printf("\n2 - Listar Pedidos");
        printf("\n3 - Pesquisar Pedido");
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

        switch(escolha)
        {
        case 1:
            system("cls");
            char resposta;

            do
            {
                novoPedido();
                printf("Deseja adicionar mais algum pedido(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            break;
        case 2:
            system("cls");
            listarVendas();
            break;
        case 3:
            system("cls");
            pesquisarPedido();
            break;
        default:
            system("cls");
        }
    }
    while(escolha !=0);

    system("cls");
}

