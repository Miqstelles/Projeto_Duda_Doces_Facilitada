#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct cliente {
    char nome[80];
    int codigo;
    int pedidos[200];
} cliente;

void cadastrarCliente();
void listarClientes();
void listarClientesPedido();
void pesquisarCliente();
int obterProximoCodigoCliente();

#endif
