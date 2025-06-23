#include <stdio.h>
 
int main() {
 
    int i = 1, j = 7;

	while(i <= 9)
	{
		printf("I=%d J=%d\n", i, j);
		if(j < i+5)
		{
			i += 2;
			j = i + 6;
		} else
			j--;
	}
 
    return 0;
}