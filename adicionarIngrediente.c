#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"

void adicionarIngrediente(){
    FILE *pFile; // Declara um ponteiro para o arquivo chamado pFile.
    ingredientes *ing; // Declara um ponteiro para a estrutura chamada ingredientes.

    ing = (ingredientes *)calloc(1, sizeof(ingredientes)); // Aloca memória para a estrutura ingredientes.

    pFile = fopen("estoque_ingredientes.txt", "a"); // Abre o arquivo "estoque_ingredientes.txt" em modo de apêndice(append).

    ing[0].codigo = obterProximoCodigo(); // Atribui o próximo código disponível ao campo "codigo" da estrutura ingredientes.

    fflush(stdin); // Limpa o buffer de entrada padrão (stdin).

    printf("Insira o nome do ingrediente: ");
    scanf("%[^\n]s", ing[0].nome);

    printf("Insira a quantidade em estoque: ");
    scanf("%i", &ing[0].quantidade);

    fwrite(&ing[0], sizeof(ingredientes), 1, pFile); // Escreve os dados da estrutura ingredientes no arquivo.

    fclose(pFile);  // fecha o arquivo "estoque_ingredientes.txt".
}

