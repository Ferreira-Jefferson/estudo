#include <stdio.h>
#include <threads.h>

// threads é um pouco mais intuitivo, mas também mais liitada, como é o caso do retorno,
// como ela retorna apenas um int, o retorno deve ser feito passando um ponteiro de retorno via args

int funcao(void *args)
{
	int valor = *(int*) args;
	printf("Valor: %d\n", valor);
	return (0);
}

int main(void)
{
	thrd_t thread;
	int valor = 10;
	 
	thrd_create(&thread, funcao, &valor);
	thrd_join(thread, NULL);

	return (0);
}
