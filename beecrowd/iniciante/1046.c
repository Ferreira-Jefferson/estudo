#include <stdio.h>

void calculate_duration(int start, int end)
{
	int duration = 24 - start + end;

	if(duration > 24)
		duration -= 24;

	printf("O JOGO DUROU %d HORA(S)\n", duration);
}

int main() {
 
	int start, end;

	scanf("%d %d", &start, &end);

	calculate_duration(start, end);

    return 0;
}