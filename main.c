#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

// TELA CONTROLE ESTOQUE DE INGREDIENTES
typedef struct ingredientes
{
    char nome[80];
    int codigo;
    int quantidade;
} ingredientes;

typedef struct cardapio
{
    char nome[80];
    int codigo;
    int tipo;
    int listaIngredientes[80];
    int qtdIngredientes;
    float preco;
} cardapio;

typedef struct vendas
{
    int codigo;
    int pedido[80];
    int qtdProdutos;
    float valor;
    char nomeCliente[80];
} vendas;

int obterProximoCodigo()
{
    FILE *pFile;
    ingredientes ing;
    int maiorCodigo = 0;

    pFile = fopen("estoque_ingredientes.txt", "r");

    if (pFile != NULL)
    {
        while (fread(&ing, sizeof(ingredientes), 1, pFile) == 1)
        {
            if (ing.codigo > maiorCodigo) maiorCodigo = ing.codigo;
        }

        fclose(pFile);
    }

    return maiorCodigo + 1;
}


void adicionarIngrediente()
{
    FILE *pFile;
    ingredientes *ing;
    int n = 1, i;

    ing = (ingredientes *)calloc(n, sizeof(ingredientes));
    pFile = fopen("estoque_ingredientes.txt", "a");

    for (i = 0; i < n; i++)
    {
        ing[i].codigo = obterProximoCodigo();

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
    if (!encontrou) printf("Ingrediente não encontrado!\n");

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
            char resposta;

            do
            {
                adicionarIngrediente();
                printf("Deseja adicionar mais algum ingrediente(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

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
        default:
            system("cls");
        }
    }
    while (escolha != 0);

    system("cls");
}
// TELA CONTROLE ESTOQUE DE INGREDIENTES //

// TELA CARDAPIO
int obterProximoCodigoCardapio()
{
    FILE *pFile;
    cardapio cardap;
    int maiorCodigo = 0;

    pFile = fopen("cardapio.txt", "r");

    if (pFile != NULL)
    {
        while (fread(&cardap, sizeof(cardapio), 1, pFile) == 1)
        {
            if (cardap.codigo > maiorCodigo) maiorCodigo = cardap.codigo;
        }

        fclose(pFile);
    }

    return maiorCodigo + 1;
}


void adicionarProdutoCardapio()
{
    cardapio *cardap;
    ingredientes ing1;

    FILE *pFile;
    FILE *pFile1;
    int n = 1, i, codigo = 1;

    cardap = (cardapio *)calloc(n, sizeof(cardapio));
    pFile = fopen("cardapio.txt", "a");
    pFile1 = fopen("estoque_ingredientes.txt", "r");

    for (i = 0; i < n; i++)
    {
        cardap[i].qtdIngredientes = 0;

        cardap[i].codigo = obterProximoCodigoCardapio();

        printf("Insira o tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
        scanf("%i", &cardap[i].tipo);

        fflush(stdin);
        printf("Insira o nome do produto: ");
        scanf("%[^\n]s", cardap[i].nome);

        listarIngrediente();
        while (1)
        {
            int codigoIngrediente;

            printf("Insira o código do ingrediente a ser adicionado (0 para finalizar): ");
            scanf("%i", &codigoIngrediente);

            if (codigoIngrediente == 0) break;

            int ingredienteExiste = 0;

            rewind(pFile1);
            while (fread(&ing1, sizeof(ingredientes), 1, pFile1))
            {
                if (ing1.codigo == codigoIngrediente)
                {
                    ingredienteExiste = 1;
                    cardap[i].listaIngredientes[cardap[i].qtdIngredientes] = codigoIngrediente;
                    cardap[i].qtdIngredientes++;
                    printf("Ingrediente adicionado ao produto.\n");
                    break;
                }
            }

            if (!ingredienteExiste) printf("Código de ingrediente inexistente. Tente novamente.\n");
        }

        printf("Insira o valor do produto: ");
        scanf("%f", &cardap[i].preco);

        fwrite(&cardap[i], sizeof(cardapio), 1, pFile);
    }

    free(cardap);
    fclose(pFile);
    fclose(pFile1);
}

int codigoJaExisteCardapio(int codigo)
{
    FILE *file = fopen("cardapio.txt", "r");

    if (file)
    {
        cardapio temp;

        while (fread(&temp, sizeof(cardapio), 1, file))
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

char* getNomeIngredientePorCodigo(int codigo)
{
    FILE *pFile = fopen("estoque_ingredientes.txt", "r");
    ingredientes ing1;
    char *nomeIngrediente = NULL;

    while (fread(&ing1, sizeof(ingredientes), 1, pFile))
    {
        if (ing1.codigo == codigo)
        {
            nomeIngrediente = strdup(ing1.nome);
            break;
        }
    }

    fclose(pFile);

    return nomeIngrediente;
}

void listarCardapio()
{
    cardapio cardap;
    FILE *pFile = fopen("cardapio.txt", "r");

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        printf("\nCódigo: %i\n", cardap.codigo);
        printf("Nome: %s\n", cardap.nome);
        printf("Tipo: %s\n", cardap.tipo == 1 ? "Bolo" : cardap.tipo == 2 ? "Doce" : "Sobremesa");
        printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes);

        printf("Ingredientes:\n");

        for (int i = 0; i < cardap.qtdIngredientes; i++)
        {
            int codigoIngrediente = cardap.listaIngredientes[i];
            char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
            printf("  Nome: (%i)%s\n", cardap.listaIngredientes[i], nomeIngrediente);
        }

        printf("\nPreço: %.2f\n", cardap.preco);

        printf("------------------------------------------\n------------------------------------------");
        printf("\n\n");
    }

    fclose(pFile);
}

void pesquisarProdutoCardapio()
{
    cardapio cardap;
    FILE *pFile;
    pFile = fopen("cardapio.txt", "r");

    int codigo, encontrou = 0;
    printf("Insira o codigo do produto: ");
    scanf("%i", &codigo);

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            printf("\nCódigo: %i\n", cardap.codigo);
            printf("Nome: %s\n", cardap.nome);
            printf("Tipo: %s\n", cardap.tipo == 1 ? "Bolo" : cardap.tipo == 2 ? "Doce" : "Sobremesa");
            printf("\nQuantidade de Ingredientes: %i\n", cardap.qtdIngredientes);

            printf("Ingredientes:\n");

            for (int i = 0; i < cardap.qtdIngredientes; i++)
            {
                int codigoIngrediente = cardap.listaIngredientes[i];
                char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
                printf("  Nome: (%i)%s\n", cardap.listaIngredientes[i], nomeIngrediente);
            }

            printf("\nPreço: %.2f\n", cardap.preco);

            printf("------------------------------------------\n------------------------------------------");
            printf("\n\n");
            encontrou=1;
        }
    }
    if (!encontrou) printf("Produto não encontrado!\n");

    fclose(pFile);
}

void atualizarProdutoCardapio()
{
    listarCardapio();

    cardapio cardap;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("cardapio.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do produto a ser atualizado: ");
    scanf("%i", &codigo);

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            encontrou = 1;

            char escolhaAtualizar;

            printf("Deseja atualizar o nome do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            if (escolhaAtualizar == 'S')
            {
                fflush(stdin);
                printf("Insira o novo nome do produto: ");
                scanf("%[^\n]s", cardap.nome);
            }

            printf("Deseja atualizar o tipo do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo tipo do produto (1 - Bolo, 2 - Doce, 3 - Sobremesa): ");
                scanf("%i", &cardap.tipo);
            }

            printf("Deseja atualiza o valor do produto? (S/N): ");
            scanf(" %c", &escolhaAtualizar);
            escolhaAtualizar = toupper(escolhaAtualizar);

            if (escolhaAtualizar == 'S')
            {
                printf("Insira o novo preço do produto: ");
                scanf("%f", &cardap.preco);
            }


            char escolha;
            printf("Deseja adicionar (A) ou deletar (D) ingredientes? (0 para finalizar): ");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);

            while (escolha == 'A' || escolha == 'D')
            {
                if (escolha == 'A')
                {
                    if (cardap.qtdIngredientes < 30)
                    {
                        int codigoIngrediente;
                        listarIngrediente();

                        printf("Insira o código do ingrediente a ser adicionado: ");
                        scanf("%i", &codigoIngrediente);

                        int ingredienteRepetido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                printf("Este ingrediente já foi adicionado ao produto.\n");
                                ingredienteRepetido = 1;
                                break;
                            }
                        }

                        if (!ingredienteRepetido)
                        {
                            cardap.listaIngredientes[cardap.qtdIngredientes] = codigoIngrediente;
                            cardap.qtdIngredientes++;
                        }
                    }
                    else
                    {
                        printf("Lista de ingredientes cheia. Não é possível adicionar mais ingredientes.\n");
                    }
                }
                else if (escolha == 'D')
                {
                    if (cardap.qtdIngredientes > 0)
                    {
                        int codigoIngrediente;
                        listarCardapio();

                        printf("Insira o código do ingrediente a ser deletado: ");
                        scanf("%i", &codigoIngrediente);

                        int ingredienteValido = 0;
                        for (int j = 0; j < cardap.qtdIngredientes; j++)
                        {
                            if (cardap.listaIngredientes[j] == codigoIngrediente)
                            {
                                for (int k = j; k < cardap.qtdIngredientes - 1; k++)
                                {
                                    cardap.listaIngredientes[k] = cardap.listaIngredientes[k + 1];
                                }
                                cardap.qtdIngredientes--;
                                ingredienteValido = 1;
                                printf("Ingrediente removido do produto.\n");
                                break;
                            }
                        }
                        if (!ingredienteValido) printf("Código de ingrediente inválido ou não encontrado no produto.\n");

                    }
                    else printf("O produto não possui ingredientes para deletar.\n");
                }

                printf("Deseja continuar a adicionar (A) ou deletar (D) ingredientes? (A/D/0 para finalizar): ");
                scanf(" %c", &escolha);
                escolha = toupper(escolha);
            }
        }
        fwrite(&cardap, sizeof(cardapio), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("cardapio.txt", "w");

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) fwrite(&cardap, sizeof(cardapio), 1, pFile);

        fclose(pFile);
        fclose(pFile1);
        remove("temp.txt");
    }
    else printf("Produto não encontrado!\n");
}

void deletarProdutoCardapio()
{
    listarCardapio();

    cardapio cardap;
    FILE *pFile;
    FILE *pFile1;
    pFile = fopen("cardapio.txt", "r");
    pFile1 = fopen("temp.txt", "w");

    int codigo, encontrou = 0;
    printf("Insira o código do produto a ser deletado: ");
    scanf("%i", &codigo);

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            encontrou = 1;
            printf("Produto: %s deletado com sucesso!\n", cardap.nome);
        }
        else fwrite(&cardap, sizeof(cardapio), 1, pFile1);
    }

    fclose(pFile);
    fclose(pFile1);

    if (encontrou)
    {
        pFile1 = fopen("temp.txt", "r");
        pFile = fopen("cardapio.txt", "w");

        while (fread(&cardap, sizeof(cardapio), 1, pFile1)) fwrite(&cardap, sizeof(cardapio), 1, pFile);

        fclose(pFile);
        fclose(pFile1);
    }
    else printf("Produto não encontrado!\n");
}

void telaCardapio()
{
    int escolha;

    do
    {
        printf("\nCARDAPIO");
        printf("\n1 - Adicionar Produto no Cardápio");
        printf("\n2 - Listar Cardapio");
        printf("\n3 - Pesquisar Produto");
        printf("\n4 - Atualizar Produto");
        printf("\n5 - Deletar Produto");
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
            char resposta;

            do
            {
                adicionarProdutoCardapio();
                printf("Deseja adicionar mais algum produto(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            break;
        case 2:
            system("cls");
            listarCardapio();
            break;
        case 3:
            system("cls");
            pesquisarProdutoCardapio();
            break;
        case 4:
            system("cls");
            atualizarProdutoCardapio();
            break;
        case 5:
            system("cls");
            deletarProdutoCardapio();
            break;
        default:
            system("cls");
        }
    }
    while (escolha != 0);

    system("cls");
}

// TELA CARDAPIO //

// TELA CARDAPIO //

// TELA VENDAS

int obterProximoCodigoVenda()
{
    FILE *pFile;
    vendas vnd;
    int maiorCodigo = 0;

    pFile = fopen("vendas.txt", "r");

    if (pFile != NULL)
    {
        while (fread(&vnd, sizeof(vendas), 1, pFile) == 1)
        {
            if (vnd.codigo > maiorCodigo) maiorCodigo = vnd.codigo;
        }

        fclose(pFile);
    }

    return maiorCodigo + 1;
}

void novoPedido()
{
    FILE *pFile;
    FILE *pFile1;

    vendas *vnd;
    cardapio cardap;

    int n = 1, i;

    vnd = (vendas *)calloc(n, sizeof(vendas));
    pFile = fopen("vendas.txt", "a");
    pFile1 = fopen("cardapio.txt", "r");

    for (i = 0; i < n; i++)
    {
        vnd[i].codigo = obterProximoCodigoVenda();

        fflush(stdin);
        printf("Insira o nome do cliente: ");
        scanf("%[^\n]s", vnd[i].nomeCliente);

        vnd[i].qtdProdutos = 0;

        listarCardapio();
        while (1)
        {
            int codigoProduto;

            printf("Insira o código do produto a ser adicionado (0 para finalizar): ");
            scanf("%i", &codigoProduto);

            if (codigoProduto == 0) break;

            int produtoExiste = 0;

            rewind(pFile1);
            while (fread(&cardap, sizeof(cardapio), 1, pFile1))
            {
                if (cardap.codigo == codigoProduto)
                {
                    produtoExiste = 1;
                    vnd[i].pedido[vnd[i].qtdProdutos] = codigoProduto;
                    vnd[i].qtdProdutos++;
                    printf("Produto adicionado ao produto.\n");
                    break;
                }
            }

            if (!produtoExiste) printf("Código de produto inexistente. Tente novamente.\n");
        }

        fwrite(&vnd[i], sizeof(vendas), 1, pFile);
    }
    fclose(pFile);
}

cardapio getProdutoPorCodigo(int codigo)
{
    FILE *pFile = fopen("cardapio.txt", "r");
    cardapio cardap;
    cardapio produtoEncontrado;

    while (fread(&cardap, sizeof(cardapio), 1, pFile))
    {
        if (cardap.codigo == codigo)
        {
            produtoEncontrado = cardap;
            break;
        }
    }

    fclose(pFile);

    return produtoEncontrado;
}

void listarVendas()
{
    vendas vnd;

    int escolha;

    do
    {

        FILE *pFile = fopen("vendas.txt", "r");

        while (fread(&vnd, sizeof(vendas), 1, pFile))
        {
            printf("\nCódigo: %i\n", vnd.codigo);
            printf("Cliente: %s\n", vnd.nomeCliente);

            printf("Produtos:\n");

            float valorPedido = 0;

            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto);

                valorPedido += produto.preco;
                printf("  Nome: %s\n", produto.nome);
            }

            printf("\nPreço Total do Pedido: %.2f\n", valorPedido);

            printf("------------------------------------------\n------------------------------------------");
            printf("\n\n");
        }

        printf("\n1 - Detalhar pedido: ");
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

        if(escolha == 1){
            int escolhaPedido;
            do{
                pesquisarPedido();
                printf("\n0 - Voltar: ");
                scanf("%i", &escolhaPedido);
            }while(escolhaPedido != 0);
            system("cls");
        }

        fclose(pFile);

    } while(escolha !=0);

    system("cls");

}

void pesquisarPedido()
{
    vendas vnd;
    FILE *pFile;
    pFile = fopen("vendas.txt", "r");

    int codigo, encontrou = 0;
    printf("Insira o codigo do pedido: ");
    scanf("%i", &codigo);

    while (fread(&vnd, sizeof(vendas), 1, pFile))
    {
        if (vnd.codigo == codigo)
        {
            system("cls");
            printf("\nCódigo do Pedido: %i\n", vnd.codigo);
            printf("Cliente: %s\n\n", vnd.nomeCliente);

            printf("Produtos:\n");

            float valorPedido = 0;

            for (int i = 0; i < vnd.qtdProdutos; i++)
            {
                int codigoProduto = vnd.pedido[i];
                cardapio produto = getProdutoPorCodigo(codigoProduto);

                valorPedido += produto.preco;

                printf("  Nome: %s\n", produto.nome);
                printf("  Tipo: %s\n", (produto.tipo == 1) ? "Bolo" : (produto.tipo == 2) ? "Doce" : "Sobremesa");
                printf("  Preço: %.2f\n\n", produto.preco);

                printf("  Ingredientes:\n");
                for (int j = 0; j < produto.qtdIngredientes; j++)
                {
                    int codigoIngrediente = produto.listaIngredientes[j];
                    char *nomeIngrediente = getNomeIngredientePorCodigo(codigoIngrediente);
                    printf("    %s\n", nomeIngrediente);
                }
                printf("\n  -------------------\n");
                printf("\n");
            }

            printf("Preço Total do Pedido: %.2f\n", valorPedido);

            printf("------------------------------------------");
            printf("\n\n");

            encontrou = 1;
        }
    }
    if (!encontrou) printf("Pedido não encontrado!\n");

    fclose(pFile);
}

void telaVendas()
{
    int escolha;

    do
    {
        printf("\nVENDAS");
        printf("\n1 - Novo Pedido");
        printf("\n2 - Listar Pedidos");
        printf("\n3 - Pesquisar Pedido");
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

        switch(escolha)
        {
        case 1:
            system("cls");
            char resposta;

            do
            {
                novoPedido();
                printf("Deseja adicionar mais algum pedido(S/N)?: ");
                scanf(" %c", &resposta);
                resposta = toupper(resposta);
            }
            while(resposta != 'N');

            break;
        case 2:
            system("cls");
            listarVendas();
            break;
        case 3:
            system("cls");
            pesquisarPedido();
            break;
        default:
            system("cls");
        }
    }
    while(escolha !=0);

    system("cls");
}

// TELA VENDAS //

void barraDeLoading()
{
    system("color 0A");

    char a = 177, b = 219;

    printf("\n\n\n\n");
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t Carregando...\n\n");
    printf("\t\t\t\t\t");

    for (int i = 0; i < 26; i++) printf("%c", a);

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

    setlocale(LC_ALL, "Portuguese");

    int escolha;

    do
    {
        printf("\nBem Vindo\n");
        printf("\n1 - Vendas");
        printf("\n2 - Cardapio");
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
            telaVendas();
            break;
        case 2:
            system("cls");
            telaCardapio();
            break;
        case 3:
            system("cls");
            telaEstoqueIngredientes();
            break;
        default:
            system("cls");
        }
    }
    while (escolha != 0);

    printf("\nVolte sempre!\n");

    return 0;
}
