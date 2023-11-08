#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"

void atualizarProdutoCardapio()
{
    listarCardapio();

    cardapio cardap;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("cardapio.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do produto a ser atualizado: ");
    scanf("%i", &codigo);

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            encontrou = 1;

            char escolhaAtualizar;

            printf("Deseja atualizar o nome do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            if (escolhaAtualizar == 'S')
            {
                fflush(stdin);
                printf("Insira o novo nome do produto: ");
                scanf("%[^\n]s", cardap.nome);
            }

            printf("Deseja atualizar o tipo do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while(escolhaAtualizar != 'S' && escolhaAtualizar != 'N') {
                printf("ERRO! Escolha invalida!\nDeseja atualizar o tipo do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
                scanf("%i", &cardap.tipo);
            }

            printf("Deseja atualiza o valor do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while(escolhaAtualizar != 'S' && escolhaAtualizar != 'N') {
                printf("ERRO! Escolha invalida!\nDeseja atualizar o valor do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo preço do produto: ");
                scanf("%f", &cardap.preco);
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
                        listarIngrediente();

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
                    else
                    {
                        printf("Lista de ingredientes cheia. Não é possível adicionar mais ingredientes.\n");
                    }
                }
                else if (escolha == 'D')
                {
                    if (cardap.qtdIngredientes > 0)
                    {
                        int codigoIngrediente;
                        listarCardapio();

                        printf("Insira o código do ingrediente a ser deletado: ");
                        scanf("%i", &codigoIngrediente);

                        int ingredienteValido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                for (int k = j; k < cardap.qtdIngredientes - 1; k++)
                                {
                                    cardap.listaIngredientes[k] = cardap.listaIngredientes[k + 1];
                                }
                                cardap.qtdIngredientes--;
                                ingredienteValido = 1;
                                printf("Ingrediente removido do produto.\n");
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
        fwrite(&cardap, sizeof(cardapio), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("cardapio.txt", "w");

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) fwrite(&cardap, sizeof(cardapio), 1, pFile);

        fclose(pFile);
        fclose(pFile1);
        remove("temp.txt");
    }
    else printf("Produto não encontrado!\n");
}
