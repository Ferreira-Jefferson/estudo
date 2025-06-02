#include <stdio.h>
 
void calculate_duration(int time_start, int minute_start, int time_end, int minute_end)
{
	int duration_time, duration_minute;

	duration_time = 24 - time_start + time_end;
	if(duration_time > 24)
		duration_time -= 24;
	
	if(minute_start > minute_end)
		duration_time -= 1;
	
	duration_minute = 60 - minute_start + minute_end;
	if(duration_minute > 60)
		duration_minute -= 60;
	
	if(duration_minute == 60)
		duration_minute = 0;
	
	if(duration_time == 24 && duration_minute > 0)
		duration_time = 0;

	printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", duration_time, duration_minute);
}

int main()
{
 
    int time_start, minute_start, time_end, minute_end;

	scanf("%d %d %d %d", &time_start, &minute_start, &time_end, &minute_end);

	calculate_duration(time_start, minute_start, time_end, minute_end);
 
    return (0);
}