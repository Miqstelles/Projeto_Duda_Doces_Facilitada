#include <stdio.h>
#include <stdlib.h>
#include "vendas.h"
#include "cardapio.h"
#include "clientes.h"
#include "cores.h"

void novoPedido()
{
    int escolha;
    int codigo;
    do
    {
        // FAZER STATUS
        system("cls");

        FILE *pFile; // Declara um ponteiro de arquivo para o arquivo de vendas.
        FILE *pFile1;   // Declara um ponteiro de arquivo para o arquivo de produtos.
        FILE *pFile2;  // Declara um ponteiro de arquivo para o arquivo de clientes.

        vendas *vnd; // Declara um ponteiro para a estrutura chamada vendas.
        cardapio cardap;
        cliente clnt;

        vnd = (vendas *)calloc(1, sizeof(vendas)); // Aloca memória para a estrutura vendas.
        pFile = fopen("vendas.txt", "a"); // Abre o arquivo "vendas.txt" em modo de apêndice.
        pFile1 = fopen("cardapio.txt", "r"); // Abre o arquivo "cardapio.txt" para leitura+apêndice.
        pFile2 = fopen("clientes.txt", "r+"); // Abre o arquivo "cardapio.txt" para leitura+apêndice.

        vnd[0].codigo = obterProximoCodigoVenda(); // Obtém o próximo código para a venda.
        vnd[0].status = 0;

        listarClientesPedido();

        codigo = verificacaoCodigo("\nInsira o codigo do cliente que esta realizando o pedido(0 - Sair): ", RED "\nERRO INSIRA UM CÓDIGO VÁLIDO" RESET);

        if(codigo == 0){
            system("cls");
            break;
        }

        while(codigo >= obterProximoCodigoCliente())
        {
            codigo = verificacaoCodigo("\nERRO: Codigo não encontrado! Insira o codigo do cliente que esta realizando o pedido(0 - Sair): ", RED "\nERRO INSIRA UM CÓDIGO VÁLIDO" RESET);
        }

        if(codigo == 0){
            system("cls");
            break;
        }

        while (fread(&clnt, sizeof(cliente), 1, pFile2))
        {
            if(clnt.codigo == codigo)
            {
                strcpy(vnd[0].nomeCliente, clnt.nome);
                // Encontra o próximo índice disponível no array de pedidos
                int i;
                for (i = 0; i < 200; i++)
                {
                    if (clnt.pedidos[i] == 0)
                    {
                        clnt.pedidos[i] = vnd[0].codigo;
                        break;
                    }
                }

                fseek(pFile2, -sizeof(cliente), SEEK_CUR);
                fwrite(&clnt, sizeof(cliente), 1, pFile2);
                fflush(pFile2);
                break;
            }
        }

        vnd[0].qtdProdutos = 0; // Inicializa a quantidade de produtos no pedido.

        listarCardapioPedido(); // Chama a função listarCardapio para mostrar os produtos disponíveis.
        while (1)
        {
            int codigoProduto;

            codigoProduto = verificacaoCodigo("\nInsira o código do produto a ser adicionado (0 para finalizar): ", RED "\nERRO INSIRA UM CÓDIGO VÁLIDO" RESET);

            if (codigoProduto == 0) break; // Finaliza a adição de produtos quando o código é 0.

            int produtoExiste = 0;

            while (fread(&cardap, sizeof(cardapio), 1, pFile1))
            {
                if (cardap.codigo == codigoProduto && strstr(cardap.nome, "(DESATIVADO)") == NULL)
                {
                    produtoExiste = 1;
                    vnd[0].pedido[vnd[0].qtdProdutos] = codigoProduto;
                    vnd[0].qtdProdutos++;
                    printf("Produto adicionado ao pedido.\n");
                    break;
                }
            }

            if (!produtoExiste) printf(RED "Código de produto inexistente ou desativado. Tente novamente.\n" RESET);
        }

        fwrite(&vnd[0], sizeof(vendas), 1, pFile); // Escreve os dados da venda no arquivo.

        int read = 0;

        escolha = verificacaoCodigo("\nDeseja adicionar mais um pedido?(1 - Sim, 0 - Não): ", "\nERRO INSIRA UM CÓDIGO VÁLIDO");

        fclose(pFile); // Fecha o arquivo de vendas.

    }
    while(escolha != 0 && codigo != 0);
    system("cls");
}
