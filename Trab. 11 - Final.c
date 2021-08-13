//Criar um sistema que permite o controle de estoque de produtos e o registro de vendas. O cadastro de produtos deve ter pelo menos os seguintes campos: nome, código, preço, estoque. O registro de vendas deve ter as seguintes informações: código do prod., quantidade, data.

//O usuário deve ser capaz de cadastrar produtos (e possivelmente editar e eliminar) e registrar vendas (quando existe o produto em estoque).

//O sistema deve gerar os seguintes relatórios:

//vendas realizadas em determinado mês.
//vendas de um determinado produto (através do código do produto).
//ranking de produtos mais vendidos
//Os dados devem ser armazenados em arquivos para que sejam mantidos mesmo após encerrar a execução do programa. Eles devem ser recuperados se o programa for executado novamente. Os trabalhos são individuais e devem ser enviados pelo sistema Run Codes (sem casos de teste).

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    char nome_produto[100];
    int codigo_produto;
    float preco_produto;
    int estoque_produto;
}produtos_cadastro;

typedef struct {
    int codigo_venda;
    int codigo_produto_venda;
    char nome_produto_venda[100];
    int quantidade_produto;
    float preco_venda_unitario;
    int dia;
    int mes;
    int ano;
    int h;
    int m;
    int s;
}registro_vendas;

//Conjunto de funções
int opcoes_menu ();
int opcoes_menu_vendas ();
int menu_relatorio ();
void cadastro_produto (produtos_cadastro *buffer);
void posicao_vazia (int *posicao_livre, int tamanho_do_banco, produtos_cadastro *buffer);
void posicao_vazia_vendas (int *posicao_livre_venda, int tamanho_do_banco_venda, registro_vendas *buffer_vendas);
void procura_produto (int tamanho_do_banco, produtos_cadastro *buffer);
void editar_produto (int tamanho_do_banco, produtos_cadastro *buffer);
void excluir_produto (int tamanho_do_banco, produtos_cadastro *buffer);
void registrar_venda (int tamanho_do_banco, produtos_cadastro *buffer, int tamanho_do_banco_vendas, registro_vendas *buffer_vendas, registro_vendas *vendas, struct tm *tm, time_t t);
void relatorios_vendas (int tamanho_do_banco, produtos_cadastro *buffer, int tamanho_do_banco_vendas, registro_vendas *buffer_vendas);

int main (){
    setlocale(LC_ALL, "Portuguese");
    int *posicao_livre, *posicao_livre_venda, pos_livre=0, pos_livre_venda=0, tamanho_do_banco=100, tamanho_do_banco_vendas=100, prog_rodando=1;
    posicao_livre = &pos_livre;
    posicao_livre_venda = &pos_livre_venda;
    FILE *arq_produtos, *arq_produtos_vendas;
    produtos_cadastro *buffer = (produtos_cadastro *) calloc (tamanho_do_banco, sizeof(produtos_cadastro));
    registro_vendas *buffer_vendas = (registro_vendas *) calloc (tamanho_do_banco_vendas, sizeof(registro_vendas));
    if((arq_produtos=fopen("Ex. Trabalho 11_Final.txt", "rb+")) == NULL){
        if((arq_produtos=fopen("Ex. Trabalho 11_Final.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo.\n");
            return 0;
        }
    }
    fseek(arq_produtos, 0, SEEK_SET);
    fread(buffer, sizeof(produtos_cadastro), tamanho_do_banco, arq_produtos);
    fclose(arq_produtos);
    if((arq_produtos_vendas=fopen("Ex. Trabalho 11_Final-Vendas.txt", "rb+")) == NULL){
        if((arq_produtos_vendas=fopen("Ex. Trabalho 11_Final-Vendas.txt", "wb+")) == NULL){
            printf("\nErro ao abrir o arquivo.\n");
            return 0;
        }
    }
    fseek(arq_produtos_vendas, 0, SEEK_SET);
    fread(buffer_vendas, sizeof(registro_vendas), tamanho_do_banco_vendas, arq_produtos_vendas);
    fclose(arq_produtos_vendas);
    time_t t;
    struct tm *tm;
    while(prog_rodando){
        system("cls || clear");
        switch(opcoes_menu()){

            case 0:
                system("cls || clear");
                printf("\n Obrigado por utilizar o programa de Ivan Pinheiro!\n");
                printf("\n Programa encerrado!\n");
                prog_rodando = 0;
                break;

            case 1:
                system("cls || clear");
                posicao_vazia (posicao_livre, tamanho_do_banco, buffer);
                cadastro_produto (&buffer[*posicao_livre]);
                break;

            case 2:
                system("cls || clear");
                editar_produto (tamanho_do_banco, buffer);
                break;

            case 3:
                system("cls || clear");
                procura_produto (tamanho_do_banco, buffer);
                break;

            case 4:
                system("cls || clear");
                excluir_produto (tamanho_do_banco, buffer);
                break;

            case 5:
                system("cls || clear");
                posicao_vazia_vendas (posicao_livre_venda, tamanho_do_banco_vendas, buffer_vendas);
                registrar_venda(tamanho_do_banco, buffer, tamanho_do_banco_vendas, &buffer_vendas[*posicao_livre_venda], buffer_vendas, tm, t);
                break;

            case 6:
                system("cls || clear");
                relatorios_vendas (tamanho_do_banco, buffer, tamanho_do_banco_vendas, buffer_vendas);
                break;

            default:
                system("cls || clear");
                printf(" Número inválido!\n");
                break;
        }
        if((arq_produtos=fopen("Ex. Trabalho 11_Final.txt", "wb+")) == NULL){
            printf("\n Erro ao abrir o arquivo.\n");
            return 0;
        }
        fseek(arq_produtos, 0, SEEK_SET);
        fwrite(buffer, sizeof(produtos_cadastro), tamanho_do_banco, arq_produtos);
        fclose(arq_produtos);
        if((arq_produtos_vendas=fopen("Ex. Trabalho 11_Final-Vendas.txt", "wb+")) == NULL){
            printf("\n Erro ao abrir o arquivo.\n");
            return 0;
        }
        fseek(arq_produtos_vendas, 0, SEEK_SET);
        fwrite(buffer_vendas, sizeof(registro_vendas), tamanho_do_banco_vendas, arq_produtos_vendas);
        fclose(arq_produtos_vendas);
    }
    fflush(arq_produtos);
    fflush(arq_produtos_vendas);
    free(buffer);
    free(buffer_vendas);
    return 0;
}

int opcoes_menu (){
    int opcao;
    printf("\n Digite a opção desejada!\n");
    printf("\n 1 - Cadastrar produto;\n");
    printf(" 2 - Editar um cadastro de produto;\n");
    printf(" 3 - Procurar um produto;\n");
    printf(" 4 - Eliminar um cadastro de produto;\n");
    printf(" 5 - Registrar uma venda;\n");
    printf(" 6 - Relatórios e edição de vendas;\n");
    printf(" 0 - Fechar o programa.\n");
    scanf("%d", &opcao);
    return opcao;
}

int opcoes_menu_vendas (){
    int opcao;
    printf("\n Digite a opção desejada!\n");
    printf("\n 1 - Registrar venda pelo codigo do produto;\n");
    printf(" 2 - Procurar codigo do produto;\n");
    printf(" 3 - Listar todas vendas;\n");
    printf(" 0 - Fechar menu.\n");
    scanf("%d", &opcao);
    return opcao;
}

int menu_relatorio (){
    int opcao;
    printf("\n Digite a opção desejada!\n");
    printf("\n 1 - Vendas realizadas em determinado mês;\n");
    printf(" 2 - Vendas de um determinado produto;\n");
    printf(" 3 - Ranking de produtos mais vendidos;\n");
    printf(" 4 - Listar todas vendas;\n");
    printf(" 5 - Procurar pelo produto;\n");
    printf(" 6 - Editar um cadastro de venda;\n");
    printf(" 0 - Fechar menu.\n");
    scanf("%d", &opcao);
    return opcao;
}

void cadastro_produto (produtos_cadastro *buffer){
    if (buffer->codigo_produto==0){
        printf("\n Digite o nome do produto:\n");
        setbuf(stdin, 0);
        fgets(buffer->nome_produto, 99, stdin);
        buffer->nome_produto[strcspn(buffer->nome_produto, "\n")] = 0;
        printf("\n Digite o codigo do produto (exceto zero!):\n");
        scanf("%i", &buffer->codigo_produto);
        printf("\n Digite o preço do produto:\n");
        scanf("%f", &buffer->preco_produto);
        printf("\n Digite a quantidade em estoque:\n");
        scanf("%i", &buffer->estoque_produto);
    }
}

void posicao_vazia (int *posicao_livre, int tamanho_do_banco, produtos_cadastro *buffer){
    for(int i=0; i<tamanho_do_banco; i++){
        if(buffer[i].codigo_produto==0){
            *posicao_livre=i;
            break;
        }
    }
}

void posicao_vazia_vendas (int *posicao_livre_venda, int tamanho_do_banco_venda, registro_vendas *buffer_vendas){
    for(int i=0; i<tamanho_do_banco_venda; i++){
        if(buffer_vendas[i].codigo_produto_venda==0){
            *posicao_livre_venda=i;
            break;
        }
    }
}

void procura_produto (int tamanho_do_banco, produtos_cadastro *buffer){
    int modo_busca=0, realizar_busca = 1, aux_busca=0, aux_busca2=0, codigo_produto=0;
    char nome[100];
    while(realizar_busca==1){
        while(modo_busca<1 || modo_busca>3){
            printf("\n Digite o modo de busca de produtos!\n");
            printf("\n 1 - Procurar por nome;\n");
            printf(" 2 - Procurar por código;\n");
            printf(" 3 - Listar todos produtos;\n");
            printf(" 0 - Fechar menu.\n");
            scanf("%i", &modo_busca);
            if(modo_busca<0 || modo_busca>3){
                printf("\nNUMERO INVALIDO!!!\n");

            }
            if(modo_busca == 0){
                break;
            }
        }
        if(modo_busca == 0){
            break;
        }
        if(modo_busca == 1){
            system("cls || clear");
            printf("\n Digite o nome do produto: \n");
            setbuf(stdin, 0);
            fgets(nome, 99, stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("\n |  Nome  |  Código do produto  |  Preço  |  Estoque  |\n\n");
            for(int i=0; i<tamanho_do_banco; i++){
                if(strcmp(nome, buffer[i].nome_produto) == 0){
                    printf("   %s", buffer[i].nome_produto);
                    printf("           %i", buffer[i].codigo_produto);
                    printf("                 R$%0.2f", buffer[i].preco_produto);
                    printf("       %i", buffer[i].estoque_produto);
                    aux_busca++;
                    realizar_busca=3;
                }
                if(i == (tamanho_do_banco-1) && aux_busca==0){
                        aux_busca2=1;
                }
            }
            if(aux_busca2 ==1 ){
                printf("\n\n NÃO FOI POSSÍVEL ENCONTRAR O PRODUTO!!!\n\n");
                realizar_busca=3;
            }

        }
        if(modo_busca == 2){
            system("cls || clear");
            printf("\n Digite o código do produto: \n");
            scanf("%i", &codigo_produto);
            printf("\n |  Nome  |  Código do produto  |  Preço  |  Estoque  |\n\n");
            for(int i=0; i<tamanho_do_banco; i++){
                if(buffer[i].codigo_produto == codigo_produto){
                    printf("   %s", buffer[i].nome_produto);
                    printf("           %i", buffer[i].codigo_produto);
                    printf("                 R$%0.2f", buffer[i].preco_produto);
                    printf("       %i", buffer[i].estoque_produto);
                    aux_busca++;
                    realizar_busca=3;
                }
                if(i == (tamanho_do_banco-1) && aux_busca==0){
                    aux_busca2=1;
                }
            }
            if(aux_busca2==1){
                printf("\n\n NÃO FOI POSSÍVEL ENCONTRAR O PRODUTO!!!\n\n");
                realizar_busca=3;
            }
        }
        if(modo_busca == 3){
            system("cls || clear");
            printf("\n |  Nome  |  Código do produto  |  Preço  |  Estoque  |\n\n");
            for(int i=0; i<(tamanho_do_banco); i++){
                if(buffer[i].codigo_produto != 0){
                    printf("   %s", buffer[i].nome_produto);
                    printf("           %i", buffer[i].codigo_produto);
                    printf("                 R$%0.2f", buffer[i].preco_produto);
                    printf("       %i\n\n", buffer[i].estoque_produto);
                    aux_busca++;
                    realizar_busca = 3;
                }
                if(i == (tamanho_do_banco-1) && aux_busca==0){
                    aux_busca2 = 1;
                    break;
                }
            }
            if(aux_busca2==1){
                printf("\n\n NÃO FOI POSSÍVEL ENCONTRAR O PRODUTO!!!\n\n");
                realizar_busca=3;
            }
        }
        if(realizar_busca == 3){
            modo_busca = 0;
            aux_busca = 0;
            aux_busca2 = 0;
            while (realizar_busca<1 || realizar_busca>2){
                printf("\n\n Deseja realizar mais uma busca?\n");
                printf("\n 1 - Sim;\n");
                printf("\n 2 - Nao.\n");
                scanf("%i", &realizar_busca);
                if(realizar_busca==2){
                    break;
                }
                if(realizar_busca<1 || realizar_busca>2){
                    printf("\n NÚMERO INVÁLIDO!!!\n");
                }
            }
        }
    }
}

void editar_produto (int tamanho_do_banco, produtos_cadastro *buffer){
    int procura_cadastro=0, aux_procura=0, alterar_cadastro=0, confirma_alteracao=0, continuar=0;
    printf("\n Qual produto deseja alterar?\n");
    scanf("%i", &procura_cadastro);
    for (int i=0; i<tamanho_do_banco; i++){
        if(buffer[i].codigo_produto==procura_cadastro){
            alterar_cadastro=i;
            break;
        }
        if (i==99){
            aux_procura=1;
        }
    }
    while(aux_procura==1){
        system("cls || clear");
        printf("\n\n CADASTRO NÃO ENCONTRADO!!!\n\n");
        continuar=0;
        printf("\n Deseja prosseguir?\n");
        while (continuar<1 || continuar>2){
            printf(" 1 - Sim;");
            printf("\n 2 - Não.\n");
            scanf("%i", &continuar);
            if(continuar==2){
                break;
            }
        }
        if(continuar==2){
            break;
        }
        printf("\n Qual produto deseja alterar?\n");
        scanf("%i", &procura_cadastro);
        for (int i=0; i<tamanho_do_banco; i++){
            if(buffer[i].codigo_produto==procura_cadastro){
                alterar_cadastro=i;
                aux_procura=0;
                break;
            }
        }
    }
    if(continuar!=2){
        system("cls || clear");
        printf("\n Nome do produto: %s", buffer[alterar_cadastro].nome_produto);
        printf("\n Código do produto: %i", buffer[alterar_cadastro].codigo_produto);
        printf("\n Preço do produto: R$%0.2f", buffer[alterar_cadastro].preco_produto);
        printf("\n Estoque do produto: %i\n", buffer[alterar_cadastro].estoque_produto);
        printf("\n Tem certeza que deseja alterar o cadastro número: %i?\n", procura_cadastro);
        printf("\n 1 - Sim;");
        printf("\n 2 - Nao.\n");
        scanf("%i", &confirma_alteracao);
        while (confirma_alteracao<1 || confirma_alteracao>2){
            printf("\n NUMERO INVALIDO!!!\n\n");
            printf("\n Tem certeza que deseja alterar o cadastro número: %i?\n", procura_cadastro);
            printf("\n 1 - Sim;");
            printf("\n 2 - Nao.\n");
            scanf("%i", &confirma_alteracao);
            if (confirma_alteracao==2){
                break;
            }
        }
        if (confirma_alteracao==1){
            system("cls || clear");
            printf("\n Nome do produto: %s", buffer[alterar_cadastro].nome_produto);
            printf("\n Código do produto: %i", buffer[alterar_cadastro].codigo_produto);
            printf("\n Preço do produto: R$%0.2f", buffer[alterar_cadastro].preco_produto);
            printf("\n Estoque do produto: %i", buffer[alterar_cadastro].estoque_produto);
            printf("\n\n Digite o nome do produto:\n");
            setbuf(stdin, 0);
            fgets(buffer[alterar_cadastro].nome_produto, 99, stdin);
            buffer[alterar_cadastro].nome_produto[strcspn(buffer[alterar_cadastro].nome_produto, "\n")] = 0;
            printf("\n Digite o codigo do produto (exceto zero!):\n");
            scanf("%i", &buffer[alterar_cadastro].codigo_produto);
            printf("\n Digite o preço do produto:\n");
            scanf("%f", &buffer[alterar_cadastro].preco_produto);
            printf("\n Digite a quantidade em estoque:\n");
            scanf("%i", &buffer[alterar_cadastro].estoque_produto);
        }
    }
}

void excluir_produto (int tamanho_do_banco, produtos_cadastro *buffer){
    int procura_cadastro=0, aux_procura=0, excluir_cadastro=0, confirma_alteracao=0, continuar=0;
    printf("\nQual produto deseja excluir?\n");
    scanf("%i", &procura_cadastro);
    for (int i=0; i<tamanho_do_banco; i++){
        if(buffer[i].codigo_produto==procura_cadastro){
            excluir_cadastro=i;
            break;
        }
        if (i==99){
            aux_procura=1;
        }
    }
    while(aux_procura==1){
        system("cls || clear");
        printf("\n\nCADASTRO NÃO ENCONTRADO!!!\n\n");
        continuar=0;
        printf("\nDeseja prosseguir?\n");
        while (continuar<1 || continuar>2){
            printf("1 - Sim;");
            printf("\n2 - Não.\n");
            scanf("%i", &continuar);
            if(continuar==2){
                break;
            }
        }
        if(continuar==2){
            break;
        }
        printf("\nQual produto deseja alterar\n");
        scanf("%i", &procura_cadastro);
        for (int i=0; i<tamanho_do_banco; i++){
            if(buffer[i].codigo_produto==procura_cadastro){
                excluir_cadastro=i;
                aux_procura=0;
                break;
            }
        }
    }
    if(continuar!=2){
        system("cls || clear");
        printf("\n Código do produto: %i", buffer[excluir_cadastro].codigo_produto);
        printf("\n Nome do produto: %s", buffer[excluir_cadastro].nome_produto);
        printf("\n Estoque do produto: %i", buffer[excluir_cadastro].estoque_produto);
        printf("\n Preço do produto: %0.2f\n", buffer[excluir_cadastro].preco_produto);
        printf("\n Tem certeza que deseja alterar o cadastro número: %i?\n", procura_cadastro);
        printf("\n 1 - Sim;");
        printf("\n 2 - Nao.\n");
        scanf("%i", &confirma_alteracao);
        while (confirma_alteracao<1 || confirma_alteracao>2){
            printf("\n NUMERO INVALIDO!!!\n\n");
            printf("\n Tem certeza que deseja alterar o cadastro número: %i?\n", procura_cadastro);
            printf("\n 1 - Sim;");
            printf("\n 2 - Nao.\n");
            scanf("%i", &confirma_alteracao);
            if (confirma_alteracao==2){
                break;
            }
        }
        if (confirma_alteracao==1){
            for(int j=0; j<strlen(buffer[excluir_cadastro].nome_produto); j++){
                buffer[excluir_cadastro].nome_produto[j] = 0;
            }
            buffer[excluir_cadastro].codigo_produto = 0;
            buffer[excluir_cadastro].preco_produto = 0;
            buffer[excluir_cadastro].estoque_produto = 0;
        }
    }
}

void registrar_venda (int tamanho_do_banco, produtos_cadastro *buffer, int tamanho_do_banco_vendas, registro_vendas *buffer_vendas, registro_vendas *vendas,  struct tm *tm, time_t t){
    int menu_vendas_rodando = 1, codigo_lido = 0, posicao_produto_venda = 0,
    aux_busca_produto = 0, aux_busca_produto2 = 0, quantidade_vendida = 0, continuar = 0, codigo_venda = 0, codigo_livre = 1;
    time(&t);
    tm = gmtime(&t);
    while(menu_vendas_rodando){
        switch(opcoes_menu_vendas()){
            case 0:
                system("cls || clear");
                menu_vendas_rodando = 0;
                break;
            case 1:
                while(codigo_lido==0){
                    codigo_lido = 0;
                    aux_busca_produto = 0;
                    aux_busca_produto2 = 0;
                    printf("\n Digite o código do produto!\n");
                    scanf("%i", &codigo_lido);
                    for(int i=0; i<tamanho_do_banco; i++){
                        if(buffer[i].codigo_produto == codigo_lido){
                            codigo_lido = buffer[i].codigo_produto;
                            posicao_produto_venda = i;
                            aux_busca_produto++;
                            break;
                        }
                        if(i == (tamanho_do_banco-1) && aux_busca_produto == 0){
                            aux_busca_produto2 = 1;
                        }
                    }
                    if(aux_busca_produto2 == 1){
                        system("cls || clear");
                        printf("\n\n NÃO FOI POSSÍVEL ENCONTRAR O PRODUTO!!!\n\n");
                        codigo_lido = 0;
                        continuar = 0;
                        posicao_produto_venda = 0;
                        aux_busca_produto = 0;
                        aux_busca_produto2 = 0;
                        while(continuar<1 || continuar>2){
                            printf("\n Deseja continuar?");
                            printf("\n 1 - Sim;\n");
                            printf("\n 2 - Não.\n");
                            scanf("%i", &continuar);
                            if (continuar == 1){
                                system("cls || clear");
                                quantidade_vendida = 0;
                                break;
                            }
                            if (continuar == 2){
                                system("cls || clear");
                                break;
                            }
                        }
                    }
                    if (continuar == 1){
                        continue;
                    }
                    if (continuar == 2){
                        break;
                    }
                }
                if (continuar == 2){
                    break;
                }
                continuar = 0;
                while(quantidade_vendida == 0){
                    time(&t);
                    tm = gmtime(&t);
                    system("cls || clear");
                    printf("\n Código do produto: %i", buffer[posicao_produto_venda].codigo_produto);
                    printf("\n Nome do produto: %s", buffer[posicao_produto_venda].nome_produto);
                    printf("\n Estoque do produto: %i", buffer[posicao_produto_venda].estoque_produto);
                    printf("\n Preço do produto: %0.2f\n", buffer[posicao_produto_venda].preco_produto);
                    printf("\n Quantas unidades serão vendidas?\n");
                    scanf("%i", &quantidade_vendida);
                    while(quantidade_vendida < 0){
                        printf("\n ERRO! Valor inválido!!!\n");
                        printf("\n Quantas unidades serão vendidas?\n");
                        scanf("%i", &quantidade_vendida);
                    }
                    if(buffer[posicao_produto_venda].estoque_produto == 0 || buffer[posicao_produto_venda].estoque_produto < quantidade_vendida){
                        printf("\n ERRO! Estoque insuficiente!\n");
                        while(continuar == 0){
                            printf("\n Deseja continuar?");
                            printf("\n 1 - Sim;\n");
                            printf("\n 2 - Não.\n");
                            scanf("%i", &continuar);
                            if (continuar == 1){
                                quantidade_vendida = 0;
                                break;
                            }
                            if (continuar == 2){
                                break;
                            }
                        }
                    }
                    if (continuar == 2){
                        break;
                    }
                }
                if (continuar == 2){
                    break;
                }
                if (quantidade_vendida != 0){
                    while(codigo_venda == 0 || codigo_venda < 0 || codigo_livre){
                        printf("\n Digite o código da venda!\n");
                        scanf("%i", &codigo_venda);
                        for(int i=0; i < tamanho_do_banco_vendas; i++){
                            if(codigo_venda == vendas[i].codigo_venda){
                                printf("\n Código de venda inválido!\n");
                                break;
                            }
                            if(i == (tamanho_do_banco_vendas-1)){
                                codigo_livre = 0;
                            }
                        }
                    }
                    buffer_vendas->codigo_venda = codigo_venda;
                    buffer_vendas->codigo_produto_venda = codigo_lido;
                    strcpy (buffer_vendas->nome_produto_venda, buffer[posicao_produto_venda].nome_produto);
                    buffer_vendas->quantidade_produto = quantidade_vendida;
                    buffer[posicao_produto_venda].estoque_produto = (buffer[posicao_produto_venda].estoque_produto) - (quantidade_vendida);
                    buffer_vendas -> preco_venda_unitario = buffer[posicao_produto_venda].preco_produto;
                    buffer_vendas -> dia = tm -> tm_mday;
                    buffer_vendas -> mes = tm -> tm_mon + 1;
                    buffer_vendas -> ano = tm -> tm_year + 1900;
                    buffer_vendas -> h = tm -> tm_hour + 9;
                    buffer_vendas -> m = tm -> tm_min;
                    buffer_vendas -> s = tm -> tm_sec;
                    codigo_lido=0;
                    posicao_produto_venda=0;
                    aux_busca_produto=0;
                    aux_busca_produto2=0;
                    continuar = 0;
                    quantidade_vendida =0;
                    printf("\n\n Processando venda...\n");
                    sleep(2);
                    printf("\n\n Venda realizada com sucesso!\n");
                    sleep(1);
                    return;
                }
                break;

            case 2:
                system("cls || clear");
                procura_produto (tamanho_do_banco, buffer);
                break;

            case 3:
                system("cls || clear");
                printf("Código_venda  |  Código produto  |  Quantidade  |  Nome do produto  |  Preço Unitário  |  Preço total  |        Data venda        |\n");
                for(int i=0; i<(tamanho_do_banco_vendas); i++){
                    if(vendas[i].codigo_venda != 0){
                        printf("      %i", vendas[i].codigo_venda);
                        printf("                %i", vendas[i].codigo_produto_venda);
                        printf("               %i", vendas[i].quantidade_produto);
                        printf("           %s", vendas[i].nome_produto_venda);
                        printf("           R$%0.2f", vendas[i].preco_venda_unitario);
                        printf("          R$%0.2f", vendas[i].preco_venda_unitario*vendas[i].quantidade_produto);
                        printf("        %02i/%02i/%02i - %02i:%02i:%02i\n\n", vendas[i].dia, vendas[i].mes,
                                   vendas[i].ano, vendas[i].h, vendas[i].m, vendas[i].s);
                    }
                }
                break;

            default:
                printf(" Número inválido!\n");
                break;
        }
    }
}

void relatorios_vendas (int tamanho_do_banco, produtos_cadastro *buffer, int tamanho_do_banco_vendas, registro_vendas *buffer_vendas){
    int menu_relatorio_rodando = 1, mes_busca = 0, codigo_produto = 0;
    int procura_cadastro = 0, aux_procura = 0, alterar_cadastro = 0, confirma_alteracao = 0, continuar = 0, encontra_cadadastro_mod = 0;
    registro_vendas top_vendas;
    while (menu_relatorio_rodando == 1){
        switch (menu_relatorio ()){
            case 0:
                system("cls || clear");
                menu_relatorio_rodando = 0;
                break;

            case 1:
                system("cls || clear");
                while(mes_busca < 1 || mes_busca >13){
                    printf("\nDigite o mês desejado!\n");
                    scanf("%i", &mes_busca);
                }
                printf("Código_venda  |  Código produto  |  Quantidade  |  Nome do produto  |  Preço Unitário  |  Preço total  |        Data venda        |\n");
                for (int i=0; i<tamanho_do_banco_vendas; i++){
                        if(buffer_vendas[i].mes == mes_busca){
                            printf("      %i", buffer_vendas[i].codigo_venda);
                            printf("                %i", buffer_vendas[i].codigo_produto_venda);
                            printf("               %i", buffer_vendas[i].quantidade_produto);
                            printf("           %s", buffer_vendas[i].nome_produto_venda);
                            printf("           R$%0.2f", buffer_vendas[i].preco_venda_unitario);
                            printf("          R$%0.2f", buffer_vendas[i].preco_venda_unitario*buffer_vendas[i].quantidade_produto);
                            printf("        %02i/%02i/%02i - %02i:%02i:%02i\n\n", buffer_vendas[i].dia, buffer_vendas[i].mes,
                                       buffer_vendas[i].ano, buffer_vendas[i].h, buffer_vendas[i].m, buffer_vendas[i].s);
                        }
                }
                mes_busca = 0;
                break;

            case 2:
                system("cls || clear");
                while(codigo_produto <= 0){
                    printf("\nDigite o código do produto!\n");
                    scanf("%i", &codigo_produto);
                }
                printf("Código_venda  |  Código produto  |  Quantidade  |  Nome do produto  |  Preço Unitário  |  Preço total  |        Data venda        |\n");
                for (int i=0; i<tamanho_do_banco_vendas; i++){
                        if(buffer_vendas[i].codigo_produto_venda == codigo_produto){
                            printf("      %i", buffer_vendas[i].codigo_venda);
                            printf("                %i", buffer_vendas[i].codigo_produto_venda);
                            printf("               %i", buffer_vendas[i].quantidade_produto);
                            printf("           %s", buffer_vendas[i].nome_produto_venda);
                            printf("           R$%0.2f", buffer_vendas[i].preco_venda_unitario);
                            printf("          R$%0.2f", buffer_vendas[i].preco_venda_unitario*buffer_vendas[i].quantidade_produto);
                            printf("        %02i/%02i/%02i - %02i:%02i:%02i\n\n", buffer_vendas[i].dia, buffer_vendas[i].mes,
                                       buffer_vendas[i].ano, buffer_vendas[i].h, buffer_vendas[i].m, buffer_vendas[i].s);
                        }
                }
                codigo_produto = 0;
                break;

            case 3:
                system("cls || clear");
                system("cls || clear");
                for (int i = 0; i < tamanho_do_banco_vendas; i++){
                    for(int j = i + 1; j < tamanho_do_banco_vendas; j++){
                        if(buffer_vendas[i].codigo_produto_venda != 0 && buffer_vendas[i].quantidade_produto > buffer_vendas[j].quantidade_produto){
                           top_vendas = buffer_vendas[i];
                           buffer_vendas[i] = buffer_vendas[j];
                           buffer_vendas[j] = top_vendas;
                        }
                    }
                }
                printf("Código_venda  |  Código produto  |  Quantidade  |  Nome do produto  |  Preço Unitário  |  Preço total  |        Data venda        |\n");
                for (int i=0; i<tamanho_do_banco_vendas; i++){
                    if(buffer_vendas[i].codigo_produto_venda != 0){
                        printf("      %i", buffer_vendas[i].codigo_venda);
                        printf("                %i", buffer_vendas[i].codigo_produto_venda);
                        printf("               %i", buffer_vendas[i].quantidade_produto);
                        printf("           %s", buffer_vendas[i].nome_produto_venda);
                        printf("           R$%0.2f", buffer_vendas[i].preco_venda_unitario);
                        printf("          R$%0.2f", buffer_vendas[i].preco_venda_unitario*buffer_vendas[i].quantidade_produto);
                        printf("        %02i/%02i/%02i - %02i:%02i:%02i\n\n", buffer_vendas[i].dia, buffer_vendas[i].mes,
                                    buffer_vendas[i].ano, buffer_vendas[i].h, buffer_vendas[i].m, buffer_vendas[i].s);
                    }
                }
                break;

            case 4:
                system("cls || clear");
                printf("Código_venda  |  Código produto  |  Quantidade  |  Nome do produto  |  Preço Unitário  |  Preço total  |        Data venda        |\n");
                for (int i=0; i<tamanho_do_banco_vendas; i++){
                    if(buffer_vendas[i].codigo_produto_venda != 0){
                        printf("      %i", buffer_vendas[i].codigo_venda);
                        printf("                %i", buffer_vendas[i].codigo_produto_venda);
                        printf("               %i", buffer_vendas[i].quantidade_produto);
                        printf("           %s", buffer_vendas[i].nome_produto_venda);
                        printf("           R$%0.2f", buffer_vendas[i].preco_venda_unitario);
                        printf("          R$%0.2f", buffer_vendas[i].preco_venda_unitario*buffer_vendas[i].quantidade_produto);
                        printf("        %02i/%02i/%02i - %02i:%02i:%02i\n\n", buffer_vendas[i].dia, buffer_vendas[i].mes,
                                    buffer_vendas[i].ano, buffer_vendas[i].h, buffer_vendas[i].m, buffer_vendas[i].s);
                    }
                }
                break;

            case 5:
                system("cls || clear");
                procura_produto (tamanho_do_banco, buffer);
                break;

            case 6:
                printf("\n Qual venda deseja alterar?\n");
                scanf("%i", &procura_cadastro);
                for (int i=0; i<tamanho_do_banco_vendas; i++){
                    if(buffer_vendas[i].codigo_venda == procura_cadastro){
                        alterar_cadastro = i;
                        break;
                    }
                    if (i==99){
                        aux_procura=1;
                    }
                }
                while(aux_procura==1){
                    printf("\n\n VENDA NÃO ENCONTRADA!!!\n\n");
                    continuar=0;
                    printf("\n Deseja prosseguir?\n");
                    while (continuar < 1 || continuar > 2){
                        printf(" 1 - Sim;");
                        printf("\n 2 - Não.\n");
                        scanf("%i", &continuar);
                        if(continuar==2){
                            break;
                        }
                    }
                    if(continuar==2){
                        break;
                    }
                    printf("\n Qual venda deseja alterar?\n");
                    scanf("%i", &procura_cadastro);
                    for (int i=0; i<tamanho_do_banco_vendas; i++){
                        alterar_cadastro = 0;
                        if(buffer_vendas[i].codigo_venda == procura_cadastro){
                            alterar_cadastro = i;
                            aux_procura = 0;
                            break;
                        }
                    }
                }
                if(continuar!=2){
                    printf("Código_venda  |  Código produto  |  Quantidade  |  Nome do produto  |  Preço Unitário  |  Preço total  |        Data venda        |\n");
                    printf("      %i", buffer_vendas[alterar_cadastro].codigo_venda);
                    printf("                %i", buffer_vendas[alterar_cadastro].codigo_produto_venda);
                    printf("               %i", buffer_vendas[alterar_cadastro].quantidade_produto);
                    printf("           %s", buffer_vendas[alterar_cadastro].nome_produto_venda);
                    printf("           R$%0.2f", buffer_vendas[alterar_cadastro].preco_venda_unitario);
                    printf("          R$%0.2f", buffer_vendas[alterar_cadastro].preco_venda_unitario*buffer_vendas[alterar_cadastro].quantidade_produto);
                    printf("        %02i/%02i/%02i - %02i:%02i:%02i\n\n", buffer_vendas[alterar_cadastro].dia, buffer_vendas[alterar_cadastro].mes,
                                    buffer_vendas[alterar_cadastro].ano, buffer_vendas[alterar_cadastro].h, buffer_vendas[alterar_cadastro].m, buffer_vendas[alterar_cadastro].s);
                    printf("\n Tem certeza que deseja alterar a venda número: %i?\n", procura_cadastro);
                    printf("\n 1 - Sim;");
                    printf("\n 2 - Nao.\n");
                    scanf("%i", &confirma_alteracao);
                    while (confirma_alteracao < 1 || confirma_alteracao > 2){
                        printf("\n NUMERO INVALIDO!!!\n\n");
                        printf("\n Tem certeza que deseja alterar a venda número: %i?\n", procura_cadastro);
                        printf("\n 1 - Sim;");
                        printf("\n 2 - Nao.\n");
                        scanf("%i", &confirma_alteracao);
                        if (confirma_alteracao==2){
                            break;
                        }
                    }

                    if (confirma_alteracao==1){
                        printf("\n Digite o codigo da venda:\n");
                        scanf("%i", &buffer_vendas[alterar_cadastro].codigo_venda);
                        printf("\n Digite o codigo do produto:\n");
                        scanf("%i", &buffer_vendas[alterar_cadastro].codigo_produto_venda);
                        for (int i = 0; i < tamanho_do_banco; i++){
                            if(buffer_vendas[alterar_cadastro].codigo_produto_venda == buffer[i].codigo_produto){
                               encontra_cadadastro_mod = i;
                                break;
                            }
                        }
                        buffer[encontra_cadadastro_mod].estoque_produto =  buffer[encontra_cadadastro_mod].estoque_produto + buffer_vendas[alterar_cadastro].quantidade_produto;
                        buffer_vendas[alterar_cadastro].quantidade_produto = 0;
                        while(buffer_vendas[alterar_cadastro].quantidade_produto == 0){
                            printf("\n Quantas unidades foram vendidas?\n");
                            scanf("%i", &buffer_vendas[alterar_cadastro].quantidade_produto);
                            while(buffer_vendas[alterar_cadastro].quantidade_produto < 0){
                                printf("\n ERRO! Valor inválido!!!\n");
                                printf("\n Quantas unidades foram vendidas?\n");
                                scanf("%i", &buffer_vendas[alterar_cadastro].quantidade_produto);
                            }
                            if(buffer[encontra_cadadastro_mod].estoque_produto == 0 || buffer[encontra_cadadastro_mod].estoque_produto < buffer_vendas[alterar_cadastro].quantidade_produto){
                                printf("\n ERRO! Estoque insuficiente!\n");
                                buffer_vendas[alterar_cadastro].quantidade_produto = 0;
                            }
                        }
                        buffer[encontra_cadadastro_mod].estoque_produto = buffer[encontra_cadadastro_mod].estoque_produto - buffer_vendas[alterar_cadastro].quantidade_produto;
                        printf("\n Digite o nome do produto:\n");
                        setbuf(stdin, 0);
                        fgets(buffer_vendas[alterar_cadastro].nome_produto_venda, 99, stdin);
                        buffer_vendas[alterar_cadastro].nome_produto_venda[strcspn(buffer_vendas[alterar_cadastro].nome_produto_venda, "\n")] = 0;
                        printf("\n Digite o preço:\n");
                        scanf("%f", &buffer_vendas[alterar_cadastro].preco_venda_unitario);
                        printf("\n Digite o dia da venda:\n");
                        scanf("%i", &buffer_vendas[alterar_cadastro].dia);
                        printf("\n Digite o mês da venda:\n");
                        scanf("%i", &buffer_vendas[alterar_cadastro].mes);
                        printf("\n Digite o ano da venda:\n");
                        scanf("%i", &buffer_vendas[alterar_cadastro].ano);
                    }
                }
                break;

            default:
                printf("Número inválido!\n");
                break;
        }
    }
}
