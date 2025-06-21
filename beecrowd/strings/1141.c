#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRINGS 10000
#define MAX_LEN 1000

char *strings[MAX_STRINGS];
int n;
int dp[MAX_STRINGS];
int visited[MAX_STRINGS];

int compare(const void *a, const void *b)
{
    char * const *sa = (char * const *)a;
    char * const *sb = (char * const *)b;
    int la = strlen(*sa);
    int lb = strlen(*sb);

    if (la != lb)
        return la - lb;

    return strcmp(*sa, *sb);
}

// Verifica se b é substring contígua de a
int contains(char *a, char *b)
{
    int la = strlen(a);
    int lb = strlen(b);

    int i = 0;
    while(i <= la - lb)
    {
        int j = 0;
        while(j < lb && a[i+j] == b[j])
            j++;
        if(j == lb)
            return 1;
        i++;
    }
    return 0;
}

int dfs(int u)
{
    if(visited[u])
        return dp[u];

    visited[u] = 1;
    int max_len = 1;
    int v = u + 1;

    while(v < n)
    {
        if(strlen(strings[v]) > strlen(strings[u]) && contains(strings[v], strings[u]))
        {
            int candidate = 1 + dfs(v);
            if(candidate > max_len)
                max_len = candidate;
        }
        v++;
    }
    dp[u] = max_len;
    return max_len;
}

int main()
{
    clock_t start = clock();

    int results[10000];
    int res_count = 0;

    while(1)
    {
        if(scanf("%d", &n) != 1 || n == 0)
            break;

        int i = 0;
        while(i < n)
        {
            strings[i] = (char *)malloc((MAX_LEN+1)*sizeof(char));
            scanf("%s", strings[i]);
            i++;
        }

        qsort(strings, n, sizeof(char *), compare);

        // limpa dp e visited
        i = 0;
        while(i < n)
        {
            dp[i] = 0;
            visited[i] = 0;
            i++;
        }

        int max_seq = 0;
        i = 0;
        while(i < n)
        {
            int cur = dfs(i);
            if(cur > max_seq)
                max_seq = cur;
            i++;
        }

        results[res_count++] = max_seq;

        // libera memória strings
        i = 0;
        while(i < n)
        {
            free(strings[i]);
            i++;
        }
    }

    int j = 0;
    while(j < res_count)
    {
        printf("%d\n", results[j]);
        j++;
    }

    clock_t end = clock();
    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %f\n", tempo);

    return 0;
}
