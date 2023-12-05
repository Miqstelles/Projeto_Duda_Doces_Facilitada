#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"

int obterProximoCodigoCliente(){
    FILE *pFile; // Declara um ponteiro de arquivo para o arquivo de cliente.
    cliente clnt; // Declara a estrutura chamada clientes.
    int maiorCodigo = 0;

    pFile = fopen("clientes.txt", "r"); // Abre o arquivo de clientes para leitura.

    while(fread(&clnt, sizeof(cliente), 1 ,pFile) == 1){
        if(clnt.codigo > maiorCodigo) maiorCodigo = clnt.codigo;
    }

    fclose(pFile); // Fecha o arquivo de clientes.

    return maiorCodigo + 1; // Retorna o próximo código disponível (maior código + 1).
}

