#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void telaCardapio()
{
    int escolha;

    do
    {
        printf(YELLOW "\n\t-------------------------------------------\n\t|\t\t\t\t\t  |");
        printf("\n\t|\t   *------------*\t\t  |"  );
        printf("\n\t|\t   |  CARDAPIO  |    \t\t  |\n");
        printf("\t|");
        printf("\t   *------------*\t\t  |\n\t|\t\t\t\t\t  |" RESET);

        printf(YELLOW "\n\t|" RESET RED "\t1 - " RESET "Adicionar Produto no Cardápio"  YELLOW " |");
        printf(YELLOW "\n\t|" RESET RED "\t2 - " RESET "Listar Cardapio" YELLOW "\t\t  |");
        printf(YELLOW "\n\t|" RESET RED "\t3 - " RESET "Pesquisar Produto" YELLOW "\t\t  |");
        printf(YELLOW "\n\t|" RESET RED "\t4 - " RESET "Atualizar Produto" YELLOW "\t\t  |");
        printf(YELLOW "\n\t|" RESET RED "\t5 - " RESET "Ativar/Desativar" YELLOW "\t\t  |");
        printf(YELLOW "\n\t|" RESET RED "\t0 - " RESET "Sair" YELLOW "\t\t\t  |\n");
        printf(YELLOW "\t| \t\t\t\t\t  |");
        printf("\n\t-------------------------------------------\n" RESET);

        escolha = verificacao('5', GREEN "\n\n\tDigite sua escolha: " RESET, RED "\n\tOpção inválida !!!\n" RESET);

        switch (escolha)
        {
        case '1':
            system("cls");
            char resposta;

            do
            {
                adicionarProdutoCardapio();
                printf("Deseja adicionar mais algum produto(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            system("cls");
            break;
        case '2':
            system("cls");

            do
            {
                system("cls");
                listarCardapio();
                printf("Deseja listar novamente(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            system("cls");
            break;
        case '3':
            system("cls");
            pesquisarProdutoCardapio();
            break;
        case '4':
            system("cls");
            atualizarProdutoCardapio();
            break;
        case '5':
            system("cls");
            AtivarDesativarProdutoCardapio();
            break;
        default:
            system("cls");
        }
    }
    while (escolha != '0');

    system("cls");
}
