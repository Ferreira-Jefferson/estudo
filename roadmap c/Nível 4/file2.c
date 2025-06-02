#include <stdio.h>

int main(void)
{
    FILE *arquivo = fopen("teste2.txt", "a+");

    fprintf(arquivo, "Teste 1\nTeste 2\nTeste 3");

    rewind(arquivo);
    char str[50];
    int num;
    fscanf(arquivo, "%s %d", str, &num);

    printf("%s - %d\n", str, num);

    rewind(arquivo);

    while(fgets(str, sizeof(str), arquivo) != NULL)
        printf("while: %s", str);

    fclose(arquivo);

    return (0);
}