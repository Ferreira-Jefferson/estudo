#include <stdio.h>

void fun(void)
{
    printf("Olá.\n");
}

int fun2(int a, int b)
{
    return (a + b);
}

int main(void)
{
    // A declaração apesar de extensa ela apenas replíca o retorno e parâmetros que se espera
    // e dentro fica o nome do ponteiro que irá chamá-la
    // O uso do void no parâmetro, apesar de não ser obrigatório, ele deixa claro que nada deve ser passado.
    void (*pf_fun)(void);

    fun();

    pf_fun = fun;
    pf_fun();

    // Se tem N parâmetros, todos os tipos esperados devem ser passados.
    // Também pode ser passado int (*pf_fun2)(int a, int b); mas a e b não tem uso prático, nem são declarados como variáveis.
    int (*pf_fun2)(int, int);

    int value = fun2(2, 2);
    printf("Função original: %d\n", value);
    
    pf_fun2 = fun2;
    pf_fun2(2, 2);
    printf("Ponteiro da função: %d\n", value);

    return (0);
}