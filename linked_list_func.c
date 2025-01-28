#include <stdio.h>
#include <stdlib.h>
#include <paciente_func.h>

struct List_node
{
    Pacient *dados;
    struct List_node *next;
    struct List_node *prev;

};

struct Linked_list
{
    struct List_node *primeiro;
    struct List_node *ultimo;
    int quant_no;
};

struct Linked_list *criacao_lista_vazia(){
    struct Linked_list *list = (struct Linked_list *)malloc(sizeof(struct Linked_list));
    
    // inicialização da lista. Ponto de partida
    list->primeiro = NULL;
    list->ultimo = NULL;
    list->quant_no = 0;

    return list;
}

struct List_node *criacao_no(Pacient *info, int contador, struct Linked_node *proximo, struct Linked_node *anterior){
    struct List_node *no = (struct List_node *)malloc(sizeof(struct List_node));
    no->dados = info;
    no->next = proximo;
    no->prev= anterior;

    return no;
}



