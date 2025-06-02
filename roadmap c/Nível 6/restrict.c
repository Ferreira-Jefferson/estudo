#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// O restrict informa ao compilador que ele não precisa ficar fazendo validações se dois ponteiros se sobrepõem
// Ou seja, se eu tenho a[20]; e aponto *b = &a[1] e *c = &a[10] => *b e *c se sobrepõem, pois ao percorrer um eu passo no endereço que outro compartilha
// Quando informamos que a sobreposição não irá ocorrer, o compilador tem que fazer menos validações, o que pode tornar o algorítmo mais rápido

#define TAM 100000000
void funcao(volatile const int *restrict vet, int *restrict vet2)
{
	long i = 0;
	while(i < TAM)
	{
		vet2[i] = vet[i] << 10;
		i++;
	}
}

int main(void)
{
	clock_t start, end;
	double time;
	int *vet = (int*) malloc(TAM * sizeof(int));
	int *vet2 = (int*) malloc(TAM * sizeof(int));

	start = clock();

	memset(vet, 1, sizeof(vet));

	long i = 0;
	while(i < TAM)
	{
		vet[i] = vet[i] << 10;
		i++;
	}

	funcao(vet, vet2);

	end = clock();

	time = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Tempo de execução: %.6lf\n", time);

	free(vet);
	free(vet2);

	return (0);
}