#include <stdio.h>
 
void weighted_average(double num1, double num2, double num3)
{
	num1 *= 2;
	num2 *= 3;
	num3 *= 5;

	double w_average = (num1 + num2 + num3) / (2 + 3 + 5);

	printf("%.1f\n", w_average);
}

int main() {
 
	int i = 0;
	int qtt;
	double num1, num2, num3;

	scanf("%d%*c", &qtt);

	while (i < qtt)
	{
		scanf("%lf %lf %lf%*c", &num1, &num2, &num3);
		weighted_average(num1, num2, num3);
		i++;
	}

    return 0;
}