#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_GARCONS 5

pthread_mutex_t mutex_pedido = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_pedido_pronto = PTHREAD_COND_INITIALIZER;

int pedido_pronto = 0;
int acabou_pedidos = 0;


int qtd = 5;
void* chef(void* args)
{
	int i = 0;
	while(i < NUM_GARCONS)
	{
		pthread_mutex_lock(&mutex_pedido);
		printf("Chef: preprando pedido %d\n", i+1);
		sleep(1);

		pedido_pronto = 1;
		printf("Chef: pedido %d pronto\n", i+1);

		pthread_cond_broadcast(&cond_pedido_pronto);
		pthread_mutex_unlock(&mutex_pedido);

		sleep(1); 
		i++;
	}
	pthread_mutex_lock(&mutex_pedido);
    acabou_pedidos = 1;
    pthread_cond_broadcast(&cond_pedido_pronto);  // Libera garçons que ainda estiverem esperando
    pthread_mutex_unlock(&mutex_pedido);
	return (NULL);
}

void* garcom(void* args)
{
	int id = *(int*) args;

	while(1)
	{
		pthread_mutex_lock(&mutex_pedido);
		while(!pedido_pronto && !acabou_pedidos)
		{
			pthread_cond_wait(&cond_pedido_pronto, &mutex_pedido);
		}

		if(acabou_pedidos)
		{
			pthread_mutex_unlock(&mutex_pedido);
			break;
		}

		printf("Garcom %d: entreguando pedido.\n", id);
		pedido_pronto = 0;
		pthread_mutex_unlock(&mutex_pedido);
		sleep(3);
		printf("Garcom %d: pedido entregue\n\n", id);
	}
	return (NULL);
}

int main()
{
	pthread_t th_chef;
	pthread_t th_garcom[qtd];
	int id[qtd];
	int i;

	pthread_create(&th_chef, NULL, chef, NULL);

	i = 0;
	while(i < qtd)
	{
		id[i] = i + 1;
		pthread_create(&th_garcom[i], NULL, garcom, &id[i]);
		i++;
	}

	pthread_join(th_chef, NULL);

	i = 0;
	while(i < qtd)
		pthread_join(th_garcom[i++], NULL);

	pthread_mutex_destroy(&mutex_pedido);
	pthread_cond_destroy(&cond_pedido_pronto);

	printf("Restaurante encerrando operações!\n");

	return (0);
}