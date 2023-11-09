#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void adicionarProdutoCardapio()
{
    cardapio *cardap; // Declara um ponteiro para a estrutura chamada cardapio.
    ingredientes ing1; // Declara a estrutura chamada ingredientes.

    FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "estoque_ingredientes.txt".
    int codigo = 1;

    cardap = (cardapio *)calloc(1, sizeof(cardapio)); // Aloca mem�ria para a estrutura cardapio.
    pFile = fopen("cardapio.txt", "a"); // Abre o arquivo "cardapio.txt" em modo de ap�ndice.
    pFile1 = fopen("estoque_ingredientes.txt", "r"); // Abre o arquivo "estoque_ingredientes.txt" para leitura.

    cardap[0].qtdIngredientes = 0; // Inicializa o campo qtdIngredientes da estrutura cardapio.

    cardap[0].codigo = obterProximoCodigoCardapio();  // Obt�m o pr�ximo c�digo para o produto no card�pio.

    printf("Insira o tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
    scanf("%i", &cardap[0].tipo); // L� o tipo do produto.

    fflush(stdin);
    printf("Insira o nome do produto: ");
    scanf("%[^\n]s", cardap[0].nome); // L� o nome do produto.

    listarIngrediente(); // Chama a fun��o listarIngrediente para mostrar os ingredientes dispon�veis.

    while (1)
    {
        int codigoIngrediente;

        printf("Insira o c�digo do ingrediente a ser adicionado (0 para finalizar): ");
        scanf("%i", &codigoIngrediente);

        if (codigoIngrediente == 0) break; // Finaliza a adi��o de ingredientes quando o c�digo � 0.

        int ingredienteExiste = 0;

        rewind(pFile1);  // Volta ao in�cio do arquivo de ingredientes.

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1)){
            if (ing1.codigo == codigoIngrediente){ // Verifica se o c�digo do ingrediente corresponde ao c�digo fornecido.
                ingredienteExiste = 1; // Define a flag para indicar que o ingrediente foi encontrado.
                cardap[0].listaIngredientes[cardap[0].qtdIngredientes] = codigoIngrediente; // Adiciona o c�digo do ingrediente � lista de ingredientes do produto.
                cardap[0].qtdIngredientes++; // Incrementa a quantidade de ingredientes no produto.
                printf("Ingrediente adicionado ao produto.\n");
                break; // Sai do loop, uma vez que o ingrediente foi encontrado e adicionado.
            }
        }

        if (!ingredienteExiste) printf("C�digo de ingrediente inexistente. Tente novamente.\n");
    }

    printf("Insira o valor do produto: ");
    scanf("%f", &cardap[0].preco);

    fwrite(&cardap[0], sizeof(cardapio), 1, pFile);  // Escreve os dados do produto no arquivo.

    free(cardap);  // Libera a mem�ria alocada para a estrutura cardapio.
    fclose(pFile);  // Fecha o arquivo "cardapio.txt".
    fclose(pFile1); // Fecha o arquivo "estoque_ingredientes.txt".
}
