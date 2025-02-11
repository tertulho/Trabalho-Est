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

void consultar_paciente(BDPaciente *bd){
    
    char opcao , cpf[14] , nome[100];
    int resposta = 0 , fds = 0; //indica sucesso ou falha na busca
    
    printf("Escolha uma das opcoes : \n c -> consultar buscando pelo cpf \n n -> buscar usando o nome \noutra entrada retorna ao menu inicial \n");

    scanf(" %s" , &opcao);
    
    
    switch (opcao)
    {
    case ('c'):
        printf("digite o cpf desejado : ");
        scanf(" %s" , cpf);
        resposta = buscar_paciente_por_cpf(bd, cpf);
        if (resposta==0)
        {
            printf("Erro na busca, paciente não encontrado\n");
            return;
            break;
        }
        
        break;

    case('n'):

        printf("digite o nome desejado : ");
        getc(stdin); // recebe \n digitado pelo teclado
        fgets( nome , 100, stdin); // recebe a string digitada

        while (nome[fds]!= '\n')
        {
            fds++; // indica \n na string 
        }
        nome[fds] = '\0' ;  // retira \n da string

        
        resposta = buscar_paciente_por_nome(bd, nome, strlen(nome)); // buscando nome
        if (resposta == 0) 
            printf("Erro na busca, nenhum paciente encontrado \n");
        
        return;
        break;
    default:
        break;
    }
    
    
    return;
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

int buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf) {
    ListNode *atual = bd->first;
    int cont = 0; // conta os cadastros encontrados

    printf("\nID | CPF | Nome | Idade | Data Cadastro\n"); // imprime cabeçalho

    while (atual) {
        if (strcmp(atual->info->cpf, cpf) == 0) {
            printf("%d | %s | %s | %d | %s\n", atual->info->id, atual->info->cpf, atual->info->nome, atual->info->idade, atual->info->data_cadastro); // imprime cadastros encontrados
            cont++;
            
        }
        atual = atual->next;
    }
    return cont;

}

int buscar_paciente_por_nome(BDPaciente *bd, const char *nome , const int tamanho) {
    ListNode *atual = bd->first;

    printf("\nID | CPF | Nome | Idade | Data Cadastro\n"); // imprime cabeçalho
    
    int cont=0 , i = 0; //verifica quantidade certa de igualdade entre as strings
    int achado = 0;

    while (atual) {
        // percorre o nome do paciente
        while(atual->info->nome[i]!='\0'){
            // verifica a igualdade sequencial dos caracteres ; a presença dos ||(ou logico) garante que a letra seja reconhecida mesmo que seja uma minuscula e outra maiuscual
            if (atual->info->nome[i] == nome[cont] || atual->info->nome[i] == toupper(nome[cont]) || tolower(atual->info->nome[i]) == nome[cont] || toupper(atual->info->nome[i]) == nome[cont] ){
                cont++;
                // verifica se a string desejada esta contida totalmente
                if(cont == tamanho){
                    printf("%d | %s | %s | %d | %s\n", atual->info->id, atual->info->cpf, atual->info->nome, atual->info->idade, atual->info->data_cadastro); // imprime cadastros encontrados 
                    achado++;
                    break;
                }
            }else{
                cont = 0;
            }
            i++;
            
        }
        cont = 0; // zerando contadores para verificação de um novo nome
        i = 0;
        atual = atual->next;
    }
    return achado;
}

//atualiza algum usuario ja existente
void atualizar_paciente(BDPaciente *bd) {
    int id;
    printf("\nDigite o ID do paciente a ser atualizado: ");
    scanf("%d", &id);//pede id do usuario a ser atualizado

    ListNode *atual = bd->first; //começa a busca a partir do primeiro nó
    while (atual) { //percorre enquanto tiver nós
        if (atual->info->id == id) { //verifica se od id atual é o procurado
            //printf("Digite o novo CPF, Nome, Idade e Data_Cadastro (ou '-' para manter o valor atual):\n");
            char cpf[15], nome[100], data[11], opcao;
            int idade, fds = 0;
            //scanf(" %[^\n] %[^\n] %d %[^\n]", cpf, nome, &idade, data); //le os novos valores de dados
            
            while(1){
                printf("\nEscolha uma das letra abaixo para modificar um dado \n");
                printf("n -> para atualizar o nome \ni -> para atualizar a idade do paciente \nc -> para atualizar o cpf \nd -> para atualizar a data de cadastro \nQ -> para finalizar a alteração dos dados \nopção : ");
                scanf(" %c", &opcao);
                
                switch(opcao){
                    case('n'):
                    printf("digite o novo nome : ");
                    getc(stdin);
                    fgets( nome , 100, stdin);

                    while (nome[fds]!= '\n')
                    {
                        fds++;
                    }
                    nome[fds] = '\0' ;
                    strcpy(atual->info->nome, nome);
                    break;

                    case('c'):
                    printf("digite o novo cpf : ");
                    scanf(" %s" , cpf);
                    strcpy(atual->info->cpf, cpf);
                    break;

                    case('d'):
                    printf("Digite a data de cadastro (AAAA-MM-DD) : ");
                    scanf(" %s", data);
                    strcpy(atual->info->data_cadastro, data);
                    break;
                    
                    case('i'):
                    printf("Digite a nova idade do paciente : ");
                    scanf(" %d" , &idade);
                    atual->info->idade = idade;
                    break;

                    case('Q'):
                    printf("dados atualizados com sucesso!\n");
                    return;
                }

            }

           
        }
        atual = atual->next; //avança próximo nó
    }
    printf("Paciente não encontrado.\n");
    return;
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
