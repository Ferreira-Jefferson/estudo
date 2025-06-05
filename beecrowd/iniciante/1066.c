#include <stdio.h>
 
int main() {
 
    int i = 0;
	int QTD_NUM = 5;
	
	int num;
	int cont_pares = 0;
	int cont_impares = 0;
	int cont_positivos = 0;
	int cont_negativos = 0;


	while(i < QTD_NUM)
	{
		scanf("%d%*c", &num);
		
		if(num > 0)
			cont_positivos++;
		else if(num < 0)
				cont_negativos++;
		
		if(num & 0x1)
			cont_impares++;
		else
			cont_pares++;
		i++;
	}

	printf("%d valor(es) par(es)\n", cont_pares);
	printf("%d valor(es) impar(es)\n", cont_impares);
	printf("%d valor(es) positivo(s)\n", cont_positivos);
	printf("%d valor(es) negativo(s)\n", cont_negativos);
 
    return 0;
}