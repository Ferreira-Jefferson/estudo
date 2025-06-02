#include <stdio.h>
#include "jf_math.h"
#include "jf_string.h"

// As libs estáticas agrupam arquivos .o o que permite compilar um programa sem os arquvios .c ou .o
// Ainda assim é necessário manter os arquivos .h
// Passos para criar uma lib.a (lib estática)
    // compilar os arquivos .c em .o: gcc -c jf_math.c jf_string.c (no local deve ter os .h também)
    // Unir os .o na .a: ar rcs libNomeLib.a *.o (lib é um prefixo, deve existir antes do nome real da lib)
    // Usar com a main.c e demais libs: gcc main.c -L. -lNomeLib -o programa (-L. diz para procurar a lib na pasta atual, -l diz o nome da lib (não precisa do prefixo lib e nem da extensão .a))
// É também possível adicionar novos .o em uma lib.a já criada
    // Compile a nova funcionalidade: gcc -c nova_funcao.c -o nova_funcao.o
    // Adicione a lib existente: ar r libNomeLib.a nova_funcao.o
    // Atualize os índices da lib.a: ranlib libNomeLib.a (Ajuda o linker a encontrar as funções corretamente na lib)

int main(void)
{
    char teste[50] = "palavra de teste";

    printf("Soma: %d\n", soma(10, 10));
    printf("String len: %d\n", jf_strlen(teste));
    printf("Struct: nome: %s | len: %d\n", String.value, String.jf_strlen(String.value));
}