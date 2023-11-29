#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void listarIngrediente(){
    int escolha;

    do{
        system("cls");
        ingredientes ing1; // Declara a estrutura chamada ingredientes.
        FILE *pFile; // Declara um ponteiro de arquivo.
        pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.

        printf("\n=========================================================");
        printf("\nEstoque\n");
        printf("\nCódigo \t Nome \t\t   Quantidade");

        while (fread(&ing1, sizeof(ingredientes), 1, pFile)) // Lê um registro de ingredientes do arquivo.
        {
            printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade); // Exibe o código, nome e quantidade do ingrediente em um formato de tabela.
        }

        printf("\n=========================================================\n"); // Exibe uma linha de separação após listar os ingredientes.

        fclose(pFile); // Fecha o arquivo após a leitura.

        printf("\n0 - Sair: ");
        scanf("%d", &escolha);
    }
    while(escolha !=0);

    system("cls");
}

