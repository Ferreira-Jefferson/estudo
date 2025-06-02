#include <stdio.h>
#include <stdlib.h>

// Função de comparação usada pelo qsort
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Implementação básica do QuickSort
void quicksort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    if (num < 2) return;  // Caso base: array com 1 ou 0 elementos já está ordenado

    char *arr = (char *)base;  // Convertendo para char* para manipulação de bytes
    char *pivot = arr + (num / 2) * size;  // Escolhendo o pivô no meio do array

    size_t i = 0, j = num - 1;
    while (i <= j) {
        while (compar(arr + i * size, pivot) < 0) i++;  // Encontrar elemento maior que o pivô
        while (compar(arr + j * size, pivot) > 0) j--;  // Encontrar elemento menor que o pivô

        if (i <= j) {
            // Troca os elementos
            for (size_t k = 0; k < size; k++) {
                char temp = arr[i * size + k];
                arr[i * size + k] = arr[j * size + k];
                arr[j * size + k] = temp;
            }
            i++;
            j--;
        }
    }

    // Recursivamente ordena as duas metades
    if (j > 0) quicksort(arr, j + 1, size, compar);
    if (i < num) quicksort(arr + i * size, num - i, size, compar);
}

int main() {
    int vet[] = {5, 3, 8, 1, 2, 7, 6, 4, 0};
    size_t n = sizeof(vet) / sizeof(vet[0]);

    quicksort(vet, n, sizeof(int), comparar);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    return 0;
}
