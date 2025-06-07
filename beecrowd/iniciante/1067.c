#include <stdio.h>
 
void show_odd(int max_num)
{
	int i = 1;
	while(i <= max_num)
	{
		if(i & 0b1)
			printf("%d\n", i);
		i++;
	}
}

int main() {
 
	int num;

	scanf("%d", &num);

	show_odd(num);

    return 0;
}