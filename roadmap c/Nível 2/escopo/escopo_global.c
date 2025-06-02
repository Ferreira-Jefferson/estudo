#include <stdio.h>

int global = 10;
const int global_const = 50; // const são ready-only

void fun()
{
	printf("global fun: %d\n", global); // 10;
	global = 20; // O perigo de variáveis globais que não é constante é que algum trecho do código pode aterá-la
}

int	main(void)
{

	printf("global antes: %d\n", global);
	fun();
	printf("global depois: %d\n\n", global);

	// global_const = 100; // Aqui daria um erro pois const não podem ser alteradas 
	printf("global const: %d\n", global_const);
	return (0);
}
