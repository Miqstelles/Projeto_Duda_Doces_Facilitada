#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void atualizarProdutoCardapio()
{
    while(1)
    {
        system("cls");
        listarCardapioPedido(); // Chama a função listarCardapio para mostrar os produtos no cardápio.

        cardapio cardap; // Declara uma estrutura chamada cardapio.
        FILE *pFile; // Declara um ponteiro de arquivo para "cardapio.txt".

        pFile = fopen("cardapio.txt", "r+"); // Abre o arquivo "cardapio.txt" para leitura e escrita.

        int codigo, encontrou = 0;
        codigo = verificacaoCodigo("Insira o código do produto a ser atualizado: ", RED "\nERRO Insira um código válido\n" RESET);

        char buffer[200];

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

                    while(!verificacaoNome(cardap.nome, RED "\nERRO INSIRA UM NOME VÁLIDO" RESET))
                    {
                        fflush(stdin); // Limpa o buffer de entrada padrão (stdin).

                        printf("\nInsira o nome do produto: ");
                        scanf("%79[^\n]s", cardap.nome); // Lê o nome do ingrediente.
                    }

                    strcat(cardap.nome,  GREEN "(ATIVADO)" RESET);
                }

                printf("Deseja atualizar o tipo do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);

                while (escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
                {
                    printf("ERRO! Escolha inválida!\nDeseja atualizar o tipo do produto? (S/N): ");
                    scanf(" %c", &escolhaAtualizar);
                    escolhaAtualizar = toupper(escolhaAtualizar);
                }

                if (escolhaAtualizar == 'S')
                {
                    cardap.tipo = verificacaoCodigo("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ", RED "\nERRO INSIRA UM TIPO VÁLIDO\n" RESET);

                    while(cardap.tipo <= 0 || cardap.tipo > 3)
                    {
                        printf(RED "\nERRO INSIRA UM TIPO VÁLIDO\n" RESET);
                        cardap.tipo = verificacaoCodigo("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ", RED "\nERRO INSIRA UM TIPO VÁLIDO\n" RESET);
                    }
                }

                printf("Deseja atualizar o valor do produto? (S/N): ");
                scanf(" %c", &escolhaAtualizar);
                escolhaAtualizar = toupper(escolhaAtualizar);

                while (escolhaAtualizar != 'S' && escolhaAtualizar != 'N')
                {
                    printf("ERRO! Escolha inválida!\nDeseja atualizar o valor do produto? (S/N): ");
                    scanf(" %c", &escolhaAtualizar);
                    escolhaAtualizar = toupper(escolhaAtualizar);
                }

                if (escolhaAtualizar == 'S')
                {
                    printf("Insira o novo preço do produto: ");
                    fflush(stdin);
                    while (1)
                    {
                        // Lê a entrada como uma string
                        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
                        {
                            // Verifica se a string contém apenas dígitos e ponto decimal
                            char *endptr;
                            cardap.preco = strtod(buffer, &endptr);

                            if (endptr == buffer || *endptr != '\n')
                            {
                                // A conversão falhou ou há caracteres não convertidos
                                printf("Entrada inválida. Por favor, insira um valor válido: ");
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
                            printf("Erro na leitura. Por favor, insira um valor válido: ");
                        }
                    }
                }

                char escolha;
                printf("Deseja adicionar (A) ou deletar (D) ingredientes? (0 para finalizar): ");
                scanf(" %c", &escolha);
                escolha = toupper(escolha);

                if(escolha == '0'){
                    fclose(pFile);
                    break;
                }

                while(escolha != 'A' && escolha != 'D' && escolha != '0')
                {
                    printf(RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
                    printf("Deseja adicionar (A) ou deletar (D) ingredientes? (0 para finalizar): ");
                    scanf(" %c", &escolha);
                    escolha = toupper(escolha);
                }

                while (escolha == 'A' || escolha == 'D')
                {
                    if (escolha == 'A')
                    {
                        if (cardap.qtdIngredientes < 30)
                        {
                            int codigoIngrediente;
                            listarIngredienteCardapio(); // Chama a função listarIngrediente para mostrar os ingredientes disponíveis.

                            codigoIngrediente = verificacaoCodigo("Insira o código do ingrediente a ser adicionado: ", RED "ERRO INSIRA UM CÓDIGO DE INGREDIENTE VÁLIDO" RESET);

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
                            printf("Lista de ingredientes cheia. Não é possível adicionar mais ingredientes.\n");
                    }
                    else if (escolha == 'D')
                    {
                        if (cardap.qtdIngredientes > 0)
                        {
                            int codigoIngrediente;
                            cardapio produto = getProdutoPorCodigo(codigo); // Chama a função listarCardapio para mostrar os ingredientes no produto.

                            printf("\nCódigo: %i\n", produto.codigo);
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

                            printf("\nPreço: %.2f\n", produto.preco);

                            printf("------------------------------------------\n------------------------------------------");
                            printf("\n\n");

                            codigoIngrediente = verificacaoCodigo("Insira o código do ingrediente a ser deletado: ", RED "ERRO INSIRA UM CÓDIGO DE INGREDIENTE VÁLIDO");

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
                                printf("Código de ingrediente inválido ou não encontrado no produto.\n");
                        }
                        else
                            printf("O produto não possui ingredientes para deletar.\n");
                    }

                    printf("Deseja continuar adicionar (A) ou deletar (D) ingredientes? (0 para finalizar): ");
                    scanf(" %c", &escolha);
                    escolha = toupper(escolha);

                    while(escolha != 'A' && escolha != 'D' && escolha != '0')
                    {
                        printf(RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
                        printf("Deseja adicionar (A) ou deletar (D) ingredientes? (0 para finalizar): ");
                        scanf(" %c", &escolha);
                        escolha = toupper(escolha);
                    }
                }
                system("cls");

                fseek(pFile, -sizeof(cardapio), SEEK_CUR); // Volta para a posição do último registro lido.
                fwrite(&cardap, sizeof(cardapio), 1, pFile);   // Escreve os dados atualizados no arquivo.
                break;
            }
        }

        fclose(pFile); // fecha o arquivo "cardapio.txt".

        if (!encontrou) printf("Produto não encontrado!\n"); // Exibe uma mensagem se o produto não for encontrado.

        listarCardapio();
        int escolhaFunc;
        escolhaFunc = verificacaoCodigo("\n1 - Continuar \n0 - Sair \nInsira uma opção: ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
        if(escolhaFunc == 0) break;
    }
    system("cls");
}
