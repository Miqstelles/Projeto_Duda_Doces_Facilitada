#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"

void listarClientesPedido(){
    cliente clnt;
    int escolha;

    FILE *pFile;

    pFile = fopen("clientes.txt", "r");

    printf("\n=========================================================");
    printf("\nClientes\n");
    printf("\nCódigo \t Nome \t\t Pedidos\t");

    while(fread(&clnt, sizeof(cliente), 1, pFile) == 1)
    {
        printf("\n%-9i%-16s", clnt.codigo, clnt.nome);

        int numPedidos = 0;
        printf("[");
        for (int i = 0; i < 5 && clnt.pedidos[i] != 0; i++) {
            printf("%i", clnt.pedidos[i]);

            if (clnt.pedidos[i + 1] != 0) printf(", ");

            numPedidos++;

            if (numPedidos >= 5 && clnt.pedidos[numPedidos] != 0) printf("...");
        }
        printf("]");
    }
    printf("\n=========================================================\n");

    fclose(pFile);
}

