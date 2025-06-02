#include <stdio.h>

int	main(void)
{
	int valor = -256;
	
	printf("x1: %d\n", valor >> 1); // x1: 128
	printf("x2: %d\n", valor >> 2); // x2: 64
	printf("x3: %d\n", valor >> 3); // x3: 32
	printf("x4: %d\n", valor >> 4); // x4: 16
	printf("x5: %d\n", valor >> 5); // x5: 8
	printf("x6: %d\n", valor >> 6); // x6: 4
	printf("x7: %d\n", valor >> 7); // x7: 2
	printf("x8: %d\n", valor >> 8); // x8: 1
	
	return (0);
}