#include <stdio.h>

int main(void)
{
    FILE *arquivo = fopen("teste.txt", "w+");

    if(!arquivo)
    {
        printf("Erro ao abrir o arquivo.");
        return (1);
    }

    fprintf(arquivo, "Texto 1\nTexto 2\n");
    fprintf(arquivo, "Texto %d\nTexto %d\n", 3, 4);

    rewind(arquivo);

    char texto[50];
    int numero;
    fscanf(arquivo, "%s %d", texto, &numero);
    printf("%s %d\n", texto, numero);

    rewind(arquivo);

    char linha[50];
  
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
    return (0);
}