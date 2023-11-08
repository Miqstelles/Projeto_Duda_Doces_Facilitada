#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void telaEstoqueIngredientes()
{
    int escolha;

    do
    {
        printf("\nESTOQUE DE INGREDIENTES");
        printf("\n1 - Adicionar Ingredientes");
        printf("\n2 - Listar Ingredientes");
        printf("\n3 - Total de Ingredientes");
        printf("\n4 - Pesquisar Ingrediente");
        printf("\n5 - Atualizar Ingrediente");
        printf("\n6 - Deletar Ingrediente");
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

        switch (escolha)
        {
        case 1:
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
        case 2:
            system("cls");
            listarIngrediente();
            break;
        case 3:
            system("cls");
            qtdIngredientes();
            break;
        case 4:
            system("cls");
            pesquisarIngrediente();
            break;
        case 5:
            system("cls");
            atualizarIngrediente();
            break;
        case 6:
            system("cls");
            deletarIngrediente();
            break;
        default:
            system("cls");
        }
    }
    while (escolha != 0);

    system("cls");
}
