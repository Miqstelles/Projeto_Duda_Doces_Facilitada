#ifndef VENDAS_H
#define VENDAS_H
#include "cardapio.h"

typedef struct vendas{
    int codigo;
    int pedido[80];
    int qtdProdutos;
    int status;
    float valor;
    char nomeCliente[80];
} vendas;

int obterProximoCodigoVenda();
void novoPedido();
cardapio getProdutoPorCodigo(int codigo);
void atualizarStatusPedido();
void listarVendas();
void pesquisarPedido();

#endif
