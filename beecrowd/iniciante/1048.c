#include <stdio.h>

void calculate_adjust_salary(double salary)
{
	double percentage;
	double adjust_salary;
	double new_salary;

	if(salary > 2000)
		percentage = 4;
	else if(salary > 1200)
		percentage = 7;
	else if(salary > 800)
		percentage = 10;
	else if(salary > 400)
		percentage = 12;
	else 
		percentage = 15;
	
	adjust_salary = salary * (percentage / 100);
	new_salary = salary + adjust_salary;

	printf("Novo salario: %.2lf\n", new_salary);
	printf("Reajuste ganho: %.2lf\n", adjust_salary);
	printf("Em percentual: %.0lf %%\n", percentage);
	
}
 
int main() {
 
	double salary;

	scanf("%lf", &salary);

	calculate_adjust_salary(salary);

    return 0;
}

