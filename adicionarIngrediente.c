#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"

void adicionarIngrediente()
{
    FILE *pFile;       // Declara um ponteiro para o arquivo chamado pFile.
    ingredientes *ing; // Declara um ponteiro para a estrutura chamada ingredientes.

    ing = (ingredientes *)calloc(1, sizeof(ingredientes)); // Aloca memoria para a estrutura ingredientes.

    pFile = fopen("estoque_ingredientes.txt", "a"); // Abre o arquivo "estoque_ingredientes.txt" em modo de apéndice(append).

    ing[0].codigo = obterProximoCodigo(); // Atribui o proximo código disponivel ao campo "codigo" da estrutura ingredientes.

    fflush(stdin); // Limpa o buffer de entrada padrão (stdin).

    printf("Insira o nome do ingrediente: ");
    scanf("%79[^\n]s", ing[0].nome);
    strcat(ing[0].nome, GREEN " (ATIVADO)" RESET);

    ing[0].quantidade = verificacaoCodigo("\nInsira a quantidade em estoque: ", RED "\nERRO INSIRA UMA QUANTIDADE VALIDA" RESET);

    fwrite(&ing[0], sizeof(ingredientes), 1, pFile); // Escreve os dados da estrutura ingredientes no arquivo.

    fclose(pFile); // fecha o arquivo "estoque_ingredientes.txt".
}
