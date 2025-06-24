#include <stdio.h>

int sum_odd(int a, int b)
{
	if(a > b)
	{
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}

	int i = a + 1;
	int cont = 0;
	while(i < b)
	{
		if(i & 0x1)
			cont += i;
		i++;
	}
	return (cont);
}

int main() {
	int a, b, qtt;
	int i = 0;

	scanf("%d%*c", &qtt);

	while(i < qtt)
	{
		scanf("%d %d%*c", &a, &b);
		printf("%d\n", sum_odd(a, b));
		i++;
	}
    
    return 0;
}