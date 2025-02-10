# Simulação de sistema de pacientes
Este repositório tem por objetivo armazenar os códigos elaborados no Trabalho de Programação da disciplina de Estruturas de Dados [2024/2], ministrada pelo Prof. Thiago M. Paixão ([@thiagopx](https://github.com/thiagopx)).

### Autores

- Pedro Renã da Silva Moreira: [@Pedrordsm](https://github.com/Pedrordsm)
- Tertuliano dos Santos Junior: [@tertulho](https://github.com/tertulho)

# Sobre o trabalho

O trabalho prático de programação consiste em implementar um sistema (simplificado) de gerenciamento
de dados de pacientes de uma clínica em linguagem C. Os dados são armazenados (persistidos)
em um arquivo texto CSV e carregados em uma estrutura de dados específica (memória) para execução
do sistema. O sistema deve permitir cadastro de pacientes, consulta, atualização e exclusão de registros.

> A especificação completa do trabalho pode ser lida acessando o arquivo trabalho-prático.pdf

# Instalação e Execução
Certifique-se de conter pré-instalado em seu sistema um **compilador C (por exemplo, GCC)**. 
 
Para instalar o programa em seu computador, siga os passos a seguir:
1. Clone o repositório em seu Desktop e salve-o no local desejado:
```bash
git clone https://github.com/tertulho/Trabalho_Est
```
2. Abra seu terminal, escreva ```cd``` e cole o caminho no qual o repositório está salvo.

cd C:\Users\NomedoUsuario\Documents\trabalho\sistema_pacientes

3. Compile o código e execute-o digitando o seguinte comando:
```
make
```
Como resultado, serão gerados os arquivos ```programas_c.exe```, ```main_trab_est.o``` e ```paciente_func.o```. 


# Organização do projeto
O trabalho conta com os principais arquivos:

- **`bd_paciente.csv`**: contém nosso banco de dados de pacientes, com seus respectivos ids, nomes, CPF, idade e data de cadastro.
- **`paciente_func.c`**: contém as principais funções que simulam a interação com o banco de dados.
- **`paciente_func.h`**: contém o cabeçalho das funções e os structs utilizados.
- **`main_trab_est.c`**: contém o funcionamento principal do sistema, utilizando as funções criadas.

# Funcionamento do programa
Ao executar o programa, o banco de dados do arquivo csv é carregado e o usuário se depara com 6 opções:

1. Consultar paciente: A funcionalidade permite buscar as informações de um paciente utilizando Nome ou CPF.

**A saída do programa para consulta segue o padrão a seguir:**
Escolha o critério de busca:
1. Buscar por CPF
2. Buscar por Nome
3. Voltar ao menu principal
Opção: 2
Digite o nome do paciente: pedro

Paciente encontrado:
  ID: 20
  CPF: 12345678910
  Nome: pedro
  Idade: 12
  Data de Cadastro: 2003-02-20

Total de pacientes encontrados: 1

2. Atualizar paciente: A funcionalidade de atualização permite modificar os dados de um paciente existente no sistema.

**A saída do programa para atualizar o paciente segue o padrão a seguir:**
Digite o ID do paciente a ser atualizado: 4

Escolha uma das letras abaixo para modificar um dado:
n -> para atualizar o nome
i -> para atualizar a idade do paciente
c -> para atualizar o cpf
d -> para atualizar a data de cadastro
Q -> para finalizar a alteração dos dados

3. Remover paciente: A funcionalidade de remoção permite excluir um paciente existente no sistema de forma definitiva.

**A saída do programa para excluir o paciente segue o padrão a seguir:**

Digite o ID do paciente a ser removido: 
4

Tem certeza de que deseja excluir o registro abaixo? (S/N)
ID      CPF             Nome            Idade   Data_Cadastro
4       65465465465     Paixão  36      2024-01-24
S
Paciente removido com sucesso!

4. Inserir paciente: A funcionalidade de inserção permite adicionar um novo paciente ao sistema.

**A saída do programa para inserir o paciente segue o padrão a seguir:**

Digite o CPF, Nome, Idade e Data_Cadastro:
65465465465 
Paixão
36
2024-01-24  

Confirma a inserção do registro abaixo? (S/N)
ID      CPF             Nome            Idade   Data_Cadastro
23      65465465465     Paixão  36      2024-01-24
S
Paciente inserido com sucesso!

5. Imprimir lista de pacientes: A funcionalidade de impressão de lista permite exibir todos os registros de pacientes armazenados no sistema.

**A saída do programa para imprimir a lista de pacientes segue o padrão a seguir:**

ID | CPF | Nome | Idade | Data Cadastro
------------------------------------------
23 | 65465465465 | Paixão | 36 | 2024-01-24
21 | 78945678910 | josue | 22 | 2015-02-08
20 | 12345678910 | pedro | 12 | 2003-02-20
19 | 12345678901 | Jo├úo Silva | 30 | 2024-02-07
18 | 98765432100 | Maria Oliveira | 25 | 2024-02-06

6. Sair: A funcionalidade encerra o funcionamento do programa atualizando o banco de dados.
