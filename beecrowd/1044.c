#include <stdio.h>

void is_multiple(int a, int b)
{
	if(b > a)
	{
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;		
	}

	if(a % b == 0)
		printf("Sao Multiplos\n");
	else
		printf("Nao sao Multiplos\n");
}

int main(void)
{
	int a, b;

	scanf("%d %d", &a, &b);

	is_multiple(a, b);

	return (0);
}