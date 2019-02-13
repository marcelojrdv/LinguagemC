#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struc do empregado
typedef struct
{
    char *nome;
    char *cargo;
    char *email;
    int idade;
    float salario;
} sEmpregado, *pEmpregado;

void salvarEmpregado(pEmpregado e, FILE *fp) {
    //Salvar empregado no arquivo
}

pEmpregado lerEmpregado(FILE *fp) {
    //Ler empregado do arquivo fp
    return 0;
}

void editarEmpregado(pEmpregado e) {
    //Ler empregado do arquivo fp
}

void printEmpregado(pEmpregado e) {
    //Mostar todos os campos de um empregado na tela
}

void initEmpregado(pEmpregado e){
    e->nome = 0;
    e->cargo = 0;
    e->email= 0;
    e->idade = 0;
    e->salario = 0.0f;
}

int main()
{
    char op = 0;

    sEmpregado e;
    initEmpregado(&e);

    printf("O que você quer fazer? c = carregar, s = salvar, p = print, e = editar, q = sair: ");
    scanf("%c", &op);
    switch (op) {
        case 'e':
            editarEmpregado(&e);
        break;
        case 'p':
            printEmpregado();
        break;
        case 's':
            //salvarEmpregado();
        break;

        case 'c':
            //
        break;
        case 'q':
            {

            }
        break;
    }

    //printf("Hello world!\n");
    return 0;
}
