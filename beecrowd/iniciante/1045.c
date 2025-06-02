#include <stdio.h>

void swap(double *a, double *b, double *c)
{
	double aux;
	double vet[3] = {*a, *b, *c};
	int i, j;

	i = 0;
	while(i < 3)
	{
		j = i + 1;
		while(j < 3)
		{
			if(vet[i] < vet[j])
			{
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
			}
			j++;
		}
		i++;
	}
	*a = vet[0];
	*b = vet[1];
	*c = vet[2];
}

double squared_number(double value)
{
	return (value * value);
}

void indentify_triangle(double a, double b, double c)
{
	if(a >= b + c) {
		printf("NAO FORMA TRIANGULO\n");
		return ;
	}

	if(squared_number(a) == squared_number(b) + squared_number(c)) 
		printf("TRIANGULO RETANGULO\n");

	if(squared_number(a) > squared_number(b) + squared_number(c))
		printf("TRIANGULO OBTUSANGULO\n");

	if(squared_number(a) < squared_number(b) + squared_number(c))
		printf("TRIANGULO ACUTANGULO\n");

	if(a == b && b == c)
		printf("TRIANGULO EQUILATERO\n");

	if((a == b && a != c) || (a == c && a != b) || (b == c && b != a))
		printf("TRIANGULO ISOSCELES\n");
}

int main() {
 
	double a, b, c;

	scanf("%lf %lf %lf", &a, &b, &c);

	swap(&a, &b, &c);
	
    indentify_triangle(a, b, c);
 
    return 0;
}