
#include "paciente_func.h"

// cria um novo paciente
Paciente *newPaciente(char nome[], char cpf[], int idade, int id, char data_cadastro[]) {
    Paciente *new = (Paciente *)malloc(sizeof(Paciente)); // aloca memória para um novo paciente
    if (!new) { // verifica se a alocação falhou
        perror("Erro ao alocar memória para Paciente");
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
        perror("erro na criação do banco de dados");
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
    char nome[100], cpf[14], data_cadastro[50]; 
    int idade;
    int fds= 0;

    printf("Digite o CPF: "); // solicita o cpf do paciente
    scanf(" %s", cpf); // lê o cpf informado
    printf("Digite o nome: "); // solicita o nome do paciente
    //scanf(" %s", nome); // lê o nome informado
    getc(stdin);
    fgets( nome , 100, stdin);

    while (nome[fds]!= '\n')
    {
        fds++;
    }
    nome[fds] = '\0' ;

    printf("Digite a idade: "); // solicita a idade do paciente
    scanf(" %d", &idade); // lê a idade informada
    printf("Digite a data de cadastro (AAAA-MM-DD): "); // solicita a data de cadastro
    scanf(" %s", data_cadastro); // lê a data informada

    Paciente *new = newPaciente(nome, cpf, idade, bd->next_id++, data_cadastro); // cria um novo paciente

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode)); // aloca memória para um novo nó da lista
    if (!newNode) { // verifica se a alocação falhou
        perror("Erro ao alocar memória para o listnode");
        exit(EXIT_FAILURE);
    }
    newNode->info = new; // atribui o paciente ao novo nó
    newNode->next = bd->first; // insere o nó no início da lista
    bd->first = newNode; // define o novo nó como primeiro da lista
    bd->count++; // incrementa o contador de pacientes

    printf("Paciente inserido!\n"); // exibe mensagem de sucesso
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
    printf("\n\n");
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

//atualiza algum usuario ja existente
void atualizar_paciente(BDPaciente *bd) {
    int id;
    printf("Digite o ID do paciente a ser atualizado: ");
    scanf("%d", &id);//pede id do usuario a ser atualizado

    ListNode *atual = bd->first; //começa a busca a partir do primeiro nó
    while (atual) { //percorre enquanto tiver nós
        if (atual->info->id == id) { //verifica se od id atual é o procurado
            printf("Digite o novo CPF, Nome, Idade e Data_Cadastro (ou '-' para manter o valor atual):\n");
            char cpf[15], nome[100], data[50];
            int idade;
            scanf(" %[^\n] %[^\n] %d %[^\n]", cpf, nome, &idade, data); //le os novos valores de dados
            
            //atualiza os campos levando em consideração o "-"
            if (strcmp(cpf, "-") != 0) strcpy(atual->info->cpf, cpf);
            if (strcmp(nome, "-") != 0) strcpy(atual->info->nome, nome);
            if (idade != -1) atual->info->idade = idade;
            if (strcmp(data, "-") != 0) strcpy(atual->info->data_cadastro, data);

            printf("Paciente atualizado com sucesso!\n");
            return;
        }
        atual = atual->next; //avança próximo nó
    }
    printf("Paciente não encontrado.\n");
}

void remover_paciente(BDPaciente *bd) {
    int id;
    printf("Digite o ID do paciente a ser removido: ");
    scanf("%d", &id); //id a ser removido

    ListNode *anterior = NULL;
    ListNode *atual = bd->first; //inicio da busca a partir do primeiro nó

    while (atual) { //percorre enquanto houver nós
        if (atual->info->id == id) {
            if (anterior) { //remove o nó atual ajustando o ponteiro do nó anterior
                anterior->next = atual->next; 
            } else {
                bd->first = atual->next; //se o nó a ser removido for o primeiro, atualiza o início da lista

            }
            free(atual->info); // livera memória dos dados do paciente
            free(atual); // libera memória do nó
            bd->count--; // decrementa contador de pacietntes
            printf("Paciente removido com sucesso!\n");
            return;
        }
        anterior = atual; //atualiza ponteiro do nó anterior
        atual = atual->next; // avança pro proximo nó da lista
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
            perror("Erro ao alocar memória para ListNode");
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
    }
    fclose(file);
}
