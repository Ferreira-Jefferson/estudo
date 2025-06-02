#include <stdio.h>

int main(void)
{
    FILE *arquivo = fopen("teste_bin2.bin", "a+");

    double vet[3] = {1.5, 5.85, 3.9};
    fwrite(vet, sizeof(double), 3, arquivo);

    rewind(arquivo);

    double vet2[3];
    fread(vet2, sizeof(double), 3, arquivo);

    printf("%f, %f\n\n", vet2[0], vet2[2]);

    rewind(arquivo);
    while(fread(vet2, sizeof(double), 3, arquivo))
        printf("%f, %f\n", vet2[0], vet2[2]);

    fclose(arquivo);
    return (0);
}