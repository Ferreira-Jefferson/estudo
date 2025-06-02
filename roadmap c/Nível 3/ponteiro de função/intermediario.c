#include <stdio.h>

int adicao(int a, int b)
{
    return (a + b);
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

    // O mais interessante para se fazer um ponteiros de funções e declarar eles como parametrôs de funções
    // Isso permite o reuso de código como no exemplo abaixo

    resultado = callback(2, 5, adicao);
    printf("Resultado: %d \n", resultado);

    resultado = callback(2, 5, multiplicacao);
    printf("Resultado: %d \n", resultado);
}