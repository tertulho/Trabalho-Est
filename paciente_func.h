#ifndef PACIENTE_FUNC_H
#define PACIENTE_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCTS//
// estrutura paciente
typedef struct Paciente {
    char nome[100];
    char cpf[14];
    int idade;
    int id;
    char data_cadastro[50];
} Paciente;

// estrutura do nó
typedef struct ListNode {
    Paciente *info;
    struct ListNode *next;
} ListNode;

// estrutura banco de dados
typedef struct {
    int count;
    int next_id;
    ListNode *first;
} BDPaciente;
//STRUCTS//

//FUNCOES DO MAIN//
void inserir_paciente(BDPaciente *bd);
void consultar_paciente(BDPaciente *bd);
void atualizar_paciente(BDPaciente *bd);
void remover_paciente(BDPaciente *bd);
void imprimir_pacientes(BDPaciente *bd);
void free_lista(BDPaciente *bd);
void load_banco(BDPaciente *bd, const char *nomedoarquivo);
void salvar_banco(BDPaciente *bd, const char *nomedoarquivo);
//FUNCOES DO MAIN//

//FUNCOES AUXILIARES//
int buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf);
int buscar_paciente_por_nome(BDPaciente *bd, const char *nome , const int tamanho);
Paciente *newPaciente(char nome[], char cpf[], int idade, int id, char data_cadastro[]);
BDPaciente *ListaBD_create();
//FUNCOES AUXILIARES//
#endif
