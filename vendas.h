#ifndef VENDAS_H
#define VENDAS_H
#include "cardapio.h"

typedef struct vendas{
    int codigo;
    int pedido[80];
    int qtdProdutos;
    float valor;
    char nomeCliente[80];
} vendas;

int obterProximoCodigoVenda();
void novoPedido();
cardapio getProdutoPorCodigo(int codigo);
void listarVendas();
void pesquisarPedido();

#endif
