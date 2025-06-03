#include <stdio.h>

void show_even(void)
{
	int i = 1;

	while (i <= 100)
	{
		if(!(i & 0x1))
			printf("%d\n", i);
		i++;
	}
	
}

int main(void) {
 
    show_even();
 
    return (0);
}