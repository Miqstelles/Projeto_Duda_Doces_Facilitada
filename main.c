#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

// TELA CONTROLE ESTOQUE DE INGREDIENTES
typedef struct ingredientes{
    char nome[80];
    int codigo;
    int quantidade;
} ingredientes;

typedef struct cardapio{
    char nome[80];
    int codigo;
    int tipo;
    int listaIngredientes[80];
    int qtdIngredientes;
} cardapio;

void adicionarIngrediente()
{
    FILE *pFile;
    ingredientes *ing;
    int n, i;

    printf("Quantos ingredientes deseja adicionar?: ");
    scanf("%i", &n);

    ing = (ingredientes *)calloc(n, sizeof(ingredientes));
    pFile = fopen("estoque_ingredientes.txt", "a");

    for (i = 0; i < n; i++)
    {
        printf("Insira o codigo do produto: ");
        scanf("%i", &ing[i].codigo);

        while (codigoJaExiste(ing[i].codigo))
        {
            printf("Código já existe. Insira um novo código: ");
            scanf("%i", &ing[i].codigo);
        }

        fflush(stdin);
        printf("Insira o nome do ingrediente: ");
        scanf("%[^\n]s", ing[i].nome);

        printf("Insira a quantidade em estoque: ");
        scanf("%i", &ing[i].quantidade);

        fwrite(&ing[i], sizeof(ingredientes), 1, pFile);
    }
    fclose(pFile);
}

int codigoJaExiste(int codigo)
{
    FILE *file = fopen("estoque_ingredientes.txt", "r");

    if (file)
    {
        ingredientes temp;

        while (fread(&temp, sizeof(ingredientes), 1, file))
        {
            if (temp.codigo == codigo)
            {
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    }

    return 0;
}

void listarIngrediente()
{
    ingredientes ing1;
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");

    printf("\n=========================================================");
    printf("\nEstoque\n");
    printf("\nCódigo \t Nome \t\t   Quantidade");

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade);
    }

    printf("\n=========================================================\n");
    fclose(pFile);
}

void qtdIngredientes()
{
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");
    fseek(pFile, 0, SEEK_END);
    int n = ftell(pFile) / sizeof(ingredientes);
    printf("\nQuantidade de ingredientes em estoque é de: %i\n", n);
}

void pesquisarIngrediente()
{
    ingredientes ing1;
    FILE *pFile;
    pFile = fopen("estoque_ingredientes.txt", "r");

    int codigo, encontrou = 0;
    printf("Insira o codigo do ingrediente: ");
    scanf("%i", &codigo);

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            printf("\n=========================================================");
            printf("\nEstoque\n");
            printf("\nCódigo \t Nome \t\t   Quantidade");
            printf("\n%-9i%-20s%4i", ing1.codigo, ing1.nome, ing1.quantidade);
            printf("\n=========================================================\n");
            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("Ingrediente não encontrado!\n");

    fclose(pFile);
}

void atualizarIngrediente()
{
    listarIngrediente();

    ingredientes ing1;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("estoque_ingredientes.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do ingrediente a ser atualizado: ");
    scanf("%i", &codigo);

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            encontrou = 1;
            fflush(stdin);
            printf("Insira o novo nome do ingrediente: ");
            scanf("%[^\n]s", ing1.nome);

            printf("Insira a nova quantidade em estoque: ");
            scanf("%i", &ing1.quantidade);

            printf("\nIngrediente %s atualizado com sucesso!\n", ing1.nome);
        }
        fwrite(&ing1, sizeof(ingredientes), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("estoque_ingredientes.txt", "w");

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
        {
            fwrite(&ing1, sizeof(ingredientes), 1, pFile);
        }

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Ingrediente não encontrado!\n");
}

void deletarIngrediente()
{
    listarIngrediente();

    ingredientes ing1;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("estoque_ingredientes.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do ingrediente a ser deletado: ");
    scanf("%i", &codigo);

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            encontrou = 1;
        }
        else
            fwrite(&ing1, sizeof(ingredientes), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("estoque_ingredientes.txt", "w");

        while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
        {
            fwrite(&ing1, sizeof(ingredientes), 1, pFile);
        }

        fclose(pFile);
        fclose(pFile1);
    }
    else
        printf("Ingrediente não encontrado!\n");
}

void telaEstoqueIngredientes()
{
    int escolha;

    do
    {
        printf("\nESTOQUE DE INGREDIENTES");
        printf("\n1 - Adicionar Ingredientes");
        printf("\n2 - Listar Ingredientes");
        printf("\n3 - Total de Ingredientes");
        printf("\n4 - Pesquisar Ingrediente");
        printf("\n5 - Atualizar Ingrediente");
        printf("\n6 - Deletar Ingrediente");
        printf("\n0 - Sair");

        int read = 0;

        while (read != 1)
        {
            printf("\n\nInsira uma opção: ");
            read = scanf("%i", &escolha);

            if (read != 1)
            {
                printf("ERRO! Digite uma opção valida");
                scanf("%*[^\n]");
            }
        }

        switch (escolha)
        {
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
    }
    while (escolha != 0);

    system("cls");
}
// TELA CONTROLE ESTOQUE DE INGREDIENTES //

// TELA CARDAPIO
void adicionarProdutoCardapio(){
    cardapio *cardap;
    ingredientes ing1;

    FILE *pFile;
    FILE *pFile1;
    int n, i, codigo;

    printf("Quantos produtos deseja adicionar ao cardápio?: ");
    scanf("%i", &n);

    cardap = (cardapio *)calloc(n, sizeof(cardapio));
    pFile = fopen("cardapio.txt", "a");
    pFile1 = fopen("estoque_ingredientes.txt", "r");

    for (i = 0; i < n; i++)
    {
        cardap[i].qtdIngredientes = 0;

        printf("Insira o codigo do produto: ");
        scanf("%i", &cardap[i].codigo);

        printf("Insira o tipo do produto:\n");
        printf("\n1 - Bolo");
        printf("\n2 - Doce");
        printf("\n3 - Sobremesa");
        printf("\nSelecione: ");
        scanf("%i", &cardap[i].tipo);

        fflush(stdin);
        printf("Insira o nome do produto: ");
        scanf("%[^\n]s", cardap[i].nome);

        int qtd = 0;

        while (codigo != 0)
        {
            listarIngrediente();
            printf("Selecione um ingrediente (0 para finalizar): ");
            scanf("%i", &codigo);

            if (cardap[i].qtdIngredientes < 30)
            {
                rewind(pFile1);
                while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
                {
                    if (ing1.codigo == codigo){
                        cardap[i].listaIngredientes[cardap[i].qtdIngredientes] = ing1.codigo;
                        cardap[i].qtdIngredientes++;
                    }
                }
            }
            else
            {
                printf("Lista de ingredientes cheia. Não é possível adicionar mais ingredientes.\n");
            }
        }

        fwrite(&cardap[i], sizeof(cardapio), 1, pFile);
    }

    free(cardap);
    fclose(pFile);
    fclose(pFile1);
}

char* getNomeIngredientePorCodigo(int codigo) {
    FILE *pFile = fopen("estoque_ingredientes.txt", "r");
    ingredientes ing1;
    char *nomeIngrediente = NULL;

    while (fread(&ing1, sizeof(ingredientes), 1, pFile)) {
        if (ing1.codigo == codigo) {
            nomeIngrediente = strdup(ing1.nome);
            break;
        }
    }

    fclose(pFile);

    return nomeIngrediente;
}

void listarCardapio() {
    cardapio cardap;
    FILE *pFile = fopen("cardapio.txt", "r");

    while (fread(&cardap, sizeof(cardapio), 1, pFile)) {
        printf("\nCódigo: %i\n", cardap.codigo);
        printf("Nome: %s\n", cardap.nome);
        printf("Tipo: %i\n", cardap.tipo);
        printf("Quantidade de Ingredientes: %i\n", cardap.qtdIngredientes);

        printf("Ingredientes:\n");

        for (int i = 0; i < cardap.qtdIngredientes; i++) {
            int codigoIngrediente = cardap.listaIngredientes[i];
            char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
            printf("  Nome: %s\n", nomeIngrediente);
        }

        printf("\n");
    }

    fclose(pFile);
}

void telaCardapio()
{
    int escolha;

    do
    {
        printf("\nESTOQUE DE INGREDIENTES");
        printf("\n1 - Adicionar Produto no Cardápio");
        printf("\n2 - Listar Cardapio");
        printf("\n0 - Sair");

        int read = 0;

        while (read != 1)
        {
            printf("\n\nInsira uma opção: ");
            read = scanf("%i", &escolha);

            if (read != 1)
            {
                printf("ERRO! Digite uma opção valida");
                scanf("%*[^\n]");
            }
        }

        switch (escolha){
        case 1:
            system("cls");
            adicionarProdutoCardapio();
            break;
        case 2:
            system("cls");
            listarCardapio();
            break;
        }
    }
    while (escolha != 0);

    system("cls");
}

// TELA CARDAPIO //

void barraDeLoading()
{
    system("color 0A");

    char a = 177, b = 219;

    printf("\n\n\n\n");
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t Carregando...\n\n");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++)
        printf("%c", a);

    printf("\r");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++)
    {
        printf("%c", b);
        Sleep(100);
    }

    system("color 7");
    system("cls");
}

int main()
{
    barraDeLoading();

    setlocale(LC_ALL, "Portuguese_Brazil");

    int escolha;

    do
    {
        printf("\nBem Vindo");
        printf("\n1 - Cardapio");
        printf("\n2 - Vendas");
        printf("\n3 - Estoque de Ingredientes");
        printf("\n0 - Sair");

        int read = 0;

        while (read != 1)
        {
            printf("\n\nInsira uma opção: ");
            read = scanf("%i", &escolha);

            if (read != 1)
            {
                printf("ERRO! Digite uma opção valida");
                scanf("%*[^\n]");
            }
        }

        switch (escolha)
        {
        case 1:
            system("cls");
            telaCardapio();
            break;
        case 2:
            system("cls");
            printf("Vendas");
            break;
        case 3:
            system("cls");
            telaEstoqueIngredientes();
            break;
        }
    }
    while (escolha != 0);

    printf("\nVolte sempre!\n");

    return 0;
}
