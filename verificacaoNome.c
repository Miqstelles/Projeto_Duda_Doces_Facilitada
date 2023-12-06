#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cores.h"
#include <stdbool.h>
#define MAXCHAR 128

bool verificacaoNome(char nome[MAXCHAR], char textoErro[MAXCHAR])
{
    if (strlen(nome) != 0) return 1;

    printf("%s", textoErro);
    Sleep(500);
}
