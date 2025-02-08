#include <stdio.h>
#include <stdlib.h>
#include "paciente_func.h"

#define ARQUIVO_CSV "bd_paciente.csv"

int main() {
    BDPaciente *bd = ListaBD_create();
    load_banco(bd, ARQUIVO_CSV);  // carrega pacientes do arquivo CSV
    char opcao = '0';
    char menu[] = "1 - Consultar paciente\n2 - Atualizar paciente\n3 - Remover paciente\n4 - Inserir paciente\n5 - Imprimir lista de pacientes\nQ - Sair";
    printf("Bem-vindo ao sistema HealthSys!\n");
    
    do {
        printf("%s\n", menu);
        printf("////////////////////////////\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao); 
        
        switch (opcao) {
            /*case '1':
                consultar_paciente(bd); MUDAAAAAR
                break;*/
            case '2':
                atualizar_paciente(bd);
                break;
            case '3':
                remover_paciente(bd);
                break;
            case '4':
                inserir_paciente(bd);
                break;
            case '5':
                imprimir_pacientes(bd);
                break;
            case 'Q':
                salvar_banco(bd, ARQUIVO_CSV);
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 'Q');

    free_lista(bd);  // libera memória
    free(bd);
    return 0;
}
