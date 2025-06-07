#include <stdio.h>
 
void show_6_odd(int start)
{
	int i = 0;
	while(1)
	{
		if(start & 0b1) {
			printf("%d\n", start);
			i++;
		}
		if(i == 6)
			break;
		start++;
	}
}

int main() {
 
	int num;

	scanf("%d", &num);

	show_6_odd(num);

    return 0;
}