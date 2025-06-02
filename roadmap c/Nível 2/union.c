#include <stdio.h>
#include <string.h>

// A diferença da union pra struct é que a union usa apenas um espaço de memória, 
// considerando o tamanho da maior variável interna.
// Ela sobrescreve o valor a cada nova atribuição (mas nem sempre).
// Pode haver alguma ilusão de que o valor não foi alterado, por exemplo no union_name abaixo,
// Isso ocorre pois como é reservado um espaço para o maior valor, 
// toda a memória da cadeia pode ser utilizada e não apenas a primeira
// De char cabe no final da memoria que foi reservada ele pode entrar no final da cadeia 
// e manter a referência de ambas, só que por segurança ela não deve ser utilizada

// O uso de Union é interessante em casos que podem ter mais de uma opção declaração, 
// mas uma só uma existe por vez, como seria o caso de um método de pagamento,
// Pode ter cartão, boleto e TED, se o usuário escolher um não é necessário manter as informações do outro.


union union_name {
    int a;
    double b;
    char c;
};

union Pagamento {
    struct {
        char numero_cartao[16];
        char validade[5];
    } cartao_credito;

    struct {
        char codigo_barras[50];
    } boleto;

    struct {
        char numero_conta[20];
    } transferencia;
};

void teste_simples(void)
{
    union union_name my_union_name;

    my_union_name.a = 10;
    printf("my_union_name.a: %d\n\n", my_union_name.a);
    
    my_union_name.b = 20.0;
    printf("my_union_name.b: %f\n\n", my_union_name.b);

    my_union_name.c = 'X';
    printf("my_union_name.c: %c\n\n", my_union_name.c);

    printf("my_union_name.a: %d\n", my_union_name.a);
    printf("my_union_name.b: %f\n", my_union_name.b);
    printf("my_union_name.c: %c\n\n", my_union_name.c);
}

void teste_pagamento(void)
{
    union Pagamento pagamento;

    // Exemplo: Pagamento via cartão de crédito
    strcpy(pagamento.cartao_credito.numero_cartao, "1234123412341234");
    strcpy(pagamento.cartao_credito.validade, "12/30");

    printf("Pagamento via Cartão de Crédito:\n");
    printf("Número: %s\n", pagamento.cartao_credito.numero_cartao);
    printf("Validade: %s\n\n", pagamento.cartao_credito.validade);

    // Agora, o cliente decide pagar com boleto
    strcpy(pagamento.boleto.codigo_barras, "12345678901234567890123456789012345678901234");

    printf("Pagamento via Boleto:\n");
    printf("Código de Barras: %s\n\n", pagamento.boleto.codigo_barras);

    printf("Número cartão (sobrescrito): %s\n\n", pagamento.cartao_credito.numero_cartao);
}

int main(void)
{
    teste_simples();
    teste_pagamento();
    return (0);
}