#include "paciente_func.h"

// cria um novo paciente
Paciente *newPaciente(char nome[], char cpf[], int idade, int id, char data_cadastro[]) {
    Paciente *new = (Paciente *)malloc(sizeof(Paciente)); // aloca memória para um novo paciente
    if (!new) { // verifica se a alocação falhou
        printf("Erro ao alocar memória para Paciente");
        exit(EXIT_FAILURE); 
    }

    strcpy(new->nome, nome); // copia o nome para a estrutura
    strcpy(new->cpf, cpf); // copia o cpf para a estrutura
    strcpy(new->data_cadastro, data_cadastro); // copia a data de cadastro para a estrutura
    new->idade = idade; // atribui a idade ao paciente
    new->id = id; // atribui o id ao paciente

    return new; // retorna o ponteiro para o novo paciente
}

// cria um banco de dados de pacientes
BDPaciente *ListaBD_create() {
    BDPaciente *lista = (BDPaciente *)malloc(sizeof(BDPaciente)); // aloca memória para o banco de dados
    if (!lista) { // verifica se a alocação falhou
        printf("erro na criação do banco de dados");
        exit(EXIT_FAILURE); 
    }
    lista->count = 0; // inicializa o contador de pacientes como zero
    lista->next_id = 1; // inicializa o próximo id como 1
    lista->first = NULL; // inicializa a lista como vazia
    return lista; // retorna o ponteiro para o banco de dados
}

// insere um novo paciente no banco de dados
void inserir_paciente(BDPaciente *bd) {
    // declara variáveis para armazenar os dados
    char nome[100], cpf[15], data_cadastro[50]; 
    int idade, id = bd->next_id; // proximo ID é gerado

    printf("Digite o CPF, Nome, Idade e Data_Cadastro:\n");
    scanf(" %[^\n] %[^\n] %d %[^\n]", cpf, nome, &idade, data_cadastro); // le os novos valores

    // mostra os dados inseridos e pede confirmação
    printf("\nConfirma a inserção do registro abaixo? (S/N)\n");
    printf("ID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");
    printf("%d\t%s\t%s\t%d\t%s\n", id, cpf, nome, idade, data_cadastro);

    char confirmacao;
    scanf(" %c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        // cria um novo paciente
        Paciente *new = newPaciente(nome, cpf, idade, bd->next_id++, data_cadastro);

        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode)); // aloca memória para um novo nó
        if (!newNode) {
            printf("Erro ao alocar memória para o ListNode\n");
            exit(EXIT_FAILURE);
        }
        newNode->info = new; // atribui o paciente ao novo nó
        newNode->next = bd->first; // insere o nó no início da lista
        bd->first = newNode; // define o novo nó como primeiro da lista
        bd->count++; // incrementa o contador de pacientes

        printf("Paciente inserido com sucesso!\n");
    } else {
        printf("Operação cancelada.\n");
    }
}

// imprime todos os pacientes cadastrados
void imprimir_pacientes(BDPaciente *bd) {
    ListNode *atual = bd->first; // inicializa o ponteiro para percorrer a lista
    printf("\nID | CPF | Nome | Idade | Data Cadastro\n"); // imprime cabeçalho
    printf("------------------------------------------\n"); // imprime separador
    while (atual) { // percorre a lista de pacientes
        Paciente *p = atual->info; // obtém o paciente do nó atual
        printf("%d | %s | %s | %d | %s\n", p->id, p->cpf, p->nome, p->idade, p->data_cadastro); // imprime os dados do paciente
        atual = atual->next; // avança para o próximo nó
    }
}

Paciente* buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf) {
    ListNode *atual = bd->first;
    while (atual) {
        if (strcmp(atual->info->cpf, cpf) == 0) {
            return atual->info;
        }
        atual = atual->next;
    }
    return NULL;
}

Paciente* buscar_paciente_por_nome(BDPaciente *bd, const char *nome) {
    ListNode *atual = bd->first;
    while (atual) {
        if (strcmp(atual->info->nome, nome) == 0) {
            return atual->info;
        }
        atual = atual->next;
    }
    return NULL;
}

void consultar_paciente(BDPaciente *bd) {
    int opcao;
    char valor[100]; // armazena o cpf ou nome a ser buscado

    // menu de opções para o usuário
    printf("Escolha o critério de busca:\n");
    printf("1. Buscar por CPF\n");
    printf("2. Buscar por Nome\n");
    printf("3. Voltar ao menu principal\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Digite o CPF do paciente: ");
            scanf(" %[^\n]", valor); // le o cpf
            Paciente *resultado_cpf = buscar_paciente_por_cpf(bd, valor); // busca por cpf
            if (resultado_cpf != NULL) {
                printf("\nPaciente encontrado:\n");
                printf("  ID: %d\n", resultado_cpf->id);
                printf("  CPF: %s\n", resultado_cpf->cpf);
                printf("  Nome: %s\n", resultado_cpf->nome);
                printf("  Idade: %d\n", resultado_cpf->idade);
                printf("  Data de Cadastro: %s\n", resultado_cpf->data_cadastro);
            } else {
                printf("Paciente não encontrado.\n");
            }
            break;
        case 2:
            printf("Digite o nome do paciente: ");
            scanf(" %[^\n]", valor); // le o nome
            ListNode *atual = bd->first;
            int encontrados = 0;

            // percorre a lista de pacientes
            while (atual != NULL) {
                if (strcmp(atual->info->nome, valor) == 0) {
                    printf("\nPaciente encontrado:\n");
                    printf("  ID: %d\n", atual->info->id);
                    printf("  CPF: %s\n", atual->info->cpf);
                    printf("  Nome: %s\n", atual->info->nome);
                    printf("  Idade: %d\n", atual->info->idade);
                    printf("  Data de Cadastro: %s\n", atual->info->data_cadastro);
                    encontrados++;
                }
                atual = atual->next; //avança próximo paciente
            }

            if (encontrados == 0) {
                printf("Nenhum paciente encontrado com o nome: %s\n", valor);
            } else {
                printf("\nTotal de pacientes encontrados: %d\n", encontrados);
            }
            break;
        case 3:
            printf("Retornando ao menu principal\n");
            return;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

//atualiza algum usuario ja existente
void atualizar_paciente(BDPaciente *bd) {
    int id;
    printf("Digite o ID do paciente a ser atualizado: ");
    scanf("%d", &id); // pede ID do usuário a ser atualizado

    ListNode *atual = bd->first; // começa a busca a partir do primeiro nó

    while (atual) { // percorre enquanto tiver nós
        if (atual->info->id == id) { // verifica se o ID atual é o procurado
            printf("Digite o novo CPF, Nome, Idade e Data_Cadastro (ou '-' para manter o valor atual):\n");

            char cpf[15], nome[100], data[50];
            int idade;
            scanf(" %[^\n] %[^\n] %d %[^\n]", cpf, nome, &idade, data); // lê os novos valores de dados

            // mostra os dados atuais e os novos para confirmação
            printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
            printf("ID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");
            printf("%d\t%s\t%s\t%d\t%s\n", 
                   atual->info->id, 
                   (strcmp(cpf, "-") == 0 ? atual->info->cpf : cpf), 
                   (strcmp(nome, "-") == 0 ? atual->info->nome : nome), 
                   (idade == -1 ? atual->info->idade : idade), 
                   (strcmp(data, "-") == 0 ? atual->info->data_cadastro : data));

            char confirmacao;
            scanf(" %c", &confirmacao);

            if (confirmacao == 'S') {
                // atualiza os campos levando em consideração o "-"
                if (strcmp(cpf, "-") != 0) strcpy(atual->info->cpf, cpf);
                if (strcmp(nome, "-") != 0) strcpy(atual->info->nome, nome);
                if (idade != -1) atual->info->idade = idade;
                if (strcmp(data, "-") != 0) strcpy(atual->info->data_cadastro, data);

                printf("Paciente atualizado com sucesso!\n");
            } else {
                printf("Operação cancelada.\n");
            }
            return;
        }
        atual = atual->next; // avança para o próximo nó
    }
    printf("Paciente não encontrado.\n");
}

void remover_paciente(BDPaciente *bd) { 
    int id;
    char confirmacao;

    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &id); // id a ser removido

    ListNode *anterior = NULL;
    ListNode *atual = bd->first; // início da busca a partir do primeiro nó

    while (atual) { // percorre enquanto houver nós
        if (atual->info->id == id) {
            printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n");
            printf("ID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");
            printf("%d\t%s\t%s\t%d\t%s\n", 
                   atual->info->id, 
                   atual->info->cpf, 
                   atual->info->nome, 
                   atual->info->idade, 
                   atual->info->data_cadastro);

            scanf(" %c", &confirmacao); // Captura a confirmação do usuário

            if (confirmacao == 'S' || confirmacao == 's') {
                if (anterior) { // remove o nó atual ajustando o ponteiro do nó anterior
                    anterior->next = atual->next; 
                } else {
                    bd->first = atual->next; // se for o primeiro nó, atualiza o início da lista
                }
                free(atual->info); // libera memória dos dados do paciente
                free(atual); // libera memória do nó
                bd->count--; // decrementa contador de pacientes
                printf("Paciente removido com sucesso!\n");
            } else {
                printf("Operação cancelada.\n");
            }
            return;
        }
        anterior = atual; // atualiza ponteiro do nó anterior
        atual = atual->next; // avança para o próximo nó da lista
    }
    printf("Paciente não encontrado.\n");
}

// libera a memória da lista de pacientes
void free_lista(BDPaciente *bd) {
    ListNode *atual = bd->first; // inicia a partir do primeiro nó da lista
    while (atual) { // percorre a lista de nós
        ListNode *temp = atual; // armazena o nó atual em uma variável temporária
        atual = atual->next; // avança para o próximo nó
        free(temp->info); // libera a memória dos dados do paciete
        free(temp); // libera a memória do nó
    }
}
void load_banco(BDPaciente *bd, const char *arquivo) {
    FILE *file = fopen(arquivo, "r"); // le o arquivo csv
    if (!file) { // verifica se o arquivo foi aberto com sucesso
        printf("Arquivo CSV não encontrado. Criando novo...\n");
        salvar_banco(bd, arquivo); // cria um novo arquivo csv se não existir
        return;
    }

    char linha[200];
    fgets(linha, sizeof(linha), file); // le a primeira linha

    while (fgets(linha, sizeof(linha), file)) { //le linha por linha
        char nome[100], cpf[14], data[50];
        int id, idade;
        // pega os valores do arquivo
        sscanf(linha, "%d,%[^,],%[^,],%d,%s", &id, cpf, nome, &idade, data);

        // cria um novo paciente com os dados lidos
        Paciente *new = newPaciente(nome, cpf, idade, id, data);
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode)); // aloca memória para um novo nó
        if (!newNode) { // verifica se alocou certo
            printf("Erro ao alocar memória para ListNode");
            exit(EXIT_FAILURE);
        }
        newNode->info = new; // armazena o paciente no nó
        newNode->next = bd->first; // insere o nó no início da lista
        bd->first = newNode; // atualiza o início da lista
        bd->count++; // incrementa o contador de pacientes

        
        if (id >= bd->next_id) { //atualiza próximo id
            bd->next_id = id + 1;
        }
    }

    fclose(file);
}

void salvar_banco(BDPaciente *bd, const char *arquivo) {
    FILE *file = fopen(arquivo, "w"); //abre o arquivo csv para escrever
    fprintf(file, "ID,CPF,Nome,Idade,Data_Cadastro\n"); // escreve o cabeçalho no arquivo

    ListNode *atual = bd->first; // inicia a partir do primeiro nó da lista
    while (atual) { // percorre a lista enquanto tem nós
        // escreve os dados do paciente no arquivo csv
        fprintf(file, "%d,%s,%s,%d,%s\n", atual->info->id, atual->info->cpf, atual->info->nome, atual->info->idade, atual->info->data_cadastro);
        atual = atual->next; // avança pro próximo nó
    
}fclose(file); 
}
