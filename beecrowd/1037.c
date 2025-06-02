#include <stdio.h>

int main(void)
{
    double value;

    scanf("%lf", &value);

    if(value < 0 || value > 100)
        printf("Fora de intervalo\n");
    else if(value <= 25.0)
        printf("Intervalo [0,25]\n");
    else if(value <= 50.0)
        printf("Intervalo (25,50]\n");
    else if(value <= 75.0)
        printf("Intervalo (50,75]\n");
    else
        printf("Intervalo (75,100]\n");

    return (0);
}