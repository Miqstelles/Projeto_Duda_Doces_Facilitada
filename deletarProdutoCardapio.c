#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void AtivarDesativarProdutoCardapio()
{
    do
    {
        system("cls");
        listarCardapio();

        cardapio cardap;
        FILE *pFile;
        pFile = fopen("cardapio.txt", "r+");

        int codigo, escolha, encontrou = 0;

        escolha = verificacaoCodigo("\nDeseja Ativar ou Desativar um Produto? (1 - Ativar, 2 - Desativar, 0 - Sair): ", RED "\nERRO: Insira uma opção válida" RESET);
        if(escolha == 0) break;

        while(escolha < 0 || escolha > 2){
            printf(RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);
            escolha = verificacaoCodigo("\nDeseja Ativar ou Desativar um Produto?(1 - Ativar, 2 - Desativar, 0 - Sair): ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA" RESET);
        }
        if(escolha == 0) break;

        codigo = verificacaoCodigo("\nInsira o código do produto a ser ativado/desativado: ", RED "\nERRO: Insira um código válido" RESET);

        while (fread(&cardap, sizeof(cardapio), 1, pFile))
        {
            if (cardap.codigo == codigo)
            {
                encontrou = 1;

                // Remove qualquer indicação de ativado ou desativado
                strtok(cardap.nome, "(ATIVADO)");
                strtok(cardap.nome, "(DESATIVADO)");

                if (escolha == 1)
                {
                    // Ativa o produto
                    strcat(cardap.nome, GREEN "(ATIVADO)" RESET);
                    printf("\nProduto %s ativado com sucesso!\n", cardap.nome);
                }
                else if (escolha == 2)
                {
                    // Desativa o produto
                    strcat(cardap.nome, RED "(DESATIVADO)" RESET);
                    printf("\nProduto %s desativado com sucesso!\n", cardap.nome);
                }

                fseek(pFile, -sizeof(cardapio), SEEK_CUR);
                fwrite(&cardap, sizeof(cardapio), 1, pFile);

                break;
            }
        }
        if (!encontrou) printf("\nProduto não encontrado.\n");

        int escolhaFunc;
        escolhaFunc = verificacaoCodigo("\n1 - Continuar \n0 - Sair \nInsira uma opção: ", RED "\nERRO INSIRA UMA OPÇÃO VÁLIDA\n" RESET);

        if(escolhaFunc == 0) break;

        fclose(pFile);
    }
    while(1);

    system("cls");
}
