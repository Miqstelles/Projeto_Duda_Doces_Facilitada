#include <stdio.h>
#include <stdlib.h>
#include "cores.h"

void telaClientes()
{
    int escolha;

    do
    {
        printf(YELLOW "\n\t-----------------------------------------\n\t|\t\t\t\t\t|");
        printf("\n\t|\t   *------------*\t\t|"  );
        printf("\n\t|\t   |  Clientes  |    \t\t|\n");
        printf("\t|");
        printf("\t   *------------*\t\t|\n\t|\t\t\t\t\t|" RESET);

        printf(YELLOW "\n\t|" RESET RED "\t1 - " RESET "Cadastrar Cliente\t\t"  YELLOW "|");
        printf(YELLOW "\n\t|" RESET RED "\t2 - " RESET "Listar Clientes" YELLOW "\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t3 - " RESET "Pesquisar Cliente" YELLOW "\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t0 - " RESET "Sair" YELLOW "\t\t\t|\n");
        printf(YELLOW "\t| \t\t\t\t\t|");
        printf("\n\t-----------------------------------------\n" RESET);

        escolha = verificacao('3', GREEN "\n\n\tDigite sua escolha: " RESET, RED "\n\tOpção inválida !!!\n" RESET);

        switch(escolha)
        {
        case '1':
            system("cls");
            char resposta;

            do
            {
                cadastrarCliente();
                printf("Deseja cadastrar mais algum cliente(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            break;
        case '2':
            system("cls");
            listarClientes();
            break;
        case '3':
            system("cls");
            pesquisarCliente();
            break;
        default:
            system("cls");
        }
    }
    while(escolha != '0');

    system("cls");
}
