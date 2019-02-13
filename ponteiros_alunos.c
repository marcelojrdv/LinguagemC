#include <stdio.h>
#include <stdlib.h>

//#define limparAluno(x) \#printf("Limpando aluno");

#define \
    limparAluno(x) \
    ({ \
        int xx = (x); \
        int result = (xx > 32) ? xx : (2*xx); \
        result; \
    })


typedef struct {
    int     idade;
    float   altura;
    char    *nome;
} sAluno, *pAluno;

void limparAluno(pAluno x) {
    x->idade    = 0;
    x->altura   = 0;
    x->nome     = 0;
}

int main(int argc, const char * argv[])
{
    sAluno aluno;
    pAluno ponteiroAluno = &aluno;

    limparAluno(&aluno);

    printf("No inicio o Aluno tem idade %d\nAltura %f\nNome %s\n\n", ponteiroAluno->idade, ponteiroAluno->altura, ponteiroAluno->nome);

    printf("Digite a idade do aluno: ");
    scanf("%d", &(ponteiroAluno->idade));

    printf("Digite a altura do aluno: ");
    scanf("%f", &(ponteiroAluno->altura));

    printf("Digite o nome do aluno: ");
    scanf("%s", &(ponteiroAluno->nome));


    /** Resutado */
    printf("O Aluno tem idade %d\nAltura %f\nNome %s\n\n", ponteiroAluno->idade, ponteiroAluno->altura, ponteiroAluno->nome);

    return 0;
}
