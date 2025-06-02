#include <stdio.h>



int main(void)
{
    FILE *arquivo = fopen("teste.bin", "wb+");

    if(!arquivo)
    {
        printf("Erro na abertuda do arquivo.");
        return (1);
    }

    double vet[5] = {1.25,2.855,3.74859,4.9865874,5.712354789};

    fwrite(vet, sizeof(double), 5, arquivo);

    rewind(arquivo);

    double vet2[5];
    fread(vet2, sizeof(double), 5, arquivo);

    printf("%f %f %f %.7f %.9f", vet2[0], vet2[1], vet2[2], vet2[3], vet2[4]);

    fclose(arquivo);
    return (0);
}