#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void telaCardapio()
{
    int escolha;

    do
    {
        printf("\nCARDAPIO");
        printf("\n1 - Adicionar Produto no Cardápio");
        printf("\n2 - Listar Cardapio");
        printf("\n3 - Pesquisar Produto");
        printf("\n4 - Atualizar Produto");
        printf("\n5 - Deletar Produto");
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
                adicionarProdutoCardapio();
                printf("Deseja adicionar mais algum produto(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            break;
        case 2:
            system("cls");
            listarCardapio();
            break;
        case 3:
            system("cls");
            pesquisarProdutoCardapio();
            break;
        case 4:
            system("cls");
            atualizarProdutoCardapio();
            break;
        case 5:
            system("cls");
            deletarProdutoCardapio();
            break;
        default:
            system("cls");
        }
    }
    while (escolha != 0);

    system("cls");
}
