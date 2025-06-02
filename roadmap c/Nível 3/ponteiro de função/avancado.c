#include <stdio.h>
#include <stdlib.h>

int adicao(int a, int b)
{
    return (a + b);
}

int subtracao(int a, int b)
{
    return (a - b);
}

int multiplicacao(int a, int b)
{
    return (a * b);
}

int callback(int a, int b, int (*pt_operacao)(int, int))
{
    return pt_operacao(a, b);
}

int main(void)   
{
    int resultado;
    int i;

    // Também é possível criar um vetor de ponteiros para funções
    int (*pt_vet[3])(int, int) = {adicao, subtracao, multiplicacao};

    i = 0;
    while(i < 3)
    {
        resultado = callback(5, 3, pt_vet[i]);
        printf("Resultado: %d \n", resultado);
        i++;
    }
    printf("\n");
    
    // Outra forma de declarar é com ponteiro de ponteiro.
    int (**ppt_vet)(int, int);
    
    ppt_vet = (int (**)(int, int)) malloc(3 * sizeof(int (*)(int, int)));

    ppt_vet[0] = adicao;
    ppt_vet[1] = subtracao;
    ppt_vet[2] = multiplicacao;
    
    i = 0;
    while(i < 3)
    {
        resultado = callback(10, 6, ppt_vet[i]);
        printf("Resultado: %d \n", resultado);
        i++;
    }
    free(ppt_vet);
    return (0);
}