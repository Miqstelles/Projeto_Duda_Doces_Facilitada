#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "windows.h"
#include "cores.h"

void adicionarProdutoCardapio()
{
    system("cls");
    char buffer[100];
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

    cardap[0].tipo = verificacaoCodigo("\nInsira o tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ", RED "\nERRO INSIRA UM TIPO V�LIDO" RESET); // L� o tipo do produto.

    while(cardap[0].tipo > 3) cardap[0].tipo = verificacaoCodigo("\nInsira o tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ", RED "\nERRO INSIRA UM TIPO V�LIDO" RESET); // L� o tipo do produto.

    fflush(stdin);
    printf("Insira o nome do produto: ");
    scanf("%79[^\n]s", cardap[0].nome); // L� o nome do produto.
    strcat(cardap[0].nome, GREEN " (ATIVADO)" RESET);

    listarIngredienteCardapio(); // Chama a fun��o listarIngrediente para mostrar os ingredientes dispon�veis.
    listarIngredienteCardapio(); // Chama a fun��o listarIngrediente para mostrar os ingredientes dispon�veis.

    while (1)
    {
        int codigoIngrediente;

        codigoIngrediente = verificacaoCodigo("\nInsira o c�digo do ingrediente a ser adicionado (0 para finalizar): ", "\nERRO INSIRA UM CODIGO V�LIDO"); // L� o tipo do produto.

        if (codigoIngrediente == 0) break; // Finaliza a adi��o de ingredientes quando o c�digo � 0.

        int ingredienteExiste = 0;

        rewind(pFile1);  // Volta ao in�cio do arquivo de ingredientes.

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
        {
            if (ing1.codigo == codigoIngrediente && strstr(ing1.nome, "(DESATIVADO)") == NULL)
            {
                // Verifica se o c�digo do ingrediente corresponde ao c�digo fornecido e se n�o est� desativado.
                ingredienteExiste = 1; // Define a flag para indicar que o ingrediente foi encontrado.
                cardap[0].listaIngredientes[cardap[0].qtdIngredientes] = codigoIngrediente; // Adiciona o c�digo do ingrediente � lista de ingredientes do produto.
                cardap[0].qtdIngredientes++; // Incrementa a quantidade de ingredientes no produto.
                printf("Ingrediente adicionado ao produto.\n");
                break; // Sai do loop, uma vez que o ingrediente foi encontrado e adicionado.
            }
        }

        if (!ingredienteExiste) printf(RED "C�digo de ingrediente inexistente ou desativado. Tente novamente.\n" RESET);
    }

    printf("Insira o valor do produto: ");

    while (1)
    {
        // L� a entrada como uma string
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            // Verifica se a string cont�m apenas d�gitos e ponto decimal
            char* endptr;
            cardap[0].preco = strtod(buffer, &endptr);

            if (endptr == buffer || *endptr != '\n')
            {
                // A convers�o falhou ou h� caracteres n�o convertidos
                printf("Entrada inv�lida. Por favor, insira um valor v�lido: ");
            }
            else
            {
                break;  // Se a leitura for bem-sucedida, saia do loop
            }
        }
        else
        {
            // Limpa o buffer de entrada em caso de erro
            while (getchar() != '\n');
            printf("Erro na leitura. Por favor, insira um valor v�lido: ");
        }
    }

    fwrite(&cardap[0], sizeof(cardapio), 1, pFile);  // Escreve os dados do produto no arquivo.

    free(cardap);  // Libera a mem�ria alocada para a estrutura cardapio.
    fclose(pFile);  // Fecha o arquivo "cardapio.txt".
    fclose(pFile1); // Fecha o arquivo "estoque_ingredientes.txt".
}
