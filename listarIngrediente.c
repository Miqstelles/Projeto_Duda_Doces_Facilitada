#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"

void listarIngrediente(){
    int escolha;

    do{
        system("cls");
        ingredientes ing1; // Declara a estrutura chamada ingredientes.
        FILE *pFile; // Declara um ponteiro de arquivo.
        pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.

        printf("\n=========================================================");
        printf("\nEstoque\n");
        printf("\nC�digo \t Nome \t\t   Quantidade");

        while (fread(&ing1, sizeof(ingredientes), 1, pFile)) // L� um registro de ingredientes do arquivo.
        {
            printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade); // Exibe o c�digo, nome e quantidade do ingrediente em um formato de tabela.
        }

        printf("\n=========================================================\n"); // Exibe uma linha de separa��o ap�s listar os ingredientes.

        fclose(pFile); // Fecha o arquivo ap�s a leitura.

        printf("\n0 - Sair: ");
        scanf("%d", &escolha);
        fclose(pFile); // Fecha o arquivo ap�s a leitura.
    }
    while(escolha !=0);

    printf("\n=========================================================\n"); // Exibe uma linha de separa��o ap�s listar os ingredientes.

}

