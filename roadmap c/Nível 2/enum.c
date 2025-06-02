#include <stdio.h>

// Enum são ideais para quanto temos uma lista de opções e queremos padronizar os valores
// Por trás dos panos eles são apenas inteiros, então é sempre bom tomar cuidado.
// O ideal é ter uma função de validação para validar que os valores passados realmente existem
// O enum automaticamente define o valor das variáveis começado em 0
// Mas você também pode atribuir um valor arbitrário de sua preferência.

enum e_dias_da_semana {
    DOMINGO, SEGUNDA, TERÇA, QUARTA, QUINTA, SEXTA, SABADO
};

typedef enum e_status {
    ERROR = -1,
    SUCCESS = 1
} t_e_status;

#define VALIDAR_DIA(dia) (dia >= DOMINGO && dia <= SABADO)

int main(void)
{
    enum e_dias_da_semana hoje = SEGUNDA;
    printf("hoje: %d \n", hoje);

    int int_qualquer = 5;
    if(VALIDAR_DIA(int_qualquer))
    {
        hoje = (enum e_dias_da_semana)int_qualquer;
        printf("Dia valido: %d \n", hoje);
    }
    
    t_e_status status = ERROR;
    printf("Error: %d \n", status);

    return (0);
}