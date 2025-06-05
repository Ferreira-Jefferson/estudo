/*
Exercício: Caixa Registradora Simulada

Imagine que você está programando uma caixa registradora para um supermercado. 
Múltiplos clientes podem estar fazendo pagamentos ao mesmo tempo, 
e cada um deve registrar corretamente o valor total no sistema. No entanto, 
apenas um cliente por vez pode acessar o saldo total da loja para atualizar o valor corretamente.

Objetivo:

Simular 5 clientes fazendo compras simultaneamente.

Cada cliente adiciona um valor aleatório ao saldo total do supermercado.

Evite condições de corrida usando mutex, garantindo que os valores sejam somados corretamente.

Perguntas para reflexão enquanto desenvolve:
O que pode acontecer se dois clientes acessarem e modificarem o saldo ao mesmo tempo?

Como garantir que apenas um cliente por vez atualize o saldo corretamente?

O que acontece se o mutex não for usado nesse programa?

Esse exercício vai ajudar a visualizar problemas reais de concorrência e como o mutex pode garantir integridade nos dados compartilhados. 🚀

Se quiser mais desafios, só me avisar! 😃
*/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex_impede_corrida = PTHREAD_MUTEX_INITIALIZER;
int total_thread = 0;

void *caixa_registradora(void* args)
{
	int valor = *(int*) args;

	pthread_mutex_lock(&mutex_impede_corrida);
	total_thread += valor;
	pthread_mutex_unlock(&mutex_impede_corrida);

	printf("args: %d\n", valor);

	return NULL;
}

int main(void)
{
	int quantidade_clientes = 5;
	pthread_t threads[quantidade_clientes];
	int valores[quantidade_clientes];
	int i = 0;
	int total = 0;

	while (i < quantidade_clientes)
	{
		valores[i] = (i + 1) * quantidade_clientes + 10;
		total += valores[i] ;
		printf("antes: %d\n", valores[i] );
		pthread_create(&threads[i], NULL, caixa_registradora, &valores[i]);
		i++;
	}

	i = 0;
	while (i < quantidade_clientes)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	

	printf("Total da main: %d\n", total);
	printf("Total da thread: %d\n", total_thread);

	pthread_mutex_destroy(&mutex_impede_corrida);
	return (0);
}
