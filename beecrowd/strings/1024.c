#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void first_pass(char *text)
{
	int i = 0;
	int size = strlen(text);

	while(i < size)
	{
		if((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
			text[i] = ((unsigned char) text[i]) + 3;
		i++;
	}
}

void second_pass(char *text)
{
	int i = 0;
	int size = strlen(text) -1;

	while(i < size)
	{
		text[i] = text[i] ^ text[size];
		text[size] = text[i] ^ text[size];
		text[i] = text[i] ^ text[size];
		size--;
		i++;
	}
}

void third_pass(char *text)
{
	int size =  strlen(text);
	int i = size / 2;
	
	while(i < size)
	{
		text[i] = ((unsigned char) text[i]) - 1;
		i++;
	}
}

void encript(char *text)
{
	first_pass(text);
	second_pass(text);
	third_pass(text);
	printf("%s\n", text);
}

int main() { 
    int qtt;
	int i = 0;
	
	scanf("%d%*c", &qtt);

	char **texts = (char**) malloc(qtt * sizeof(char*));

	while(i < qtt)
	{
		texts[i] = (char*) malloc(1000 * sizeof(char));
		scanf("%[^'\n']%*c", texts[i++]);
	}

	i = 0;
 	while(i < qtt)
		encript(texts[i++]);
	
	i = 0;
 	while(i < qtt)
		free(texts[i++]);

	free(texts);
    return 0;
}