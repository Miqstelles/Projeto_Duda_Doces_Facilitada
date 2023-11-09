#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void atualizarProdutoCardapio()
{
    listarCardapio(); // Chama a função listarCardapio para mostrar os produtos no cardápio.

    cardapio cardap; // Declara uma estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".
    FILE *pFile1; // Declara um ponteiro de arquivo para "temp.txt".
    pFile = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura.
    pFile1 = fopen("temp.txt", "w"); // Abre o arquivo "temp.txt" para escrita.

    int codigo, encontrou = 0;
    printf("Insira o código do produto a ser atualizado: ");
    scanf("%i", &codigo); // Lê o código do produto a ser atualizado.

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)  // Verifica se o código do produto corresponde ao código fornecido.
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
                scanf("%[^\n]s", cardap.nome); // Lê o novo nome do produto.
            }

            printf("Deseja atualizar o tipo do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while(escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
            {
                printf("ERRO! Escolha inválida!\nDeseja atualizar o tipo do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
                scanf("%i", &cardap.tipo); // Lê o novo tipo do produto.
            }

            printf("Deseja atualizar o valor do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while(escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
            {
                printf("ERRO! Escolha inválida!\nDeseja atualizar o valor do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo preço do produto: ");
                scanf("%f", &cardap.preco); // Lê o novo preço do produto.
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
                        listarIngrediente(); // Chama a função listarIngrediente para mostrar os ingredientes disponíveis.

                        printf("Insira o código do ingrediente a ser adicionado: ");
                        scanf("%i", &codigoIngrediente);

                        int ingredienteRepetido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                printf("Este ingrediente já foi adicionado ao produto.\n");
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
                    else printf("Lista de ingredientes cheia. Não é possível adicionar mais ingredientes.\n");

                }
                else if (escolha == 'D')
                {
                    if (cardap.qtdIngredientes > 0)
                    {
                        int codigoIngrediente;
                        listarCardapio(); // Chama a função listarCardapio para mostrar os ingredientes no produto.

                        printf("Insira o código do ingrediente a ser deletado: ");
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

                        if (!ingredienteValido) printf("Código de ingrediente inválido ou não encontrado no produto.\n");
                    }
                    else printf("O produto não possui ingredientes para deletar.\n");
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
        remove("temp.txt"); // Remove o arquivo temporário.
    }
    else printf("Produto não encontrado!\n"); // Exibe uma mensagem se o produto não for encontrado.
}

