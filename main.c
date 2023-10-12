#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct ingredientes{
    char nome[80];
    int codigo;
    int quantidade;
}ingredientes;

void adicionarIngrediente(){
    FILE * pFile;
    ingredientes *ing;
    int n, i;

    printf("Quantos ingredientes deseja adicionar?: ");
    scanf("%i", &n);

    ing = (ingredientes*)calloc(n, sizeof(ingredientes));
    pFile = fopen("estoque_ingredientes.txt", "a");

    for(i=0; i<n; i++){
        printf("Insira o codigo do produto: ");
        scanf("%i", &ing[i].codigo);

        fflush(stdin);
        printf("Insira o nome do produto: ");
        scanf("%[^\n]s", ing[i].nome);

        printf("Insira a quantidade em estoque: ");
        scanf("%i", &ing[i].quantidade);

        fwrite(&ing[i], sizeof(ingredientes),1, pFile);
    }
    fclose(pFile);
}
void listarIngrediente(){
    ingredientes ing1;
    FILE * pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");

    printf("\n=========================================================");
    printf("\nEstoque\n");
    printf("\nCódigo \t Nome \t\t   Quantidade");

    while(fread(&ing1, sizeof(ingredientes), 1, pFile)){
        printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade);
    }

    printf("\n=========================================================\n");
    fclose(pFile);
}

void qtdIngredientes(){
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");
    fseek(pFile, 0, SEEK_END);
    int n = ftell(pFile)/sizeof(ingredientes);
    printf("\nQuantidade de ingredientes em estoque é de: %i\n", n);
}

void pesquisarIngrediente(){
    ingredientes ing1;
    FILE * pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");

    int codigo, encontrou = 0;
    printf("Insira o codigo do ingrediente: ");
    scanf("%i", &codigo);

    while(fread(&ing1, sizeof(ingredientes), 1, pFile)){
        if(ing1.codigo == codigo) {
            printf("\n=========================================================");
            printf("\nEstoque\n");
            printf("\nCódigo \t Nome \t\t   Quantidade");
            printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade);
            printf("\n=========================================================\n");
            encontrou = 1;
        }
    }
    if(!encontrou) printf("Ingrediente não encontrado!\n");

    fclose(pFile);
}
void atualizarIngrediente(){
    listarIngrediente();

    ingredientes ing1;
    FILE * pFile;
    FILE * pFile1;
    pFile = fopen("estoque_ingredientes.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o codigo do ingrediente a ser atualizado: ");
    scanf("%i", &codigo);

    while(fread(&ing1, sizeof(ingredientes),1, pFile)){
        if(ing1.codigo == codigo) {
            encontrou = 1;
            fflush(stdin);
            printf("Insira o novo nome do produto: ");
            scanf("%[^\n]s", ing1.nome);

            printf("Insira a nova quantidade em estoque: ");
            scanf("%i", &ing1.quantidade);

            printf("\nIngrediente %s atualizado com sucesso!\n", ing1.nome);
        }
        fwrite(&ing1, sizeof(ingredientes), 1, pFile1);
    }
    fclose(pFile);
    fclose(pFile1);

    if(encontrou) {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("estoque_ingredientes.txt", "w");

        while(fread(&ing1, sizeof(ingredientes), 1, pFile1)){
            fwrite(&ing1, sizeof(ingredientes), 1, pFile);
        }

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Ingrediente não encontrado!\n");
}
void deletarIngrediente(){
    ingredientes ing1;
    FILE * pFile;
    FILE * pFile1;
    pFile = fopen("estoque_ingredientes.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o codigo do ingrediente a ser deletado: ");
    scanf("%i", &codigo);

    while(fread(&ing1, sizeof(ingredientes), 1, pFile)){
        if(ing1.codigo == codigo) {
            encontrou = 1;
        }
        else fwrite(&ing1, sizeof(ingredientes),1, pFile1);
    }
    fclose(pFile);
    fclose(pFile1);

    if(encontrou) {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("estoque_ingredientes.txt", "w");

        while(fread(&ing1, sizeof(ingredientes), 1, pFile1)){
            fwrite(&ing1, sizeof(ingredientes), 1, pFile);
        }

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Ingrediente não encontrado!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int escolha;

    do{
        printf("\nESTOQUE DE INGREDIENTES");
        printf("\n1 - Adicionar Ingredientes");
        printf("\n2 - Listar Ingredientes");
        printf("\n3 - Total de Ingredientes");
        printf("\n4 - Pesquisar Ingrediente");
        printf("\n5 - Atualizar Ingrediente");
        printf("\n6 - Deletar Ingrediente");
        printf("\n0 - Sair");

        int read = 0;

        while(read != 1){
            printf("\n\nInsira uma opção: ");
            read = scanf("%i", &escolha);

            if(read != 1){
                printf("ERRO! Digite uma opção valida");
                scanf("%*[^\n]");
            }
        }

        switch(escolha){
            case 1:
                system("cls");
                adicionarIngrediente();
                break;
            case 2:
                system("cls");
                listarIngrediente();
                break;
            case 3:
                system("cls");
                qtdIngredientes();
                break;
            case 4:
                system("cls");
                pesquisarIngrediente();
                break;
            case 5:
                system("cls");
                atualizarIngrediente();
                break;
            case 6:
                system("cls");
                deletarIngrediente();
                break;
        }
    }while(escolha != 0);

    printf("\nVolte sempre!\n");

    return 0;
}
