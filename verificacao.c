#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "cores.h"
#define MAXCHAR 128

char verificacao(char maxNumero, char textoEscolha[MAXCHAR], char textoErro[MAXCHAR]){
    char escolha;
    int maxNumeroInt = maxNumero - 48;
    int escolhaInt;
    int i=0;

    do{
        printf("%s", textoEscolha) ;
        fflush(stdin);

        escolha=getch();
        escolhaInt = escolha - '0';

        if(isdigit(escolha) != 0){
            if(escolhaInt < 0 || escolhaInt > maxNumeroInt){
                printf("%s", textoErro);
                Sleep(500);
                continue;
            }
            return escolha;
        }

        printf("%s", textoErro);
        Sleep(500);
        continue;
    }while(i==1);
}
