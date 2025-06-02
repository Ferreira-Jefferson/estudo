#include <stdio.h>
#include <string.h>

void print_vet(int *vet, size_t size)
{
    int i = 0;
    while(i < size)
        printf("%d\n", vet[i++]);
}

void simple_sort(int *vet, size_t size)
{   
    int aux;
    int i;
    if(size <= 1)
        return ;
    i = 0;
    while (i < size-1) {
        if(vet[i] > vet[i+1])
        {
            aux = vet[i+1];
            vet[i+1] = vet[i];
            vet[i] = aux;
        }
        i++;
    }
    simple_sort(vet, size - 1);
}

int main(void)
{
    int vet[3];
    int copy[3];

    scanf("%d %d %d", &vet[0], &vet[1], &vet[2]);
    memcpy(copy, vet, sizeof(int)*3);

    simple_sort(copy, 3);
    print_vet(copy, 3);

    printf("\n");
    print_vet(vet, 3);

    return (0);
}