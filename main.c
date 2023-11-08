#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

// TELA VENDAS //

void barraDeLoading()
{
    system("color 0A");

    char a = 177, b = 219;

    printf("\n\n\n\n");
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t Carregando...\n\n");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++) printf("%c", a);

    printf("\r");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++)
    {
        printf("%c", b);
        Sleep(100);
    }

    system("color 7");
    system("cls");
}

int main()
{
    barraDeLoading();

    setlocale(LC_ALL, "Portuguese");
    system("chcp 1252 > nul");

    int escolha;

    do
    {
        printf("\nBem Vindo\n");
        printf("\n1 - Vendas");
        printf("\n2 - Cardapio");
        printf("\n3 - Estoque de Ingredientes");
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
            telaVendas();
            break;
        case 2:
            system("cls");
            telaCardapio();
            break;
        case 3:
            system("cls");
            telaEstoqueIngredientes();
            break;
        default:
            system("cls");
        }
    }
    while (escolha != 0);

    printf("\nVolte sempre!\n");

    return 0;
}
