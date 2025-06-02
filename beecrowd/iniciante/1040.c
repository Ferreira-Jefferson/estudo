#include <stdio.h>

double calculate_average(double averages[])
{
    int i;
    double accumulator;
    int weight[4] = {2, 3, 4, 1};
    int sumWeight = 10;

    accumulator = 0;
    i = 0;
    while (i < 4)
    {
        accumulator += averages[i] * weight[i];
        i++;
    }
    return (accumulator / sumWeight);    
}

int main(void)
{
    double averages[4];
    double average;
    double exam;

    scanf("%lf %lf %lf %lf", &averages[0], &averages[1], &averages[2], &averages[3]);

    average = calculate_average(averages);

    printf("Media: %.1lf\n", average);

    if(average >= 7)
        printf("Aluno aprovado.\n");
    else if(average < 5)
        printf("Aluno reprovado.\n");
    else
    {
        scanf("%lf", &exam);
        printf("Aluno em exame.\n");
        printf("Nota do exame: %.1lf\n", exam);
        if(average >= 5)
            printf("Aluno aprovado.\n");
        else
            printf("Aluno reprovado.\n");
        printf("Media final: %.1lf\n", (average + exam) / 2);
    }

    return (0);
}