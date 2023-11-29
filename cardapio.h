#ifndef CARDAPIO_H
#define CARDAPIO_H

typedef struct cardapio
{
    char nome[80];
    int codigo;
    int tipo;
    int listaIngredientes[80];
    int qtdIngredientes;
    float preco;
} cardapio;

int obterProximoCodigoCardapio();
void adicionarProdutoCardapio();
int codigoJaExisteCardapio(int codigo);
char* getNomeIngredientePorCodigo(int codigo);
void listarCardapio();
void listarCardapioPedido();
void pesquisarProdutoCardapio();
void atualizarProdutoCardapio();
void deletarProdutoCardapio();

#endif
