#include <stdio.h>

void sum_range(int a, int b)
{
	if(a > b)
	{
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}

	int i = a;
	int cont = 0;
	while(i <= b)
	{
		cont += i;
		printf("%d ", i);
		i++;
	}
	printf("Sum=%d\n", cont);
}

int main() {
	int a, b;

	while(1)
	{
		scanf("%d %d%*c", &a, &b);
		if(a <= 0 || b <= 0)
			break ;
		sum_range(a, b);
	}
    
    return 0;
}