#include <stdio.h>

int main(){
    char opcao = '0';

    printf("Bem vindo ao sistema HealtSys!\n");
    char menu[] = "1 - Consultar paciente\n2 - Atualizar paciente\n3 - Remover paciente\n4 - Inserir paciente\n5 - Imprimir lista de pacientes\nQ - Sair";
    

    while (opcao != 'Q')
    {   
        
        printf("%s\n", menu);
        
        scanf(" %c", &opcao);
        printf("%c\n", opcao);
        // função linux abaixo, comentar quando for rodar em windows
        //system("clear");
       

        switch (opcao)
        {
        case '0':{
            printf("...");
            break;
        }
        case '1':{
            printf("função 1\n");
            break;
        }
        case '2':{
            printf("função 2\n");
            break;
        }case '3':{
            printf("função 3\n");
            break;
        }case '4':{
            printf("função 4\n");
            break;
        }case '5':{
            printf("função 5\n");
            break;
        }case 'Q':{
            printf("byby");
            break;
        }
        default:
            printf("opção invalida\n");
            break;
        }

             
    }
    printf("fim de programa");
    return 0;

}
