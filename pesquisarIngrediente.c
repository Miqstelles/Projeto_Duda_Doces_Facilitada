#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"
#define MAX_LEN 128

void pesquisarIngrediente()
{
    do
    {
        ingredientes ing1; // Declara a estrutura chamada ingredientes.
        FILE *pFile; // Declara um ponteiro de arquivo.

        pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo de estoque de ingredientes para leitura.

        int escolha, codigo, encontrou = 0;
        char nome[MAX_LEN];

        escolha = verificacaoCodigo("\nDeseja pesquisar o ingrediente pelo nome ou codigo? (1 - Nome, 2 - Codigo, 0 - Sair): ", RED "\nERRO INSIRA UMA OP��O V�LIDA" RESET);

        if(escolha == 0)
        {
            system("cls");
            break;
        }

        while(escolha < 0 || escolha > 2)
        {
            printf(RED "\nERRO INSIRA UMA OP��O V�LIDA" RESET);
            escolha = verificacaoCodigo("\nDeseja pesquisar o ingrediente pelo nome ou codigo? (1 - Nome, 2 - Codigo, 0 - Sair): ", RED "\nERRO INSIRA UMA OP��O V�LIDA" RESET);
        }

        system("cls");

        if (escolha == 1)
        {
            printf("\nInsira o nome do ingrediente: ");
            fflush(stdin);
            scanf("%79[^\n]s", nome);

            while(!verificacaoNome(nome, RED "\nERRO INSIRA UM NOME V�LIDO" RESET))
            {
                fflush(stdin); // Limpa o buffer de entrada padr�o (stdin).

                printf("\nInsira o nome do ingrediente: ");
                scanf("%79[^\n]s", nome); // L� o nome do ingrediente.
            }
        }
        else if(escolha == 2) codigo = verificacaoCodigo("\nInsira o c�digo do ingrediente: ", RED "\nERRO INSIRA UM C�DIGO V�LIDO" RESET);

        while (fread(&ing1, sizeof(ingredientes), 1, pFile))
        {
            if (escolha == 1 || escolha == 2)
            {
                strtok(ing1.nome, GREEN "(ATIVADO)");
                strtok(NULL, RED "(DESATIVADO)"); // Use NULL para continuar a partir da �ltima posi��o

                if (strcasecmp(nome, ing1.nome) == 0 || ing1.codigo == codigo)
                {
                    printf("\n=========================================================");
                    printf("\nEstoque\n");
                    printf(GREEN "\nC�digo " RESET RED "\t Nome " RESET YELLOW "\t\t\t\t   Quantidade\n" RESET);
                    printf(GREEN"\n%-9i" RESET "%-40s %10i", ing1.codigo, ing1.nome, ing1.quantidade); // Exibe os detalhes do ingrediente encontrado.
                    printf("\n=========================================================\n");
                    encontrou = 1;
                }
            }
        }
        if (!encontrou) printf(RED "Ingrediente n�o encontrado!\n" RESET); // Exibe uma mensagem se o ingrediente n�o for encontrado.

        fclose(pFile); // Fecha o arquivo de estoque de ingredientes.
    }
    while(1);
}

