#include <stdio.h>

int main(){
    char opcao[] = "0";

    printf("Bem vindo ao sistema HealtSys!\n");
    char menu[] = "1 - Consultar paciente\n2 - Atualizar paciente\n3 - Remover paciente\n4 - Inserir paciente\n5 - Imprimir lista de pacientes\nQ - Sair";
    printf("%s\n", menu);
    while (opcao[0] != 'Q')
    {
        if (opcao[0] == '1')
            printf("função 1");
        if (opcao[0] == '2')
            printf("função 2");
        if (opcao[0] == '3')
            printf("função 3");
        if (opcao[0] == '4')
            printf("função 4");
        if (opcao[0] == '5')
            printf("função 5");
        
        scanf("%c", &opcao[0]);
        printf("%s\n", opcao);
    }
    printf("fim de programa");
    
    return 0;

}
