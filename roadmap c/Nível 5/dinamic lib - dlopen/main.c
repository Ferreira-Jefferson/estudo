#include <stdio.h>
#include <dlfcn.h>

// Para tornar o programa ainda mais leve e modular é possível usar as lib dinâmicas .so apenas nos trechos desejados e as fecharem em seguida
// gcc -fPIC -c meu_math.c -o meu_math.o
// gcc -shared -o libmeu_math.so meu_math.o
// gcc main.c -o programa -ldl
// LD_LIBRARY_PATH=. ./programa

// Se achou muito trabalhoso, aqui está uma longa explicação de suas vantagens: https://copilot.microsoft.com/shares/aUtzk1JMk4yri4SSW9XfK

int main() {
    // Carregar a biblioteca dinâmica
    void *DLL = dlopen("./libmeu_math.so", RTLD_LAZY);
    if (!DLL) {
        printf("Erro ao carregar biblioteca: %s\n", dlerror());
        return 1;
    }

    // Obter referência para a função quadrado()
    double (*quadrado)(double) = dlsym(DLL, "quadrado");
    if (!quadrado) {
        printf("Erro ao localizar função quadrado!\n");
        return 1;
    }

    // Obter referência para a função cubo()
    double (*cubo)(double) = dlsym(DLL, "cubo");
    if (!cubo) {
        printf("Erro ao localizar função cubo!\n");
        return 1;
    }

    // Chamar funções carregadas dinamicamente
    printf("2 ao quadrado: %.2f\n", quadrado(2.0));
    printf("3 ao cubo: %.2f\n", cubo(3.0));

    // Fechar biblioteca
    dlclose(DLL);

    return 0;
}
