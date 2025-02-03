#ifndef PACIENTE_H
#define PACIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paciente {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
    struct Paciente *next;
} Paciente;

typedef struct {
    Paciente *first;
    int next_id;
} BDPaciente;

void load_banco(BDPaciente *bd, const char *filename);
void salvar_banco(BDPaciente *bd, const char *filename);
void consultar_paciente(BDPaciente *bd);
void atualizar_paciente(BDPaciente *bd);
void remover_paciente(BDPaciente *bd);
void inserir_paciente(BDPaciente *bd);
void imprimir_pacientes(BDPaciente *bd);

Paciente* buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf);
Paciente* buscar_paciente_por_nome(BDPaciente *bd, const char *nome);
void liberar_lista(BDPaciente *bd);

#endif
