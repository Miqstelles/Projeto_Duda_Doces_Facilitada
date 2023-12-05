#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"
#include "cardapio.h"
#include "ingredientes.h"
#include "cores.h"

void AtivarDesativarProdutoCardapio()
{
    int escolha;
    do
    {
        listarCardapio();

        cardapio cardap;
        FILE *pFile;
        pFile = fopen("cardapio.txt", "r+");

        int codigo, encontrou = 0;
        escolha = verificacaoCodigo("\nDeseja Ativar ou Desativar um Produto? (1 - Ativar, 2 - Desativar, 0 - Sair): ", RED "\nERRO: Insira uma op��o v�lida" RESET);
        codigo = verificacaoCodigo("\nInsira o c�digo do produto a ser ativado/desativado: ", RED "\nERRO: Insira um c�digo v�lido" RESET);

        while (fread(&cardap, sizeof(cardapio), 1, pFile))
        {
            if (cardap.codigo == codigo)
            {
                encontrou = 1;

                // Remove qualquer indica��o de ativado ou desativado
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

        fclose(pFile);

        if (!encontrou)
        {
            printf("\nProduto n�o encontrado.\n");
        }

        escolha = verificacaoCodigo("Deseja continuar(0 - N�o, 1 - Sim): ", "ERRO INSIRA UMA OP��O V�LIDA");
    }
    while(escolha !=0);

    system("cls");
}
