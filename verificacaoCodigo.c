#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "cores.h"
#define MAXCHAR 128

int verificacaoCodigo(char textoEscolha[MAXCHAR], char textoErro[MAXCHAR]) {
    char escolha[MAXCHAR];
    int escolhaInt;

    do {
        printf("%s", textoEscolha);
        fflush(stdin);

        if (fgets(escolha, sizeof(escolha), stdin) == NULL) return -1;

        // Remover o caractere de nova linha (se existir)
        if (escolha[strlen(escolha) - 1] == '\n') {
            escolha[strlen(escolha) - 1] = '\0';
        }

        // Verificar se a string de entrada está vazia
        if (strlen(escolha) == 0) {
            printf("%s", textoErro);
            Sleep(500);
            continue;  // Reiniciar o loop
        }

        // Verificar se todos os caracteres são dígitos
        int todosDigitos = 1;
        for (int i = 0; i < strlen(escolha); i++) {
            if (!isdigit(escolha[i])) {
                todosDigitos = 0;
                break;
            }
        }

        if (todosDigitos) {
            // Converter a string para inteiro
            escolhaInt = atoi(escolha);
            return escolhaInt;
        }

        printf("%s", textoErro);
        Sleep(500);
    } while (1);
}
