#include <stdio.h>
#include <limits.h>
 
int main() {
 
	int max = INT_MIN;
	int num;
	int i = 0;
	int pos;

	while(i < 100)
	{
    	scanf("%d%*c", &num);
		if(num > max)
		{
			max = num;
			pos = i + 1;
		}
		i++;
	}
	printf("%d\n", max);
	printf("%d\n", pos);
 
    return 0;
}