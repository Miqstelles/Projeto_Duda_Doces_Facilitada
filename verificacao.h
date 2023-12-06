#ifndef VERIFICACAO_H_INCLUDED
#define VERIFICACAO_H_INCLUDED
#include <stdbool.h>
#define MAXCHAR 128

char verificacao(char maxNumero, char textoEscolha[MAXCHAR], char textoErro[MAXCHAR]);
int verificacaoCodigo(char textoEscolha[MAXCHAR], char textoErro[MAXCHAR]);
bool verificacaoNome(char nome[MAXCHAR], char textoErro[MAXCHAR]);

#endif // VERIFICACAO_H_INCLUDED
