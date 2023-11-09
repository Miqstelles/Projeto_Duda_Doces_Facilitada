#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void atualizarProdutoCardapio()
{
    listarCardapio(); // Chama a fun��o listarCardapio para mostrar os produtos no card�pio.

    cardapio cardap; // Declara uma estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "temp.txt".
    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.
    pFile1 = fopen("temp.txt", "w"); // Abre o arquivo "temp.txt" para escrita.

    int codigo, encontrou = 0;
    printf("Insira o c�digo do produto a ser atualizado: ");
    scanf("%i", &codigo); // L� o c�digo do produto a ser atualizado.

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)  // Verifica se o c�digo do produto corresponde ao c�digo fornecido.
        {
            encontrou = 1; // Define a flag para indicar que o produto foi encontrado.

            char escolhaAtualizar;

            printf("Deseja atualizar o nome do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            if (escolhaAtualizar == 'S')
            {
                fflush(stdin);
                printf("Insira o novo nome do produto: ");
                scanf("%[^\n]s", cardap.nome); // L� o novo nome do produto.
            }

            printf("Deseja atualizar o tipo do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while(escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
            {
                printf("ERRO! Escolha inv�lida!\nDeseja atualizar o tipo do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
                scanf("%i", &cardap.tipo); // L� o novo tipo do produto.
            }

            printf("Deseja atualizar o valor do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while(escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
            {
                printf("ERRO! Escolha inv�lida!\nDeseja atualizar o valor do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo pre�o do produto: ");
                scanf("%f", &cardap.preco); // L� o novo pre�o do produto.
            }

            char escolha;
            printf("Deseja adicionar (A) ou deletar (D) ingredientes? (0 para finalizar): ");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);

            while (escolha == 'A' || escolha == 'D')
            {
                if (escolha == 'A')
                {
                    if (cardap.qtdIngredientes < 30)
                    {
                        int codigoIngrediente;
                        listarIngrediente(); // Chama a fun��o listarIngrediente para mostrar os ingredientes dispon�veis.

                        printf("Insira o c�digo do ingrediente a ser adicionado: ");
                        scanf("%i", &codigoIngrediente);

                        int ingredienteRepetido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                printf("Este ingrediente j� foi adicionado ao produto.\n");
                                ingredienteRepetido = 1;
                                break;
                            }
                        }

                        if (!ingredienteRepetido)
                        {
                            cardap.listaIngredientes[cardap.qtdIngredientes] = codigoIngrediente;
                            cardap.qtdIngredientes++;
                        }
                    }
                    else printf("Lista de ingredientes cheia. N�o � poss�vel adicionar mais ingredientes.\n");

                }
                else if (escolha == 'D')
                {
                    if (cardap.qtdIngredientes > 0)
                    {
                        int codigoIngrediente;
                        listarCardapio(); // Chama a fun��o listarCardapio para mostrar os ingredientes no produto.

                        printf("Insira o c�digo do ingrediente a ser deletado: ");
                        scanf("%i", &codigoIngrediente);

                        int ingredienteValido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                for (int k = j; k < cardap.qtdIngredientes - 1; k++) cardap.listaIngredientes[k] = cardap.listaIngredientes[k + 1];

                                cardap.qtdIngredientes--; // Decrementa a quantidade de ingredientes do produto.
                                ingredienteValido = 1; // Define a flag para indicar que o ingrediente foi removido com sucesso.
                                printf("Ingrediente removido do produto.\n"); // Exibe uma mensagem informando que o ingrediente foi removido.
                                break;
                            }
                        }

                        if (!ingredienteValido) printf("C�digo de ingrediente inv�lido ou n�o encontrado no produto.\n");
                    }
                    else printf("O produto n�o possui ingredientes para deletar.\n");
                }

                printf("Deseja continuar a adicionar (A) ou deletar (D) ingredientes? (A/D/0 para finalizar): ");
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
            }
        }
        fwrite(&cardap, sizeof(cardapio), 1, pFile1); // Escreve os dados atualizados do produto no arquivo "temp.txt".
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");  // Abre o arquivo "temp.txt" para leitura.
        pFile = fopen("cardapio.txt", "w"); // Abre o arquivo "cardapio.txt" para escrita.

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) fwrite(&cardap, sizeof(cardapio), 1, pFile);

        fclose(pFile);
        fclose(pFile1);
        remove("temp.txt"); // Remove o arquivo tempor�rio.
    }
    else printf("Produto n�o encontrado!\n"); // Exibe uma mensagem se o produto n�o for encontrado.
}

