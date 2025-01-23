#include <stdio.h>
#include "paciente_func.h"
#include <string.h>
#include <stdlib.h>

struct Paciente
{
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadast[11];
} Paciente;

Pacient *pt_create(int *id, const char *cpf, const char *nome, int *idade, const char *data_cadast)
{
    Pacient *p = (Pacient *)malloc(sizeof(Pacient));
    p->id = id;
    strcpy(p->cpf, cpf);
    strcpy(p->nome, nome);
    p->idade = idade;
    strcpy(p->data_cadast, data_cadast);
    
    return p;
}
