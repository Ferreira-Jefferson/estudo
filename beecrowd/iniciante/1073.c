#include <stdio.h>

int show_scared(int qtt)
{
	int i = 2;
	int value;

	while(i <= qtt)
	{
		value = i * i;
		printf("%d^2 = %d\n", i, value);
		i += 2;
	}
}

int main() {
 
    int qtt;

	scanf("%d", &qtt);

	show_scared(qtt);
 
    return 0;
}