#include <stdio.h>

static int static_global = 10; // Uma variável global estática só pode ser vista no arquivo .c que foi declarada

void contador()
{
	int normal_cont = 10;
	static int static_cont = 10; 
	// Variáveis estáticas mantém o seu valor mesmo após a morte da função que a criou

	normal_cont++;
	static_cont++;
	printf("normal_cont: %d \n", normal_cont);
	printf("static_cont: %d \n", static_cont); 
	printf("\n");
}

int	main(void)
{
	printf("static_global: %d \n\n", static_global);

	contador();
	contador();
	contador();
	return (0);
}
