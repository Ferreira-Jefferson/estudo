#include <stdio.h>
#include <string.h>

char* get_DDD(int code)
{
	static char city[20];
	switch(code)
	{
		case 61:
			strcpy(city, "Brasilia");
			break;
		case 71:
			strcpy(city, "Salvador");
			break;
		case 11:
			strcpy(city, "Sao Paulo");
			break;
		case 21:
			strcpy(city, "Rio de Janeiro");
			break;
		case 32:
			strcpy(city, "Juiz de Fora");
			break;
		case 19:
			strcpy(city, "Campinas");
			break;
		case 27:
			strcpy(city, "Vitoria");
			break;
		case 31:
			strcpy(city, "Belo Horizonte");
			break;
		default:
			strcpy(city, "DDD nao cadastrado");
	}

	return (city);
}

int main() {

	int code;

	scanf("%d", &code);

	printf("%s\n", get_DDD(code)); 
 
    return 0;
}