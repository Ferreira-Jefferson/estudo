#include <stdio.h>
#include <threads.h>
#include <unistd.h>

int pedido_pronto = 0;
int num_pedido;
mtx_t mtx_pedido_pronto;
cnd_t cnd_pedido_pronto;

int chef(void *args)
{
	int *pedidos = (int*) args;
	int i = 0;

	while(i < 10)
	{
		printf("[chef] Preparando pedido: %d\n", pedidos[i]);
		
		sleep(1);

		mtx_lock(&mtx_pedido_pronto);
			num_pedido = pedidos[i];
			pedido_pronto = 1;
			cnd_signal(&cnd_pedido_pronto);
		mtx_unlock(&mtx_pedido_pronto);
		
		printf("[chef] Pedido %d pronto.\n", pedidos[i]);
		i++;
	}
	printf("[chef] Fim dos pedidos.\n");

	mtx_lock(&mtx_pedido_pronto);
		pedido_pronto = -1;
		cnd_signal(&cnd_pedido_pronto);
	mtx_unlock(&mtx_pedido_pronto);

	return (0);
}

int garcom(void *args)
{
	int id = *(int*) args;

	while(1) {
		mtx_lock(&mtx_pedido_pronto);
		while(!pedido_pronto)
			cnd_wait(&cnd_pedido_pronto, &mtx_pedido_pronto);
	
		if(pedido_pronto == -1)
		{
			mtx_unlock(&mtx_pedido_pronto);
			break;
		}
			
		printf("[garcom %d] entregando pedido %d.\n", id, num_pedido);
		sleep(1);
	
		pedido_pronto = 0;
		printf("[garcom %d] Pedido %d entregue.\n", id, num_pedido);
		mtx_unlock(&mtx_pedido_pronto);		
		
	}

	return (0);
}

int main(void)
{
	thrd_t v_chef;
	thrd_t v_garcom;
	int pedidos[10] = {0,1,2,3,4,5,6,7,8,9};
	int id_garcom = 33;

	mtx_init(&mtx_pedido_pronto, mtx_plain);
	cnd_init(&cnd_pedido_pronto);
	 
	thrd_create(&v_chef, chef, pedidos);
	thrd_create(&v_garcom, garcom, &id_garcom);


	thrd_join(v_chef, NULL);
	thrd_join(v_garcom, NULL);

	mtx_destroy(&mtx_pedido_pronto);
	cnd_destroy(&cnd_pedido_pronto);

	return (0);
}
