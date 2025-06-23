#include <stdio.h>
#include <math.h>
 
int main() {
 
	double i = 0, j = 1;
	int aux = 1;
	const double EPSILON = 0.00001;

    while(1)
	{
		if(i > 2 + EPSILON)
			break ;
		
		if(fabs(i - (int) round(i)) < EPSILON)
			printf("I=%.0f J=%.0f\n", i, j);
		else
			printf("I=%.1f J=%.1f\n", i, j);

		if(aux % 3 == 0)
		{
			i += 0.2;
			j -= 3.0;
			j += 0.2;
		}
		j += 1.0;
		
		aux++;
	}
 
    return 0;
}