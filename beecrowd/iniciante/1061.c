#include <stdio.h>
#include <time.h>

void show_duration(int start_day, int start_time[], int end_day, int end_time[])
{
    int start = (start_day * 86400) + (start_time[0] * 3600) + (start_time[1] * 60) + start_time[2];
    int end = (end_day * 86400) + (end_time[0] * 3600) + (end_time[1] * 60) + end_time[2];

    int difference = end - start;

    int day = difference / 86400;
    difference %= 86400;
    int hour = difference / 3600;
    difference %= 3600;
    int minute = difference / 60;
    int second = difference % 60;

    printf("%d dia(s)\n", day);
    printf("%d hora(s)\n", hour);
    printf("%d minuto(s)\n", minute);
    printf("%d segundo(s)\n", second);	
}

int main() {
 
    int start_day;
    int end_day;

	int start_time[3];
    int end_time[3];

	scanf("Dia %d%*c", &start_day);
	scanf("%d : %d : %d%*c", &start_time[0], &start_time[1], &start_time[2]);

	scanf("Dia %d%*c", &end_day);
	scanf("%d : %d : %d%*c", &end_time[0], &end_time[1], &end_time[2]);

	show_duration(start_day, start_time, end_day, end_time);
    return 0;
}