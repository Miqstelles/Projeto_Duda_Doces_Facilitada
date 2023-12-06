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

        escolha = verificacao('6', GREEN "\n\n\tDigite sua escolha: " RESET, RED "\n\tOpção inválida !!!\n" RESET);

        switch (escolha)
        {
        case '1':
            system("cls");
            int resposta;

            do
            {
                adicionarIngrediente();
                resposta = verificacaoCodigo("Deseja adicionar um ingrediente novamente?(1 - Sim, 0 - Não): ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
                while(resposta < 0 || resposta > 1) {
                    printf(RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
                    resposta = verificacaoCodigo("Deseja adicionar um ingrediente novamente?(1 - Sim, 0 - Não): ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
                }
                system("cls");
            }
            while(resposta != 0);

            break;
        case '2':
            system("cls");
            do
            {
                system("cls");
                listarIngrediente();
                resposta = verificacao('1', "Deseja listar novamente?(1 - Sim, 0 - Não): ", RED "ERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);

                system("cls");
            }while(resposta != '0');

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
