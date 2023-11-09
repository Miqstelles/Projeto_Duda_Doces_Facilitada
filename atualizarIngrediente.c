#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void atualizarIngrediente(){
    listarIngrediente(); // Chama a função listarIngrediente para mostrar a lista de ingredientes.

    ingredientes ing1; // Declara uma estrutura chamada ingredientes.
    FILE *pFile; // Declara um ponteiro de arquivo para "estoque_ingredientes.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "temp.txt".

    pFile = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.
    pFile1 = fopen("temp.txt", "w"); // Abre o arquivo "temp.txt" para escrita.

    int codigo, encontrou = 0;
    printf("Insira o código do ingrediente a ser atualizado: ");
    scanf("%i", &codigo); // Lê o código do ingrediente a ser atualizado.

    while (fread(&ing1, sizeof(ingredientes), 1, pFile)){
        if (ing1.codigo == codigo){ // Verifica se o código do ingrediente corresponde ao código fornecido.
            encontrou = 1;
            fflush(stdin);
            printf("Insira o novo nome do ingrediente: ");
            scanf("%[^\n]s", ing1.nome);

            printf("Insira a nova quantidade em estoque: ");
            scanf("%i", &ing1.quantidade);

            printf("\nIngrediente %s atualizado com sucesso!\n", ing1.nome);
        }
        fwrite(&ing1, sizeof(ingredientes), 1, pFile1); // Escreve os dados do ingrediente atualizado no arquivo "temp.txt".
    }

    fclose(pFile);  // fecha o arquivo "estoque_ingredientes.txt".
    fclose(pFile1);  // fecha o arquivo "temp.txt".

    if (encontrou){
        pFile1 = fopen("temp.txt", "r"); // Abre o arquivo "temp.txt" para leitura.
        pFile = fopen("estoque_ingredientes.txt", "w"); // Abre o arquivo "estoque_ingredientes.txt" para escrita.

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1)){
            fwrite(&ing1, sizeof(ingredientes), 1, pFile); // Copia os dados atualizados para o arquivo "estoque_ingredientes.txt".
        }

        fclose(pFile); // fecha o arquivo "temp.txt".
        fclose(pFile1); // fecha o arquivo "estoque_ingredientes.txt".
    }
    else printf("Ingrediente não encontrado!\n"); // Exibe uma mensagem se o ingrediente não for encontrado.
}
