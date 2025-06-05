#include <stdio.h>
 
int main() {
 
    int i = 0;
	int QTD_NUM = 5;
	
	int num;
	int cont_pares = 0;

	while(i < QTD_NUM)
	{
		scanf("%d%*c", &num);
		if(!(num & 0x1))
			cont_pares++;
		i++;
	}

	printf("%d valores pares\n", cont_pares);
 
    return 0;
}