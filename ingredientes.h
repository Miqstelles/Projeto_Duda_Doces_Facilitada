#ifndef INGREDIENTES_H
#define INGREDIENTES_H

typedef struct ingredientes
{
    char nome[80];
    int codigo;
    int quantidade;
} ingredientes;

int obterProximoCodigo();
void adicionarIngrediente();
int codigoJaExiste(int codigo);
void listarIngrediente();
void qtdIngredientes();
void pesquisarIngrediente();
void atualizarIngrediente();
void deletarIngrediente();

#endif
