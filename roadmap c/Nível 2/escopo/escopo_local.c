#include <stdio.h>

int	main(void)
{
	int i = 10;

	// Variáveis quando declaradas entre chaves tem só existem neste escopo {}
	// E não dão conflito com variáveis de mesmo nome declaradas fora do escopo
	if(i >= 10)
	{
		
		printf("if antes: %d \n", i); // 10

		int i = 20;
		printf("if: %d \n", i); // 20
		i = 30;
	}
	
	// Aqui daria um erro, mas de qualquer forma não é uma declaração útil
	// if (i == 10)
	// 	int i = 40;

	printf("%d \n", i); // 10
	return (0);
}
