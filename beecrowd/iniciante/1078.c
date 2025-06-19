#include <stdio.h>
 
void mutiplication_table(int num)
{
	int i = 1;

	while(i <= 10)
	{
		printf("%d x %d = %d\n", i, num, (i * num));
		i++;
	}
}

int main() {
 
	int num;

	scanf("%d", &num);

	mutiplication_table(num);

    return 0;
}