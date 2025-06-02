#include <stdio.h>
#include <stdlib.h>

double ft_sqrt(double value, double tolerance)
{
    double x;
    double erro;
    double new_x;

    x = value;
    erro = 1.0;
    while (erro > tolerance)
    {
        new_x = (x + value / x) / 2;
        if((new_x - x) > 0)
            erro = new_x - x;
        else
            erro = x - new_x;
        x = new_x;            
    }
    return (x);
}

int main(void) {
    
    char *end;
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    
    if(a == 0)
    {
        printf("Impossivel calcular\n");
        return (0);
    }

    double delta = (b*b) - (4*a*c);
    
    if(delta < 0)
    {
        printf("Impossivel calcular\n");
        return (0);
    }
    
    double tolerance = 0.00001;
    double squared = ft_sqrt(delta, tolerance);
    double value1 = (-b + squared) / (2*a);
    double value2 = (-b - squared) / (2*a);
    
    printf("R1 = %.5f\n", value1);
    printf("R2 = %.5f\n", value2);
    
    return 0;
}