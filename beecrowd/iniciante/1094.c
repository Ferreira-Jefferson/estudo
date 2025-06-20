#include <stdio.h>
 
int main() {
 
    int qtt;
	int qtt_animal;
	char animal;
	int i = 0;
	struct {
		double total;
		double coelho;
		double rato;
		double sapo;
	} accumulator = {0, 0, 0, 0};


	scanf("%d", &qtt);

	while (i < qtt)
	{
		scanf("%d %c%*c", &qtt_animal, &animal);

		if(animal == 'C')
		{
			accumulator.coelho += (double) qtt_animal;
		} 
		else if(animal == 'R')
		{
			accumulator.rato += (double) qtt_animal;
		} else {
			accumulator.sapo += (double) qtt_animal;
		}
		accumulator.total += (double) qtt_animal;
		i++;
	}

	printf("Total: %d cobaias\n", (int) accumulator.total);
	printf("Total de coelhos: %d\n", (int) accumulator.coelho);
	printf("Total de ratos: %d\n", (int) accumulator.rato);
	printf("Total de sapos: %d\n", (int) accumulator.sapo);
	printf("Percentual de coelhos: %.2f %%\n", (accumulator.coelho / accumulator.total) * 100);
	printf("Percentual de ratos: %.2f %%\n", (accumulator.rato / accumulator.total) * 100);
	printf("Percentual de sapos: %.2f %%\n", (accumulator.sapo / accumulator.total) * 100);
 
    return 0;
}