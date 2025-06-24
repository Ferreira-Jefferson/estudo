#include <stdio.h>

void show_ordenation(int a, int b)
{
	if(a < b)
		printf("Crescente\n");
	else
		printf("Decrescente\n");
}
int main() {
	int a, b;

	while(1)
	{
		scanf("%d %d%*c", &a, &b);
		if(a == b)
			break ;
		show_ordenation(a, b);
	}
    
    return 0;
}