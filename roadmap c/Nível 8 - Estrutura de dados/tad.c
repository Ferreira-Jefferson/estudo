// https://www.facom.ufu.br/~backes/wordpress/ListaED01-Tad.pdf

/*
Crie um Tipo Abstrato de Dados (TAD) que represente os numeros racionais e que con- ´
tenha as seguintes funções:
(a) Cria racional;
(b) Soma racionais;
(c) Multiplica racionais;
(d) Testa se sao iguais;
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct racional {
	int numerador;
	int denominador;
} Racional;

Racional* criar(int p, int q)
{
	if(q == 0)
		return (NULL);

	Racional *racional = (Racional*) malloc(sizeof(Racional));
	if(!racional)
	{
		perror("Error na criacao\n");
		return (NULL);
	}

	racional->numerador = p;
	racional->denominador = q;
	return (racional);
}

Racional *somar(Racional *r1, Racional *r2)
{
	Racional *racional = (Racional*) malloc(sizeof(Racional));
	if(!racional)
	{
		perror("Erro na soma\n");
		return (NULL);
	}

	if(r1->denominador == r2->denominador)
	{
		racional->numerador = r1->numerador + r2->numerador;
		racional->denominador = r1->denominador;
		return (racional);
	}

	int den_comum = r1->denominador * r2->denominador;
	racional->numerador = (den_comum / r1->denominador) * r1->numerador  + (den_comum / r2->denominador) * r2->numerador;
	racional->denominador = den_comum;

	return (racional);
}

Racional *multiplicar(Racional *r1, Racional *r2)
{
	Racional *racional = (Racional*) malloc(sizeof(Racional));
	if(!racional)
	{
		perror("Erro na multiplicacao\n");
		return (NULL);
	}

	racional->numerador = r1->numerador * r2->numerador;
	racional->denominador = r1->denominador * r2->denominador;;

	return (racional);
}

int sao_iguais(Racional *r1, Racional *r2)
{
	return (r1->numerador == r2->numerador && r1->denominador == r2->denominador);
}

int main(void)
{
	Racional *r1 = criar(1, 2);
	Racional *r2 = criar(2, 3);

	Racional *r_soma = somar(r1, r2);
	printf("soma: %d/%d\n", r_soma->numerador, r_soma->denominador);

	Racional *r_multip = multiplicar(r1, r2);
	printf("multiplicacao: %d/%d\n", r_multip->numerador, r_multip->denominador);

	printf("São iguais? %d\n", sao_iguais(r_soma, r_multip));

	free(r1);
	free(r2);
	free(r_soma);
	free(r_multip);
	return (0);
}