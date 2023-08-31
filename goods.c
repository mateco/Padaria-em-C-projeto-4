#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "goods.h"
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
typedef struct Produto  // Estrutura para armazenar os dados de um produto
{
    unsigned long long codigo;
    char nome[26];
    float preco;
    int quantidade;
    int Vendas;
    float Subtotal;
    struct Produto* proximo;
} Produto;
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
typedef struct
{
    Produto* produto;
    int quantidade;
    float subtotal;
} ItemCupomFiscal;
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void exibirEstoque(Produto* estoque) // Fun��o para exibir o estoque de produtos
{
    if (estoque == NULL) // Verifica se o estoque est� vazio
    {
        printf("\nEstoque vazio\n");
    }
    else
    {
        printf("| Item (Codigo)\t\t| Nome do item\t\t| Valor (Unidade)\t| Estoque\n");
        Produto* atual = estoque; // Ponteiro para percorrer a lista de produtos

        while (atual != NULL) // Enquanto houver produtos na lista
        {
            printf("| %-10llu\t\t| %-20s\t| R$ %.2f\t\t| %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade);
            atual = atual->proximo; // Move para o pr�ximo produto
        }
    }
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void cadastrarProduto(Produto** estoque)  // Fun��o para cadastrar um novo produto
{
    int quantidadeProdutos;

    printf("Quantos produtos deseja cadastrar? ");
    scanf("%d", &quantidadeProdutos);

    for (int i = 0; i < quantidadeProdutos; i++)
    {
        Produto* novoProduto = (Produto*)malloc(sizeof(Produto));  // Aloca mem�ria para o novo produto
        novoProduto->proximo = NULL;  // Define o pr�ximo como NULL, pois ainda n�o sabemos onde ele ser� inserido

        printf("\nDados do produto %d:\n", i+1);
        printf("C�digo do Item (64 bits): ");
        scanf("%llu", &novoProduto->codigo);

        Produto* atual = *estoque;  // Define o produto atual como o in�cio do estoque

        while (atual != NULL)
        {
            if (atual->codigo == novoProduto->codigo)  // Verifica se o c�digo do novo produto j� existe no estoque
            {
                printf("\nErro!! O c�digo do item j� existe. Digite novamente...\n");
                free(novoProduto);  // Libera a mem�ria alocada para o novo produto
                novoProduto = NULL;  // Define o novo produto como NULL para indicar erro
                break;
            }
            atual = atual->proximo;  // Avan�a para o pr�ximo produto no estoque
        }
        if (novoProduto == NULL)  // Se o novo produto for NULL, houve um erro, ent�o volta para a itera��o anterior
        {
            i--;
            continue;
        }
        printf("Nome do Item (at� 25 caracteres): ");
        scanf(" %s", novoProduto->nome);

        atual = *estoque;

        while (atual != NULL)
        {
            if (strcmp(atual->nome, novoProduto->nome) == 0)  // Verifica se o nome do novo produto j� existe no estoque
            {
                printf("\nErro!! O nome do item j� existe. Digite novamente...\n");
                free(novoProduto);  // Libera a mem�ria alocada para o novo produto
                novoProduto = NULL;  // Define o novo produto como NULL para indicar erro
                break;
            }
            atual = atual->proximo;  // Avan�a para o pr�ximo produto no estoque
        }
        if (novoProduto == NULL)  // Se o novo produto for NULL, houve um erro, ent�o volta para a itera��o anterior
        {
            i--;
            continue;
        }
        if (strlen(novoProduto->nome) == 0 || strlen(novoProduto->nome) > 25)  // Verifica se o nome possui tamanho adequado
        {
            printf("\nErro!! O nome do item deve ter entre 1 e 25 caracteres. Digite novamente...\n");
            free(novoProduto);  // Libera a mem�ria alocada para o novo produto
            i--;
            continue;
        }
        printf("Pre�o Unit�rio do item: ");
        scanf("%f", &novoProduto->preco);

        if (novoProduto->preco < 0)  // Verifica se o pre�o � v�lido (maior ou igual a zero)
        {
            printf("\nErro!! O pre�o deve ser maior ou igual a zero. Digite novamente...\n");
            free(novoProduto);  // Libera a mem�ria alocada para o novo produto
            i--;
            continue;
        }
        printf("Quantidade do item em estoque: ");
        scanf("%d", &novoProduto->quantidade);

        if (novoProduto->quantidade < 0)  // Verifica se a quantidade � v�lida (maior ou igual a zero)
        {
            printf("\nErro!! A quantidade deve ser maior ou igual a zero. Digite novamente...\n");
            free(novoProduto);  // Libera a mem�ria alocada para o novo produto
            i--;
            continue;
        }
        if (*estoque == NULL)  // Se o estoque estiver vazio, insere o novo produto como o primeiro
        {
            *estoque = novoProduto;
        }
        else
        {
            Produto* atual = *estoque;
            while (atual->proximo != NULL)  // Encontra o �ltimo produto no estoque
            {
                atual = atual->proximo;
            }
            atual->proximo = novoProduto;  // Insere o novo produto no final do estoque
        }
        printf("Produto cadastrado com sucesso!\n");
    }
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void atualizarProduto(Produto* estoque) // Fun��o para atualizar um produto do estoque
{
    exibirEstoque(estoque); // Chama a fun��o exibirEstoque para mostrar o estoque atual
    if (estoque == NULL) // Verifica se o estoque est� vazio
    {
        printf("\nEstoque vazio\n");
        return; // Retorna da fun��o
    }

    unsigned long long codigo; // Vari�vel para armazenar o c�digo do produto a ser atualizado

    printf("\n--- Atualizar Produto ---\n");
    printf("Digite o codigo do produto a ser atualizado: ");
    scanf("%llu", &codigo); // L� o c�digo do produto a ser atualizado

    Produto* atual = estoque; // Ponteiro para percorrer a lista de produtos

    while (atual != NULL) // Enquanto houver produtos na lista
    {
        if (atual->codigo == codigo) // Verifica se o c�digo do produto atual � igual ao c�digo digitado
        {
            printf("\nProduto encontrado!\n");
            printf("| Item (Codigo)\t| Nome do item\t\t\t| Valor (Unidade)\t| Estoque\n");
            printf("| %llu\t\t| %-25s\t| R$ %.2f\t\t| %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade);

            float novoPreco; // Vari�vel para armazenar o novo pre�o do produto
            int novaQuantidade; // Vari�vel para armazenar a nova quantidade do produto

            printf("Digite o novo preco unitario do produto: ");
            scanf("%f", &novoPreco); // L� o novo pre�o do produto

            printf("Digite a nova quantidade do produto em estoque: ");
            scanf("%d", &novaQuantidade); // L� a nova quantidade do produto em estoque

            printf("\n Alteracao realizada!\n");
            printf("-----------------------\n");
            printf("Preco anterior: R$ %.2f\n", atual->preco);
            printf("Quantidade anterior: %d\n", atual->quantidade);
            printf("-----------------------\n");
            printf("Preco atualizado: R$ %.2f\n", novoPreco);
            printf("Quantidade atualizada: %d\n", novaQuantidade);
            printf("-----------------------\n");

            atual->preco = novoPreco; // Atualiza o pre�o do produto
            atual->quantidade = novaQuantidade; // Atualiza a quantidade do produto

            return; // Retorna da fun��o ap�s a atualiza��o
        }
        atual = atual->proximo; // Move para o pr�ximo produto
    }
    printf("\nProduto nao encontrado\n");
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void excluirProduto(Produto** estoque)  // Fun��o para excluir os produtos
{
    if (*estoque == NULL) // Verifica se o estoque est� vazio
    {
        printf("\nNenhum produto cadastrado.\n");
        return; // Retorna da fun��o
    }

    Produto* aux = *estoque;    // criando um ponteiro auxiliar para mostrar a lista atual
    exibirEstoque(aux); // Chama a fun��o exibirEstoque para mostrar o estoque atual

    unsigned long long codigo;  // Vari�vel para armazenar o c�digo do produto a ser atualizado
    printf("\nDigite o codigo do produto a ser excluido: ");
    scanf("%llu", &codigo);

    Produto* atual = *estoque;  // Ponteiro para percorrer a lista de produtos
    Produto* anterior = NULL;   // criando um ponteiro com valor vazio

    while (atual != NULL)   // Enquanto houver produtos na lista
    {
        if (atual->codigo == codigo)  // Verifica se o c�digo do produto atual � igual ao c�digo fornecido
        {
            printf("\nProduto encontrado:\n");
            printf("| Item (Codigo)\t| Nome do item\t\t\t| Valor (Unidade)\t| Estoque\n");
            printf("| %llu\t\t| %-25s\t| R$ %.2f\t\t| %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade);

            printf("\nDeseja realmente excluir o produto? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);

            if (resposta == 'S' || resposta == 's')  // Se a resposta for 'S' ou 's', o produto ser� exclu�do
            {
                if (anterior == NULL)  // Se o produto a ser exclu�do for o primeiro da lista
                {
                    *estoque = atual->proximo;  // O ponteiro de estoque apontar� para o pr�ximo produto
                }
                else
                {
                    anterior->proximo = atual->proximo;  // O produto anterior ter� seu ponteiro pr�ximo atualizado para pular o produto atual
                }
                free(atual);  // Libera a mem�ria alocada para o produto atual
                printf("\nProduto excluido com sucesso.\n");
            }
            else
            {
                printf("\nExclusao cancelada.\n");
            }
            return;
        }
        anterior = atual;  // Atualiza o ponteiro anterior para apontar para o produto atual
        atual = atual->proximo;  // Avan�a para o pr�ximo produto na lista
    }
    printf("\nProduto nao encontrado.\n");
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void salvarProdutos(Produto* estoque)   // Fun��o para salvar os produtos em um arquivo
{
    FILE* arquivo = fopen("produtos.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return; // Retorna da fun��o
    }

    Produto* atual = estoque; // Ponteiro para percorrer a lista de produtos

    while (atual != NULL) // Enquanto houver produtos na lista
    {
        fprintf(arquivo, "%llu\n", atual->codigo); // Escreve o c�digo do produto no arquivo
        fprintf(arquivo, "%s\n", atual->nome); // Escreve o nome do produto no arquivo
        fprintf(arquivo, "%.2f\n", atual->preco); // Escreve o pre�o do produto no arquivo
        fprintf(arquivo, "%d\n", atual->quantidade); // Escreve a quantidade do produto no arquivo
        fprintf(arquivo, "%d\n", atual->Vendas); // Escreve as vendas do produto no arquivo
        atual = atual->proximo; // Move para o pr�ximo produto
    }

    fclose(arquivo);    // Fecha o arquivo
    printf("\nProdutos salvos com sucesso\n");
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void lerProdutos(Produto** estoque) // Fun��o para ler os produtos de um arquivo e carreg�-los na mem�ria
{
    FILE* arquivo = fopen("produtos.txt", "r"); // Abre o arquivo "produtos.txt" em modo de leitura
    if (arquivo == NULL)    // Verifica se houve erro ao abrir o arquivo
    {
        printf("Erro ao abrir o arquivo\n");
        return; // Retorna da fun��o
    }

    Produto* atual = *estoque;// Ponteiro para percorrer a lista atual de produtos

    // Limpar a lista atual de produtos
    while (atual != NULL)// Enquanto houver produtos na lista
    {
        Produto* proximo = atual->proximo; // Armazena o pr�ximo produto
        free(atual); // Libera a mem�ria ocupada pelo produto atual
        atual = proximo; // Move para o pr�ximo produto
    }
    *estoque = NULL;    // Define o estoque como vazio (NULL)

    unsigned long long codigo; // Vari�vel para armazenar o c�digo do produto
    char nome[26]; // Vari�vel para armazenar o nome do produto
    float preco; // Vari�vel para armazenar o pre�o do produto
    int quantidade; // Vari�vel para armazenar a quantidade do produto
    int Vendas; // Vari�vel para armazenar as vendas do produto

    while (fscanf(arquivo, "%llu\n", &codigo) == 1) // L� o c�digo do produto do arquivo
    {
        fgets(nome, sizeof(nome), arquivo); // L� o nome do produto do arquivo
        nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha do nome
        fscanf(arquivo, "%f\n", &preco); // L� o pre�o do produto do arquivo
        fscanf(arquivo, "%d\n", &quantidade); // L� a quantidade do produto do arquivo
        fscanf(arquivo, "%d\n", &Vendas); // L� as vendas do produto do arquivo

        Produto* novoProduto = (Produto*)malloc(sizeof(Produto)); // Aloca mem�ria para o novo produto
        novoProduto->codigo = codigo; // Atribui o c�digo do produto
        strcpy(novoProduto->nome, nome); // Copia o nome do produto
        novoProduto->preco = preco; // Atribui o pre�o do produto
        novoProduto->quantidade = quantidade; // Atribui a quantidade do produto
        novoProduto->Vendas = Vendas; // Atribui as vendas do produto
        novoProduto->proximo = NULL; // Define o pr�ximo do novo produto como NULL

        if (*estoque == NULL)   // Se o estoque estiver vazio
        {
            *estoque = novoProduto; // Define o estoque como o novo produto
        }
        else
        {
            atual = *estoque; // Define o ponteiro atual como o in�cio do estoque
            while (atual->proximo != NULL) // Enquanto n�o chegar ao final do estoque
            {
                atual = atual->proximo; // Move para o pr�ximo produto
            }
            atual->proximo = novoProduto;   // Define o pr�ximo do produto atual como o novo produto
        }
    }
    fclose(arquivo);    // Fecha o arquivo
    printf("\nProdutos carregados com sucesso\n");
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void Produtos()
{
    Produto* estoque = NULL;  // Cria um ponteiro para o estoque de produtos e o inicializa como NULL
    int opc;  // Vari�vel para armazenar a op��o escolhida pelo usu�rio
    lerProdutos(&estoque);

    do
    {
        printf("\n---- MENU PRODUTOS ----\n");
        printf("1. Exibir\n");
        printf("2. Cadastrar\n");
        printf("3. Atualizar\n");
        printf("4. Excluir\n");
        printf("5. Salvar\n");
        printf("6. Ler\n");
        printf("7. Voltar\n");
        printf("------------------------\n");

        scanf("%d", &opc);  // L� a op��o escolhida pelo usu�rio
        getchar();  // L� o caractere de nova linha residual

        switch (opc)
        {
        case 1:
            exibirEstoque(estoque);  // Chama a fun��o exibirEstoque passando o ponteiro para o estoque como argumento
            break;
        case 2:
            cadastrarProduto(&estoque);  // Chama a fun��o cadastrarProduto passando o endere�o do ponteiro para o estoque como argumento
            break;
        case 3:
            atualizarProduto(estoque);  // Chama a fun��o atualizarProduto passando o ponteiro para o estoque como argumento
            break;
        case 4:
            excluirProduto(&estoque);  // Chama a fun��o excluirProduto passando o endere�o do ponteiro para o estoque como argumento
            break;
        case 5:
            salvarProdutos(estoque);  // Chama a fun��o salvarProdutos passando o ponteiro para o estoque como argumento
            break;
        case 6:
            lerProdutos(&estoque);  // Chama a fun��o lerProdutos passando o endere�o do ponteiro para o estoque como argumento
            break;
        case 7:
            printf("\nVoltando para o menu principal...\n");
            return;  // Retorna da fun��o para voltar ao menu principal
        default:
            printf("\nOp��o inv�lida! Digite novamente.\n");
            break;
        }
    }
    while (opc < 1 || opc > 7 || opc != 7);  // Repete o loop enquanto a op��o escolhida for inv�lida ou diferente de 7
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void Realizar_Venda(Produto** estoque)
{
    unsigned long long codigo;
    char resposta;
    int quantidade, tamanhoCupom = 0, opcPagamento, NumParcelas;;
    float total = 0; // Vari�vel para calcular o total das vendas

    ItemCupomFiscal cupomFiscal[100]; // Vetor para armazenar os produtos do cupom fiscal

    if(*estoque == NULL)
    {
        printf("\nNenhum produto cadastrado. Cadastre produtos antes de realizar uma venda.\n");
        return;
    }

    do
    {
        exibirEstoque(*estoque);

        printf("Digite o codigo do produto a ser vendido: ");
        scanf("%llu", &codigo);

        Produto* atual = *estoque;
        while(atual != NULL)
        {
            if(atual->codigo == codigo)
            {
                printf("\nProduto encontrado!\n");
                printf("| Item (Codigo)\t| Nome do item\t\t\t| Valor (Unidade)\t| Estoque\n");
                printf("| %llu\t\t| %-25s\t| R$ %.2f\t\t| %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade);

                printf("Digite a quantidade a ser vendida: ");
                scanf("%d", &quantidade);

                if(quantidade <= 0 || quantidade > atual->quantidade)
                {
                    printf("\nQuantidade inv�lida ou insuficiente.\n");
                    break;
                }
                float subtotal = quantidade * atual->preco;
                atual->quantidade -= quantidade;
                atual->Vendas += quantidade;
                atual->Subtotal += subtotal;

                ItemCupomFiscal item;
                item.produto = atual;
                item.quantidade = quantidade;
                item.subtotal = subtotal;

                cupomFiscal[tamanhoCupom] = item;
                tamanhoCupom++;

                total += subtotal;

                break;
            }
            atual = atual->proximo;
        }
        if (atual == NULL)
        {
            printf("\nProduto nao encontrado\n");
        }
        printf("\nDeseja realizar outra venda? (s/n): ");
        scanf(" %c", &resposta);
    }
    while (resposta == 's' || resposta == 'S');

    Produto** CupomFiscal = (Produto**)malloc(tamanhoCupom * sizeof(Produto*));    // Cria��o do vetor do cupom fiscal
    if (CupomFiscal == NULL)
    {
        printf("\nErro de aloca��o de mem�ria\n");
        return;
    }
    for(int i = 0; i < tamanhoCupom - 1; i ++)
    {
        for(int j = 0; j < tamanhoCupom - i - 1; j++)
        {
            if(cupomFiscal[j].subtotal < cupomFiscal[j+1].subtotal)
            {
                ItemCupomFiscal temp = cupomFiscal[j];
                cupomFiscal[j] = cupomFiscal[j+1];
                cupomFiscal[j+1] = temp;
            }
        }
    }
    printf("\nCupom Fiscal:\n");
    printf("| Item\t\t| Nome do Item\t\t| Valor Unit. (R$)\t| Quant.\t| Sub-Total (R$)\n");

    for (int i = 0; i < tamanhoCupom; i++)
    {
        printf("| %d\t\t| %-20s\t| R$ %.2f\t\t| %d\t\t| R$ %.2f\n", i + 1, cupomFiscal[i].produto->nome, cupomFiscal[i].produto->preco, cupomFiscal[i].quantidade, cupomFiscal[i].subtotal);
    }
    printf("\nTotal: R$ %.2f\n", total);

    int opc_pag, opc_troco, Num_Parcelas;
    float Valor_total, Desconto, Acrescimo, Valor_Parcelas, Troco, Saldo;

    Valor_total = total;

    printf("\nSelecione a forma de pagamento:\n1. A vista\n2. A prazo\n3. Voltar ao menu de vendas(caso nao haja compra no cupom fiscal):\n");
    do
    {
        scanf("%d", &opc_pag);
        if (opc_pag < 1 || opc_pag > 3)
        {
            printf("\nOpcao de pagamento invalida, digite novamente\n");
        }
    }
    while (opc_pag < 1 || opc_pag > 3);

    if (opc_pag == 1)
    {
        if (Valor_total <= 50)
        {
            Desconto = Valor_total * 0.05; // se menor que R$ 50 = 5% de desconto
            Valor_total -= Desconto;
        }
        else if (Valor_total < 100)
        {
            Desconto = Valor_total * 0.1; // se maior que R$ 50 e menor que R$ 100 = 10% de desconto
            Valor_total -= Desconto;
        }
        else
        {
            Desconto = Valor_total * 0.18; // caso contr�rio, se maior que R$ 100 = 18% de desconto
            Valor_total -= Desconto;
        }

        printf("\nPagamento a vista selecionado, precisa de troco?\n1.Sim\n2.Nao\n");
        do
        {
            scanf("%d", &opc_troco);
            if (opc_troco < 1 || opc_troco > 2)
            {
                printf("Opcao invalida, digite novamente: \n");
            }
        }
        while (opc_troco < 1 || opc_troco > 2);

        if (opc_troco == 1)
        {
            printf("Informe o valor de seu saldo: ");
            scanf("%f", &Saldo);

            while (Saldo < Valor_total)
            {
                printf("Saldo insuficiente, tente novamente\n");
                scanf("%f", &Saldo);
            }
            Troco = Saldo - Valor_total; // calculo do troco
            printf("Troco: R$ %.2f\n", Troco);
            printf("Desconto de: R$ %.2f\n", Desconto);
        }
    }
    else if (opc_pag == 2)
    {
        printf("\nValor total da compra: R$ %.2f\n", Valor_total);
        printf("Digite o numero de parcelas: ");
        scanf("%d", &Num_Parcelas);

        while (Num_Parcelas <= 0)
        {
            printf("Numero de parcelas invalido, digite um valor igual ou acima de 1 parcela.\n");
            scanf("%d", &Num_Parcelas);
        }
        if (Num_Parcelas > 3) // Se numero de parcelas maior que 3 = 8% de acr�scimo
        {
            Acrescimo = Valor_total * 0.08;
            Valor_total += Acrescimo;
        }
        else
        {
            Acrescimo = Valor_total * 0.05; // Caso contr�rio, se for 1 ou 2 = 5% de acr�scimo
            Valor_total += Acrescimo;
        }
        Valor_Parcelas = Valor_total / Num_Parcelas;
        printf("\n%dx parcelas de: R$ %.2f\n", Num_Parcelas, Valor_Parcelas);
        printf("Acrescimo de: R$ %.2f\n", Acrescimo);
    }
    printf("\n");
    free(CupomFiscal);
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void Relatorio_Vendas(Produto* estoque)
{
    if (estoque == NULL)
    {
        printf("\nEstoque vazio\n");
        return;
    }
    printf("| Item (Codigo)\t| Nome do item\t\t\t| Valor (Unidade)\t| Estoque\t| Vendidos\n");

    Produto* atual = estoque;
    while (atual != NULL)
    {
        printf("| %llu\t\t| %-25s\t| R$ %.2f\t\t| %d\t\t| %d\n", atual->codigo, atual->nome, atual->preco, atual->quantidade, atual->Vendas);
        atual = atual->proximo;
    }
    salvarProdutos(estoque);
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
void Vendas()
{
    Produto* estoque = NULL;  // Cria um ponteiro para o estoque de produtos e o inicializa como NULL
    int opc;
    lerProdutos(&estoque);

    do
    {
        printf("---- MENU ----\n");
        printf("1. Realizar venda\n");
        printf("2. Relatorio de vendas\n");
        printf("3. Voltar\n");
        printf("--------------\n");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            Realizar_Venda(&estoque);
            break;
        case 2:
            Relatorio_Vendas(estoque);
            break;
        case 3:
            printf("\nVoltando para o menu principal...\n");
            return;  // Retorna da fun��o para voltar ao menu principal
        default:
            printf("Opcao invalida, digite novamente!\n");
            break;
        }
    }
    while (opc < 1 || opc > 3 || opc != 3);
}
// MWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMWMMWMWMMWMWWMMWMWMWMWMWWMWMWMWMMWWMWMWMWMWMWMWMWMWMWM//
