#include <stdio.h>
#include <string.h>

void show_month(int month_number)
{
	char month[12][10] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	printf("%s\n", month[month_number - 1]);
}

int main() {
	int month_number;

	scanf("%d", &month_number);

 	show_month(month_number);

    return 0;
}