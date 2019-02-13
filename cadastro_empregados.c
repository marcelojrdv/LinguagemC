//
//  main.c
//  AulaC_SaveStruct
//
//  Created by Omar on 14/02/17.
//  Copyright © 2017 IMD. All rights reserved.
//

//para fread, fwrite, printf etc
#include <stdio.h>
//para o malloc e free
#include <stdlib.h>
//para o strlen e strcpy
#include <string.h>

//caminho do arquivo onde vamos ler e escrever
const char *filePath = "C:/Users/marcelo.junior/Desktop/Projetos/empregado.txt";

//a estrutura de um Empregado
typedef struct
{
    char *nome;
    char *cargo;
    char *email;
    int idade;
    float salario;
} sEmpregado, *pEmpregado;

//permite ler um campo de texto, sem desperdiçar memória
void readField(const char* fieldName, char** field)
{
    //buffer temporário
    char buffer[500];
    printf("Digite %s do empregado: ", fieldName);
    scanf("%s", buffer);
    //se não foi digitado nem um caracter, não altera o campo
    if (!strlen(buffer))
        return;
    //se já tinha memória alocada, libera
    if (*field)
        free(*field);
    //aloca nova memória do tamanho necessário
    *field = malloc(sizeof(char) * (strlen(buffer)+1));
    //copia a string do buffer para a sua posição definitiva
    strcpy(*field, buffer);
}

void editarEmpregado(pEmpregado e)
{
    //permitir que o usuário digite valores para todos os campos
    readField("o nome", &(e->nome));
    readField("o cargo", &(e->cargo));
    readField("o email", &(e->email));
    printf("Digite a idade: ");
    scanf("%d", &(e->idade));
    printf("Digite o salário: ");
    scanf("%f", &(e->salario));
}

// salva uma string em um arquivo, usando o formato
// <comprimento da string><string><\0>
void saveField(const char *s, FILE *fp)
{
    int len = 0;
    //calcula o tamanho da string
    len = (int) strlen(s);
    //salva o tamanho
    fwrite(&len, sizeof(int), 1, fp);
    //salva a string
    fwrite(s, sizeof(char), len+1, fp);
}

void salvarEmpregado(pEmpregado e, FILE *fp)
{
    //salvar o Empregado no arquivo fp
    saveField(e->nome, fp);
    saveField(e->cargo, fp);
    saveField(e->email, fp);
    fwrite(&(e->idade), sizeof(int), 1, fp);
    fwrite(&(e->salario), sizeof(float), 1, fp);
}

//carrega uma string de arquivo
void loadField(char **s, FILE *fp)
{
    int len = 0;
    //le o tamanho da string
    fread(&len, sizeof(int), 1, fp);
    //libera memória se necessário
    if (*s)
        free(s);
    //aloca memória
    *s = malloc(sizeof(char) * (len+1));
    //le a string
    fread(*s, sizeof(char), len+1, fp);
}

void lerEmpregado(pEmpregado e, FILE *fp)
{
    //ler um Empregado do arquivo fp
    loadField(&(e->nome), fp);
    loadField(&(e->cargo), fp);
    loadField(&(e->email), fp);
    fread(&(e->idade), sizeof(int), 1, fp);
    fread(&(e->salario), sizeof(float), 1, fp);
}

void printEmpregado(pEmpregado e)
{
    //mostra todos os campos de um empregado na tela
    printf("Nome: %s\n", e->nome);
    printf("Cargo: %s\n", e->cargo);
    printf("Email: %s\n", e->email);
    printf("Idade: %d\n", e->idade);
    printf("Salário: %.02f\n", e->salario);
}



int main(int argc, const char * argv[])
{
    char op = 0;

    sEmpregado e;
    initEmpregado(&e);
    //memset(&e, 0, sizeof(sEmpregado));

    while (1)
    {
        printf("O que você quer fazer? c = carregar, s = salvar, p = print, e = editar, q = sair: ");
        scanf("%c", &op);
        switch (op)
        {
            case 'e':
            {
                editarEmpregado(&e);
            }
                break;
            case 'p':
            {
                printEmpregado(&e);
            }
                break;
            case 's':
            {
                FILE *fp = fopen(filePath, "w");
                if (fp)
                {
                    salvarEmpregado(&e, fp);
                    fclose(fp);
                }
                else
                {
                    printf("Erro ao abrir/criar o arquivo %s\n", filePath);
                }
            }
                break;
            case 'c':
            {
                FILE *fp = fopen(filePath, "r");
                if (fp)
                {
                    lerEmpregado(&e,fp);
                    fclose(fp);
                }
                else
                {
                    printf("Erro ao abrir o arquivo %s\n", filePath);
                }

            }
                break;
            case 'q':
            {
                if (e.nome)
                    free(e.nome);
                if (e.cargo)
                    free(e.cargo);
                if (e.email)
                    free(e.email);
                printf("Goodbye!\n");
                return 0;
            }
            default:
                break;
        }
    }

    return 0;
}

void initEmpregado(pEmpregado e)
{
    e->nome = 0;
    e->cargo = 0;
    e->email = 0;
    e->idade = 0;
    e->salario = 0.0f;
}
