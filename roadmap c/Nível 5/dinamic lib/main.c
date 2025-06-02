#include <stdio.h>
#include "jf_math.h"
#include "jf_string.h"

// libs dinâmicas nada mais são que as famosas DLL, sendo que no linux elas são as .so
// As libs dinâmicas dão maior flexibilidade ao software
// elas permitem que partes do software sejam atualizadas, sem que todo o projeto seja compilado
// outra vantagem é que seu uso torna o software mais leve por não ser incorporada no executável na compilação.
// Passos para criar uma lib.so (lib dinâmica)
    // compilar os arquivos .c em .o: gcc -fPIC -c jf_math.c jf_string.c
    // criar a "DLL": gcc -shared -o libjf_utils.so *.o
    // Compilar o programa com a DLL como referência: gcc main.c -L. -ljf_utils -o programa

int main(void)
{
    char teste[50] = "palavra de teste";

    printf("Soma: %d\n", soma(10, 10));
    printf("String len: %d\n", jf_strlen(teste));
    printf("Struct: nome: %s | len: %d\n", String.value, String.jf_strlen(String.value));
}