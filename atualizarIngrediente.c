#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"

void atualizarIngrediente()
{
    while (1)
    {
        system("cls");
        listarIngrediente(); // Chama a função listarIngrediente para mostrar a lista de ingredientes.

        ingredientes ing1; // Declara uma estrutura chamada ingredientes.
        FILE *pFile; // Declara um ponteiro de arquivo para "estoque_ingredientes.txt".

        pFile = fopen("estoque_ingredientes.txt", "r+"); // Abre o arquivo "estoque_ingredientes.txt" para leitura e escrita.


        char escolha;
        int codigo;
        int encontrou = 0;
        codigo = verificacaoCodigo("Insira o código do ingrediente a ser atualizado(0 - Sair): ", RED "\nERRO INSIRA UM CÓDIGO VÁLIDO\n" RESET);

        if (codigo == 0)
            break;

        while (fread(&ing1, sizeof(ingredientes), 1, pFile))
        {
            if (ing1.codigo == codigo) // Verifica se o código do ingrediente corresponde ao código fornecido.
            {
                if (strstr(ing1.nome, "(DESATIVADO)") == NULL)
                {
                    encontrou = 1;
                    printf("\nDeseja atualizar o nome do ingrediente?(S/N): ");
                    fflush(stdin);
                    scanf("%c", &escolha);

                    while (toupper(escolha) != 'N' && toupper(escolha) != 'S')
                    {
                        printf(RED "\nERRO! " RESET "Insira uma escolha valida(S/N): ");
                        fflush(stdin);
                        scanf("%c", &escolha);
                    }

                    if (toupper(escolha) == 'S')
                    {
                        fflush(stdin);
                        printf("Insira o novo nome do ingrediente: ");
                        scanf("%79[^\n]s", ing1.nome);
                        strcat(ing1.nome, GREEN "(ATIVADO)" RESET);
                    }

                    printf("\nDeseja atualizar a quantidade de ingrediente do ingrediente %s?(S/N): ", ing1.nome);
                    fflush(stdin);
                    scanf("%c", &escolha);

                    while (toupper(escolha) != 'N' && toupper(escolha) != 'S')
                    {
                        printf(RED "\nERRO! Insira uma escolha valida(S/N): " RESET);
                        fflush(stdin);
                        scanf("%c", &escolha);
                    }

                    if (toupper(escolha) == 'S')
                    {
                        fflush(stdin);
                        ing1.quantidade = verificacaoCodigo("Insira a nova quantidade em estoque: ", RED "\nERRO INSIRA UMA QUANTIDADE VÁLIDA\n" RESET);
                    }

                    printf("\nIngrediente %s atualizado com sucesso!\n", ing1.nome);

                    fseek(pFile, -sizeof(ingredientes), SEEK_CUR); // Volta para a posição do último registro lido.
                    fwrite(&ing1, sizeof(ingredientes), 1, pFile);   // Escreve os dados atualizados no arquivo.
                    break;
                }
            }
        }
        if (encontrou == 0) printf(RED "Código de ingrediente inexistente ou desativado. Tente novamente.\n" RESET);

        int opcao;
        opcao = verificacaoCodigo("\n1- Continuar, 0 - Sair \nInsira uma opção: ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);

        while(opcao < 0 || opcao > 1){
            printf("\nERRO INSIRA UMA OPÇÃO VÁLIDA\n");
            opcao = verificacaoCodigo("\n1- Continuar \n0 - Sair \nInsira uma opção: ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);
        }

        fclose(pFile); // fecha o arquivo "estoque_ingredientes.txt".

        if(opcao == 0) break;
    }
    system("cls");
}
