#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void atualizarProdutoCardapio()
{
    listarCardapioPedido(); // Chama a fun��o listarCardapio para mostrar os produtos no card�pio.

    cardapio cardap; // Declara uma estrutura chamada cardapio.
    FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".

    pFile = fopen("cardapio.txt", "r+"); // Abre o arquivo "cardapio.txt" para leitura e escrita.

    int codigo, encontrou = 0;
    codigo = verificacaoCodigo("Insira o c�digo do produto a ser atualizado: ", "ERRO Insira um c�digo v�lido");

    char buffer[200];

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
                strcat(cardap.nome,  GREEN " (ATIVADO)" RESET);
            }

            printf("Deseja atualizar o tipo do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while (escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
            {
                printf("ERRO! Escolha inv�lida!\nDeseja atualizar o tipo do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
                scanf("%i", &cardap.tipo);
            }

            printf("Deseja atualizar o valor do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            while (escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
            {
                printf("ERRO! Escolha inv�lida!\nDeseja atualizar o valor do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);
            }

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo pre�o do produto: ");
                while (1)
                {
                    // L� a entrada como uma string
                    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
                    {
                        // Verifica se a string cont�m apenas d�gitos e ponto decimal
                        char *endptr;
                        cardap.preco = strtod(buffer, &endptr);

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
                        while (getchar() != '\n')
                            ;
                        printf("Erro na leitura. Por favor, insira um valor v�lido: ");
                    }
                }
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
                        listarIngredienteCardapio(); // Chama a fun��o listarIngrediente para mostrar os ingredientes dispon�veis.

                        codigoIngrediente = verificacaoCodigo("Insira o c�digo do ingrediente a ser adicionado: ", RED "ERRO INSIRA UM C�DIGO DE INGREDIENTE V�LIDO" RESET);

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
                    else
                        printf("Lista de ingredientes cheia. N�o � poss�vel adicionar mais ingredientes.\n");
                }
                else if (escolha == 'D')
                {
                    system("cls");
                    if (cardap.qtdIngredientes > 0)
                    {
                        int codigoIngrediente;
                        cardapio produto = getProdutoPorCodigo(codigo); // Chama a fun��o listarCardapio para mostrar os ingredientes no produto.

                        printf("\nC�digo: %i\n", produto.codigo);
                        printf("Nome: %s\n", produto.nome);
                        printf("Tipo: %s\n", produto.tipo == 1 ? "Bolo" : produto.tipo == 2 ? "Doce" : "Sobremesa");
                        printf("\nQuantidade de Ingredientes: %i\n", produto.qtdIngredientes);

                        printf("Ingredientes:\n");

                        for (int i = 0; i < produto.qtdIngredientes; i++)
                        {
                            int codigoIngrediente = produto.listaIngredientes[i];
                            char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
                            printf("  Nome: (%i)%s\n", produto.listaIngredientes[i], nomeIngrediente);
                        }

                        printf("\nPre�o: %.2f\n", produto.preco);

                        printf("------------------------------------------\n------------------------------------------");
                        printf("\n\n");

                        codigoIngrediente = verificacaoCodigo("Insira o c�digo do ingrediente a ser deletado: ", RED "ERRO INSIRA UM C�DIGO DE INGREDIENTE V�LIDO");

                        int ingredienteValido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                for (int k = j; k < cardap.qtdIngredientes - 1; k++)
                                    cardap.listaIngredientes[k] = cardap.listaIngredientes[k + 1];

                                cardap.qtdIngredientes--; // Decrementa a quantidade de ingredientes do produto.
                                ingredienteValido = 1;    // Define a flag para indicar que o ingrediente foi removido com sucesso.
                                printf("Ingrediente removido do produto.\n"); // Exibe uma mensagem informando que o ingrediente foi removido.
                                break;
                            }
                        }

                        if (!ingredienteValido)
                            printf("C�digo de ingrediente inv�lido ou n�o encontrado no produto.\n");
                    }
                    else
                        printf("O produto n�o possui ingredientes para deletar.\n");
                }

                printf("Deseja continuar a adicionar (A) ou deletar (D) ingredientes? (A/D/0 para finalizar): ");
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
            }
            system("cls");

            fseek(pFile, -sizeof(cardapio), SEEK_CUR); // Volta para a posi��o do �ltimo registro lido.
            fwrite(&cardap, sizeof(cardapio), 1, pFile);   // Escreve os dados atualizados no arquivo.
            break;
        }
    }

    fclose(pFile); // fecha o arquivo "cardapio.txt".

    if (!encontrou)
    {
        printf("Produto n�o encontrado!\n"); // Exibe uma mensagem se o produto n�o for encontrado.
    }
}
