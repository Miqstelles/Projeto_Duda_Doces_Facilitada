#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"
#define MAX_LEN 128

void pesquisarIngrediente()
{
    ingredientes ing1; // Declara a estrutura chamada ingredientes.
    FILE *pFile; // Declara um ponteiro de arquivo.

    pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo de estoque de ingredientes para leitura.

    int escolha, codigo, encontrou;
    char nome[MAX_LEN];

    escolha = verificacaoCodigo("\nDeseja pesquisar o cliente pelo nome ou codigo? (1 - Nome, 2 - Codigo, 0 - Sair): ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);

    if (escolha == 1)
    {
        printf("\nInsira o nome do cliente: ");
        fflush(stdin);
        scanf("%79[^\n]s", nome);
    }
    else if(escolha == 2) codigo = verificacaoCodigo("\nInsira o código do cliente: ", RED "\nERRO INSIRA UM CÓDIGO VÁLIDO" RESET);

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (escolha == 1 || escolha == 2)
        {
            if (strcasecmp(nome, ing1.nome) == 0 || ing1.codigo == codigo)
            {
                printf("\n=========================================================");
                printf("\nEstoque\n");
                printf("\nCódigo \t Nome \t\t   Quantidade");
                printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade); // Exibe os detalhes do ingrediente encontrado.
                printf("\n=========================================================\n");
                encontrou = 1;
            }
        }
    }
    if (!encontrou) printf("Ingrediente não encontrado!\n"); // Exibe uma mensagem se o ingrediente não for encontrado.

    fclose(pFile); // Fecha o arquivo de estoque de ingredientes.
}

