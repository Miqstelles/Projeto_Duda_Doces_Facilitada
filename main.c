#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include "cores.h"
#define MAX_LEN 128

void barraDeLoading()
{
    system("color 0A");

    char a = 177, b = 219;

    printf("\n\n\n\n");
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t Carregando...\n\n");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++)
        printf("%c", a);

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
    // barraDeLoading();

    setlocale(LC_ALL, "Portuguese");
    system("chcp 1252 > nul");

    int escolha;

    do
    {   printf(YELLOW "\n\t-----------------------------------------\n\t|\t\t\t\t\t|");
        printf("\n\t|\t   *-----------*\t\t|"  );
        printf("\n\t|\t   | Bem Vindo | \t\t|\n");
        printf("\t|");
        printf("\t   *-----------*\t\t|\n\t|\t\t\t\t\t|" RESET);

        printf(YELLOW "\n\t|" RESET RED "\t1 - " RESET "Vendas\t\t "  YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t2 - " RESET "Cardapio" YELLOW "\t\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t3 - " RESET "Estoque de Ingredientes" YELLOW "\t|");
        printf(YELLOW "\n\t|" RESET RED "\t4 - " RESET "Clientes" YELLOW "\t\t\t|");
        printf(YELLOW "\n\t|" RESET RED "\t0 - " RESET "Sair" YELLOW "\t\t\t|\n");
        printf(YELLOW "\t| \t\t\t\t\t|");
        printf("\n\t-----------------------------------------\n" RESET);

        escolha = verificacao('4', GREEN "\n\n\tDigite sua escolha: " RESET, RED "\n\tOpção inválida !!!\n" RESET);

        switch (escolha)
        {
        case '1':
            system("cls");
            telaVendas();
            break;
        case '2':
            system("cls");
            telaCardapio();
            break;
        case '3':
            system("cls");
            telaEstoqueIngredientes();
            break;
        case '4':
            system("cls");
            telaClientes();
            break;
        default:
            system("cls");
            break;
        }
    } while (escolha != '0');

    FILE * pFile;
    pFile = fopen("bolo.txt", "r");
    char read_string[MAX_LEN];

    while(fgets(read_string,sizeof(read_string), pFile) != NULL) printf("%s",read_string);

    return 0;
}
