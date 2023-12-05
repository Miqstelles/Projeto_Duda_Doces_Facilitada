#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"

void cadastrarCliente(){
    FILE * pFile;       // Declara um ponteiro para o arquivo chamado pFile.
    cliente *clnt; // Declara um ponteiro para a estrutura chamada clientes.

    clnt = (cliente *)calloc(1, sizeof(cliente));// Aloca memoria para a estrutura clientes.

    pFile = fopen("clientes.txt", "a"); // Abre o arquivo "clientes.txt" em modo de apéndice(append).

    clnt[0].codigo = obterProximoCodigoCliente(); // Atribui o proximo código disponivel ao campo "codigo" da estrutura clientes.

    fflush(stdin); // Limpa o buffer de entrada padrão (stdin).

    printf("Insira o nome do cliente: ");
    scanf("%79[^\n]s", clnt[0].nome);

    fwrite(&clnt[0], sizeof(cliente), 1, pFile); // Escreve os dados da estrutura clientes no arquivo.

    fclose(pFile); // fecha o arquivo "cliente.txt".

    system("cls");

    printf("\nCliente %s cadastrado com sucesso!\n", clnt[0].nome);
}
