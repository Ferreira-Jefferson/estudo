#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void get_results(char *results, char faulty_digit, char *number)
{
	int i = 0;
	int j = 0;
	int only_zero = 1;

	while(number[i])
	{
		if(number[i] != faulty_digit)
		{

			if(number[i] != '0')
				only_zero = 0;

			if(!only_zero)
			{
				results[j] = number[i];
				j++;
			}
		}
		i++;
	}

	results[j] = '\0';
	if(i > 0 && j == 0 || only_zero)
	{
		results[0] = '0';
		results[1] = '\0';
	}
}

int main() {
	int read;
	char *line = NULL;
	size_t len = 0;

	int i = 0;
	int j;

	char **results = (char**) malloc(sizeof(char*));

	while((read = getline(&line, &len, stdin)) != -1)
	{
		if(read > 0 && line[read-1] == '\n')
			line[read-1] = '\0';

		if(strlen(line) == 3 && line[0] == '0' && line[2] == '0')
			break;
		
		results = (char**) realloc(results, (i + 1) *  sizeof(char*));
		if(!results)
			return (1);

		results[i] = (char*) malloc(len * sizeof(char));
		if(!results[i])
			return (1);
		
		get_results(results[i], line[0], &line[2]);
		
		i++;
	}

	j = 0;
	while(j < i)
		printf("%s\n", results[j++]);

	i--;
	while (i > -1)
		free(results[i--]);
	free(results);
	free(line);

    return 0;
}