#include <stdio.h>

void get_position(double x, double y)
{
    if(x == 0 && y == 0)
        printf("Origem\n");
    else if(x == 0)
        printf("Eixo Y\n");
    else if(y == 0)
        printf("Eixo X\n");
    else if(x > 0 && y > 0)
        printf("Q1\n");
    else if(x < 0 && y > 0)
        printf("Q2\n");
    else if(x < 0 && y < 0)
        printf("Q3\n");
    else
        printf("Q4\n");
}

int main(void)
{
    double x, y;

    scanf("%lf %lf", &x, &y);

    get_position(x, y);

    return (0);
}