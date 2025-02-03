#include <stdio.h>
#include "paciente_func.h"
#include <string.h>
#include <stdlib.h>

void inserir_paciente(BDPaciente *bd) {
    Paciente *novo = (Paciente*)malloc(sizeof(Paciente));
    novo->id = bd->next_id++;
    printf("Digite o CPF (apenas dígitos): ");
    scanf(" %[^\n]", novo->cpf);
    printf("Digite o nome: ");
    scanf(" %[^\n]", novo->nome);
    printf("Digite a idade: ");
    scanf("%d", &novo->idade);
    printf("Digite a data de cadastro (AAAA-MM-DD): ");
    scanf(" %[^\n]", novo->data_cadastro);

    novo->next = bd->first;
    bd->first = novo;

    printf("Registro inserido com sucesso.\n");
}

void remover_paciente(BDPaciente *bd) {
    int id;
    printf("Digite o ID do registro a ser removido: ");
    scanf("%d", &id);

    Paciente *anterior = NULL;
    Paciente *atual = bd->first;

    while (atual && atual->id != id) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual) {
        if (anterior) {
            anterior->next = atual->next;
        } else {
            bd->first = atual->next;
        }
        free(atual);
        printf("Registro removido com sucesso.\n");
    } else {
        printf("Paciente não encontrado.\n");
    }
}

void imprimir_pacientes(BDPaciente *bd) {
    Paciente *atual = bd->first;
    printf("ID | CPF | Nome | Idade | Data Cadastro\n");
    while (atual) {
        printf("%d | %s | %s | %d | %s\n", atual->id, atual->cpf, atual->nome, atual->idade, atual->data_cadastro);
        atual = atual->next;
    }
}
