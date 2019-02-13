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
const char *filePath = "/Users/omar/empregados.txt";

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
    {
        free(*field);
    }
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
    {
        free(*s);
    }
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

void initEmpregado(pEmpregado e)
{
    e->nome = 0;
    e->cargo = 0;
    e->email = 0;
    e->idade = 0;
    e->salario = 0.0f;
}

void freeEmpregado(pEmpregado e)
{
    if (e->nome)
    {
        free(e->nome);
        e->nome = 0;
    }
    if (e->cargo)
    {
        free(e->cargo);
        e->cargo = 0;
    }
    if (e->email)
    {
        free(e->email);
        e->email = 0;
    }
}

float compararSalario(void *x, void *y)
{
    pEmpregado a = (*(pEmpregado *)x);
    pEmpregado b = (*(pEmpregado *)y)

	if(a.salario < b.salario)
		return -1;
	else if(a.salario > b.salario)
		return 1;
	else
		return 0;
}

float compararNome(void *x, void *y)
{
    pEmpregado a = (*(pEmpregado *)x);
    pEmpregado b = (*(pEmpregado *)y);

	//strcmp
}

float compararCargo(void *x, void *y)
{
    pEmpregado a = (*(pEmpregado *)x);
    pEmpregado b = (*(pEmpregado *)y);

	//strcmp
}

int main(int argc, const char * argv[])
{
    char op = 0;
    int numEmpregados = 0;
    int empregadoSelecionado = -1;
    pEmpregado *empregados = 0;

    FILE *fp = fopen(filePath, "r");
    if (fp)
    {
        fread(&numEmpregados, sizeof(int), 1, fp);
        //aloca a lista
        empregados = malloc(sizeof(pEmpregado) * numEmpregados);
        int i = 0;
        for (i = 0; i < numEmpregados; i++)
        {
            empregados[i] = malloc(sizeof(sEmpregado));
            initEmpregado(empregados[i]);
            lerEmpregado(empregados[i],fp);
        }
        fclose(fp);
    }
    else
    {

    }


    while (1)
    {
        printf("O que você quer fazer? l = listar, s = selecionar, n = novo, r = remover, p = print, e = editar, o = ordenar, q = sair: ");
        op = (char) fgetc(stdin);
        if (op != '\n')
            fgetc(stdin);
        switch (op)
        {
            case 's' :
            {
                printf("Digite o número do empregado que você quer selecionar: ");
                scanf("%d", &empregadoSelecionado);
                if (empregadoSelecionado < 0 || empregadoSelecionado >= numEmpregados)
                {
                    printf("Seleção inválida. Tente novamente.\n");
                    empregadoSelecionado = -1;
                    continue;
                }
                printf("Você selecionou o empregado %s\n", empregados[empregadoSelecionado]->nome);
                break;
            }
            case 'n':
            {
                pEmpregado *empregadosTemp = 0;
                numEmpregados++;
                empregadosTemp = malloc(sizeof(pEmpregado) * numEmpregados);
                if (numEmpregados > 1)
                {
                    memcpy(empregadosTemp, empregados, sizeof(pEmpregado) * (numEmpregados-1));
                    free(empregados);

                }
                empregados = empregadosTemp;
                empregadoSelecionado = numEmpregados-1;
                empregadosTemp[empregadoSelecionado] = malloc(sizeof(sEmpregado));
                initEmpregado(empregadosTemp[empregadoSelecionado]);

                editarEmpregado(empregados[empregadoSelecionado]);
                break;
            }
            case 'r':
            {
                if (empregadoSelecionado < 0 || empregadoSelecionado >= numEmpregados)
                {
                    printf("Seleção inválida. Tente novamente.\n");
                    continue;
                }

                freeEmpregado(empregados[empregadoSelecionado]);
                free(empregados[empregadoSelecionado]);
                int i = 0;
                for (i = empregadoSelecionado+1; i < numEmpregados; i++)
                {
                    empregados[i-1] = empregados[i];
                }
                numEmpregados--;
                break;
            }
            case 'e':
            {
                if (empregadoSelecionado == -1 || empregadoSelecionado >= numEmpregados)
                {
                    printf("Selecione um empregado primeiro.\n");
                    continue;
                }
                editarEmpregado(empregados[empregadoSelecionado]);
            }
                break;
            case 'p':
            {
                if (empregadoSelecionado == -1 || empregadoSelecionado >= numEmpregados)
                {
                    printf("Selecione um empregado primeiro.\n");
                    continue;
                }
                printEmpregado(empregados[empregadoSelecionado]);
            }
                break;
            case 'l':
            {
                //listar
                printf("Total empregados: %d\n", numEmpregados);
                int i = 0;
                for (i = 0; i < numEmpregados; i++)
                {
                    printEmpregado(empregados[i]);
                }
                break;
            }
            case 'o':
            {
                int tipoOrdenacao;

                if(numEmpregados == 0) {
                    printf("Sem usuario cadastrado.\n");
                    continue;
                }

                ordenarNovamente:

                //Ordenar
                printf("Selecione o tipo de ordenacao: 1 - nome, 2 - salario ou 3 - cargo: ");
                scanf("%d", &tipoOrdenacao);

                switch (tipoOrdenacao) {
                case 1:
                    {
                        qsort(empregados, numEmpregados, sizeof(pEmpregado), compararNome);
                        break;
                    }
                case 2:
                    {
                        qsort(empregados, numEmpregados, sizeof(pEmpregado), compararSalario);
                        break;
                    }
                case 3:
                    {
                        qsort(empregados, numEmpregados, sizeof(pEmpregado), compararCargo);
                        break;
                    }
                default:
                    {
                        printf("Opcao invalida\n");
                        goto ordenarNovamente;
                        continue;
                    }
                }

                break;
            }

            case 'q':
            {
                goto end;
            }
            default:
                break;
        }
    }

    //salvar:
end:
    fp = fopen(filePath, "w");
    if (fp)
    {
        fwrite(&numEmpregados, sizeof(int), 1, fp);
        int i = 0;
        for (i = 0; i < numEmpregados; i++)
        {
            salvarEmpregado(empregados[i], fp);
            freeEmpregado(empregados[i]);
            free(empregados[i]);
        }
        free(empregados);
        fclose(fp);
    }
    else
    {
        printf("Erro ao abrir/criar o arquivo %s\n", filePath);
    }

    return 0;
}
