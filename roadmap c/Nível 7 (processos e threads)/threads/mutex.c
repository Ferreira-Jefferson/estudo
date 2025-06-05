#include <stdio.h>
#include <threads.h>

mtx_t mtx_contador;
int contador = 0;

int funcao(void *args)
{
	int valor = *(int*) args;

	mtx_lock(&mtx_contador);
		contador += valor;
	mtx_unlock(&mtx_contador);
	return (0);
}

int main(void)
{
	thrd_t thread[1000];
	int valores[1000];
	int i = 0;
	int cont_ref = 0;
	mtx_init(&mtx_contador, mtx_plain);
	
	while(i < 1000)
	{
		valores[i] = i;
		cont_ref += i;
		thrd_create(&thread[i], funcao, &valores[i]);
		i++;
	}

	i = 0;
	while(i < 1000)
	{
		thrd_join(thread[i], NULL);
		i++;
	}

	printf("Contador: ref: %d | cont: %d\n", cont_ref, contador);


	mtx_destroy(&mtx_contador);

	return (0);
}
