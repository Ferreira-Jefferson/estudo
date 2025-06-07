#include <stdio.h>
 
void show_sum_odd(int start, int end)
{
	int sum = 0;
	start++;
	while(start < end)
	{
		if(start & 0b1) {
			sum += start;
		}
		start++;
	}
	printf("%d\n", sum);
}

int main() {
 
	int num1, num2;

	scanf("%d", &num1);
	scanf("%d", &num2);

	if(num2 < num1)
	{
		num1 = num1 ^ num2;
		num2 = num1 ^ num2;
		num1 = num1 ^ num2;
	}

	show_sum_odd(num1, num2);

    return 0;
}