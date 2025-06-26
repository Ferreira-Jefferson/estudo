#include <stdio.h>
 
int show_quadrant(int x, int y)
{
	if(x > 0 && y > 0)
		printf("primeiro\n");
	else if(x < 0 && y > 0)
		printf("segundo\n");
	else if(x < 0 && y < 0)
		printf("terceiro\n");
	else
		printf("quarto\n");
}

int main() {
 
    int x, y;

	while(1)
	{
		scanf("%d %d%*c", &x, &y);
		if(x == 0 || y == 0)
			break ;
		show_quadrant(x, y);
	}
 
    return 0;
}