#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

struct photo {
	char *photo;
	int size;
	int substrings;
};

struct album {
	struct photo *photos;
	int *qtt_per_album;
	int qtt_albuns;
};

int is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int contains(const char *haystack, const char *needle) {
	if (!*needle) return 1;

	int m = strlen(haystack);
	int n = strlen(needle);

	if (n > m) return 0;

	// Cria o vetor de falha (prefixo)
	int *lps = malloc(n * sizeof(int));
	int len = 0;
	lps[0] = 0;

	for (int i = 1; i < n; ) {
		if (needle[i] == needle[len]) {
			len++;
			lps[i] = len;
			i++;
		} else {
			if (len != 0) {
				len = lps[len - 1];
			} else {
				lps[i] = 0;
				i++;
			}
		}
	}

	// Executa a busca KMP
	int i = 0, j = 0;
	while (i < m) {
		if (needle[j] == haystack[i]) {
			i++;
			j++;
		}

		if (j == n) {
			free(lps);
			return 1;
		} else if (i < m && needle[j] != haystack[i]) {
			if (j != 0)
				j = lps[j - 1];
			else
				i++;
		}
	}

	free(lps);
	return 0;
}


void show_album(struct album *album)
{
	int i = 0;
	int j;

	while (i < album->qtt_albuns)
	{
		printf("Per Album: [%d]: %d\n", i, album->qtt_per_album[i]);
		j = 0;
		while (album[i].photos[j].photo)
		{
			printf("Photo: %s\n", album[i].photos[j].photo);
			// printf("Size: %d\n", album[i].photos[j].size);
			// printf("Subs: %d\n", album[i].photos[j].substrings);
			j++;
		}
		printf("\n");
		i++;
	}
}

struct album* create_album(void)
{
	int				read;
	char			*line = NULL;
	size_t			len = 0;
	int				*results;
	int				i = 0;
	int				j = 0;
	int				qtt_photos;
	struct album 	*album;

	album = (struct album*) malloc(sizeof(struct album));
	if(!album)
		return (NULL);

	album->qtt_per_album = (int*) malloc(sizeof(int));
	if(!album->qtt_per_album)
		return (NULL);

	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if(line[0] == '0')
			break;

		if(read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		if(is_number(line[0]))
		{
			album = (struct album*) realloc(album, (i + 1) * sizeof(struct album));
			if(!album)
				return (NULL);			
			
			album->qtt_per_album = (int*) realloc(album->qtt_per_album, (i + 1) * sizeof(int));
			if(!album->qtt_per_album)
				return (NULL);

			qtt_photos = atoi(line);
			album[i].photos = (struct photo*) malloc(qtt_photos * sizeof(struct photo));
			album->qtt_per_album[i] = qtt_photos;
			if(!album[i].photos)
				return (NULL);

			album->qtt_albuns = i + 1;
			i++;
			j = 0;
		} else {
			album[i - 1].photos[j].photo = strdup(line);
			album[i - 1].photos[j].size = read - 1;			
			album[i - 1].photos[j].substrings = 0;

			j++;	
		}		
	}
	return (album);
}

int compare_photos(const void *a, const void *b) {
	const struct photo *pa = (const struct photo *)a;
	const struct photo *pb = (const struct photo *)b;
	return pb->size - pa->size; // decrescente
}

void short_album(struct album *album)
{
	int i = 0;
	int j;
	struct photo *photo;
	int qtt_photos;

	while (i < album->qtt_albuns)
	{
		qsort(album[i].photos, album->qtt_per_album[i], sizeof(struct photo), compare_photos);
		i++;
	}
}

void count_sequence(struct album *album)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int qtt_photos = 0;
	int max = 0;
	int count = 0;

	while(i < album->qtt_albuns)
	{
		j = 0;
		count = 0;
		max = 0;
		qtt_photos = album->qtt_per_album[i];
		while(j < qtt_photos)
		{
			k = j + 1;
			while(1)
			{
				if(k > qtt_photos - 1)
				{
					j++;
					break ;
				}
				if(contains(album[i].photos[j].photo, album[i].photos[k].photo))
				{
					count++;
					j = k;	
					break ;
				} 
				k++;
			}

			if(count > max)
				max = count;
			
		}
		printf("%d\n", max + 1);
		max = 0;
		i++;
	}
}

void free_album(struct album *album)
{
	int i = 0;
	int j;

	while (i < album->qtt_albuns)
	{
		free(album[i].photos);
		i++;
	}
	free(album->qtt_per_album);
	free(album);
}

int main() {
	clock_t start, end;
	start = clock();
	struct album *album;

	album = create_album();

	short_album(album);

	count_sequence(album);

	//show_album(album);

	end = clock();

	double tempo = (double) (end-start) / CLOCKS_PER_SEC;
	printf("Time: %f\n", tempo);

	free_album(album);
    return 0;
}

/*
3
an
ana
anabele
4
um
ana
anabele
dois
3
an
ana
anabele
4
um
ana
anabele
dois
3
an
ana
anabele
4
um
ana
anabele
dois
3
an
ana
anabele
4
um
ana
anabele
dois


*/