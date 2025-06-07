#include <stdio.h>

void show_answer(int N)
{
	int i = 0;
	int num;
	int in = 0;
	int out = 0;

	while(i < N)
	{
		scanf("%d%*c", &num);
		if(num >= 10 && num <= 20)
			in++;
		else
			out++;
		i++;
	}
	printf("%d in\n", in);
	printf("%d out\n", out);
}

int main() {
	int N;

	scanf("%d", &N);	

	show_answer(N);  
	 
    return 0;
}