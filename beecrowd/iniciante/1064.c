#include <stdio.h>
 
int main() {
 
    int i = 0;
	int QTD_NUM = 6;
	
	double num;
	int cont_positivos = 0;
	double acumulador = 0;

	while(i < QTD_NUM)
	{
		scanf("%lf%*c", &num);
		if(num > 0)
		{
			cont_positivos++;
			acumulador += num;
		}
		i++;
	}

	printf("%d valores positivos\n", cont_positivos);
	printf("%.1lf\n", acumulador / cont_positivos);
 
    return 0;
}