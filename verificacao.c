#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "cores.h"
char verificacao(){

    char escolha;
    int i=0;

    do{

        printf(GREEN "\n\n\tDigite sua escolha: " RESET) ;
        fflush(stdin);

        escolha=getch();

        if(isdigit(escolha)!= 0){
            if(escolha != '0' && escolha != '1' && escolha != '2' && escolha != '3' && escolha != '4' && escolha != '5' && escolha != '6'){
                printf(RED "\n\tOpção invalida !!!\n" RESET);
                Sleep(500);
                continue;
            }
            return escolha;
        }else{

            printf(RED "\n\tOpção invalida !!!\n" RESET);
            Sleep(500);
            continue;
        }

    }while(i==1);

}
