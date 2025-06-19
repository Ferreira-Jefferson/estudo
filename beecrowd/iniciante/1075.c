#include <stdio.h>
 
void remains_2(int num)
{
	int i = 1;

	while(i < 10000)
	{
		if((i % num) == 2)
			printf("%d\n", i);
		i++;
	}
}

int main() {
 
	int num;

	scanf("%d", &num);

	remains_2(num);

    return 0;
}