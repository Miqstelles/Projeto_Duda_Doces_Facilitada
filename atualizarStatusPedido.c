#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cores.h"

void atualizarStatusPedido()
{
    while(1)
    {
        system("cls");
        FILE *pFile;
        vendas vnd;

        listarClientesPedido();
        pFile = fopen("vendas.txt", "r+");

        int codigo, encontrou = 0;
        codigo = verificacaoCodigo("\nInsira o c�digo do pedido que deseja alterar o status(0 - Sair): ", RED "\nERRO INSIRA UM C�DIGO V�LIDO\n" RESET);
        if (codigo == 0) break;

        char status[3][80] = {YELLOW "Em andamento" RESET, RED "Cancelado" RESET, GREEN "Concluido" RESET};

        while (fread(&vnd, sizeof(vendas), 1, pFile))
        {
            if (vnd.codigo == codigo)
            {
                encontrou = 1;
                printf("\n1 - Em andamento");
                printf("\n2 - Cancelado");
                printf("\n3 - Concluido");

                vnd.status = verificacaoCodigo("\nInsira uma op��o: ", RED "\nERRO INSIRA UMA OP��O V�LIDA\n" RESET);

                while(vnd.status <= 0 || vnd.status > 3)
                {
                    printf(RED "\nERRO INSIRA UMA OP��O V�LIDA\n" RESET);
                    vnd.status = verificacaoCodigo("\nInsira uma op��o: ", RED "\nERRO INSIRA UMA OP��O V�LIDA\n" RESET);
                }

                printf(GREEN "\nStatus do pedido %i alterado para %s" RESET, vnd.codigo, status[vnd.status - 1]);

                fseek(pFile, -sizeof(vendas), SEEK_CUR); // Move o ponteiro de posi��o no arquivo para tr�s de uma quantidade de bytes igual ao tamanho da estrutura 'ingredientes'.
                fwrite(&vnd, sizeof(vendas), 1, pFile); // Escreve os dados da estrutura 'vnd' de volta no arquivo na posi��o atual do ponteiro.

                fclose(pFile);
                break;
            }
        }
        if (!encontrou) printf(RED "\nPedido n�o encontrado.\n" RESET);
        int escolha;

        escolha = verificacaoCodigo("\n1 - Continuar \n0 - Sair \nInsira uma op��o: ", RED "\nERRO INSIRA UMA OP��O V�LIDA\n" RESET);
        if(escolha == 0) break;
    }
    system("cls");
}
