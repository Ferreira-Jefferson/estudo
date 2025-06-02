#include <stdio.h>
 
void calculate_tax(double salary)
{
	if(salary <= 2000.00)
	{
		printf("Isento\n");
		return ;
	}

	double tax_due = 0;
	
	if (salary > 2000.00)
		tax_due += (salary > 3000.00 ? 1000.00 : salary - 2000.00) * 0.08;
	if (salary > 3000.00)
		tax_due += (salary > 4500.00 ? 1500.00 : salary - 3000.00) * 0.18;
	if (salary > 4500.00)
		tax_due += (salary - 4500.00) * 0.28;

	printf("R$ %.2lf\n", tax_due);
}

int main() {
	double salary;

	scanf("%lf", &salary);

	calculate_tax(salary);    

    return 0;
}