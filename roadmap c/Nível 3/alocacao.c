#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Reserva um blodo de memória com o tamanho solicitado
    int *vet_malloc =  (int*) malloc(5 * sizeof(int));
    if(!vet_malloc)
    {
        printf("Erro no malloc\n");
        return (1);
    }

    // Reserva um blodo de memória e já inicia todos os blocos com o 0 do tipo
    int *vet_calloc =  (int*) calloc(5, sizeof(int));
    if(!vet_calloc)
    {
        printf("Erro no calloc\n");
        return (1);
    }

    // Redefine o tamanho de um blodo de memória de memória
    vet_malloc = (int*) realloc(vet_malloc, sizeof(int));
    if(!vet_malloc)
    {
        printf("Erro no realloc\n");
        return (1);
    }

    // Libera espaços alocados dinâmicamente
    free(vet_malloc);
    free(vet_calloc);

    return (0);
}