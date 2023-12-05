#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"

void telaEstoqueIngredientes()
{
    int escolha;

    do
    {
        printf(YELLOW "\n\t-----------------------------------------\n\t|\t\t\t\t\t|");
        printf("\n\t|\t   *-------------------*\t|"  );
        printf("\n\t|\t   |    INGREDIENTES   |    \t|\n");
        printf("\t|");
        printf("\t   *-------------------*\t|\n\t|\t\t\t\t\t|" RESET);

        printf(YELLOW "\n\t|" RESET RED "\t1 - " RESET "Adicionar Ingredientes"  YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t2 - " RESET "Listar Ingredientes" YELLOW "\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t3 - " RESET "Total de Ingredientes" YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t4 - " RESET "Pesquisar Ingredientes" YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t5 - " RESET "Atualizar Ingredientes" YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t6 - " RESET "Ativar/Desativar" YELLOW "\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t0 - " RESET "Sair" YELLOW "\t\t\t|\n");
        printf(YELLOW "\t| \t\t\t\t\t|");
        printf("\n\t-----------------------------------------\n" RESET);

        escolha = verificacao('6', GREEN "\n\n\tDigite sua escolha: " RESET, RED "\n\tOp��o inv�lida !!!\n" RESET);

        switch (escolha)
        {
        case '1':
            system("cls");
            char resposta;

            do
            {
                adicionarIngrediente();
                printf("Deseja adicionar mais algum ingrediente(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
                system("cls");
            }
            while(resposta != 'N');

            break;
        case '2':
            system("cls");
            int escolha;
            do
            {
                system("cls");
                listarIngrediente();
                printf("Deseja listar novamente(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
                system("cls");
            }while(resposta != 'N');

            break;
        case '3':
            system("cls");
            qtdIngredientes();
            break;
        case '4':
            system("cls");
            pesquisarIngrediente();
            break;
        case '5':
            system("cls");
            atualizarIngrediente();
            break;
        case '6':
            system("cls");
            DesativarAtivarIngrediente();
            break;
        default:
            system("cls");
            break;
        }
    }
    while (escolha != '0');

    system("cls");
}
