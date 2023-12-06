#include <stdio.h>
#include <stdlib.h>
#include "ingredientes.h"
#include "cores.h"

void DesativarAtivarIngrediente()
{
    int escolha;

    do
    {
        listarIngrediente();

        ingredientes ing1;
        FILE *pFile;
        pFile = fopen("estoque_ingredientes.txt", "r+");

        int codigo, encontrou = 0;
        escolha = verificacaoCodigo("\nDeseja Ativar ou Desativar um Ingrediente?(1 - Ativar, 2 - Desativar, 0 - Sair): ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);
        if(escolha == 0) break;

        while(escolha < 0 || escolha > 2){
            printf(RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);
            escolha = verificacaoCodigo("\nDeseja Ativar ou Desativar um Ingrediente?(1 - Ativar, 2 - Desativar, 0 - Sair): ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);
        }
        if(escolha == 0) break;

        codigo = verificacaoCodigo("\nInsira o código do ingrediente a ser desativado/ativado: ", RED "\nERRO INSIRA UM CÓDIGO VALIDO" RESET);

        while (fread(&ing1, sizeof(ingredientes), 1, pFile))
        {
            if (ing1.codigo == codigo)
            {
                encontrou = 1;

                // Remove qualquer indicação de ativado ou desativado
                strtok(ing1.nome, GREEN "(ATIVADO)" RESET);
                strtok(NULL, RED "(DESATIVADO)" RESET);

                if (escolha == 1)
                {
                    // Ativa o ingrediente
                    strcat(ing1.nome, GREEN "(ATIVADO)" RESET);
                    printf("\nIngrediente %s ativado com sucesso!\n", ing1.nome);
                }
                else if (escolha == 2)
                {
                    // Desativa o ingrediente
                    strcat(ing1.nome, RED "(DESATIVADO)" RESET);
                    ing1.quantidade = 0;

                    printf("\nIngrediente %s desativado com sucesso!\n", ing1.nome);
                }

                fseek(pFile, -sizeof(ingredientes), SEEK_CUR); // Move o ponteiro de posição no arquivo para trás de uma quantidade de bytes igual ao tamanho da estrutura 'ingredientes'.
                fwrite(&ing1, sizeof(ingredientes), 1, pFile); // Escreve os dados da estrutura 'ing1' de volta no arquivo na posição atual do ponteiro.

                fclose(pFile);

                break;
            }
        }


        if (!encontrou) printf("\nIngrediente não encontrado.\n");

        escolha = verificacaoCodigo("Deseja continuar(0 - Não, 1 - Sim): ", "\nERRO INSIRA UMA OPÇÃO VÁLIDA");
    }
    while(escolha != 0);
    system("cls");
}
