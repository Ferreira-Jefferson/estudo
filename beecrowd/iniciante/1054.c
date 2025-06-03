#include <stdio.h>
 
int main() {
 
	int i = 0;
	int count = 0;
	double number;

    while(i < 6)
	{
		scanf("%lf", &number);
		if(number > 0)
			count++;
		i++;
	}
	printf("%d valores positivos\n", count);
 
    return 0;
}