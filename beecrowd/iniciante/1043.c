#include <stdio.h>

int is_triangle(double a, double b, double c)
{
	if(!((a + b) > c))
		return (0);
	if(!((a + c) > b))
		return (0);
	if(!((b + c) > a))
		return (0);
	return (1);
}

void calculate_perimiter(double a, double b, double c)
{
	double result = a + b + c;
	printf("Perimetro = %.1lf\n", result);
}

void calculate_area(double a, double b, double c)
{
	double result = ((a + b) * c) / 2;
	printf("Area = %.1lf\n", result);
}

int main(void)
{
	double a, b, c;

	scanf("%lf %lf %lf", &a, &b, &c);

	if(is_triangle(a, b, c))
		calculate_perimiter(a, b, c);
	else
		calculate_area(a, b, c);

	return (0);
}