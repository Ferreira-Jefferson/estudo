#include <stdio.h>

// Usado para concatenar bits sem alterar os demais
// Usado para alterar bits sem afetar os demais

int main(void)
{
	int x = 5;  // Binário: 00000101
	int y = 3;  // Binário: 00000011
	int resultado = x | y;  // Faz a operação bit a bit
	printf("Resultado: %d\n", resultado);

	int valor = 0b01000;  // Binário: 00001000
	int MASCARA = 0b010;  // Binário: 00000010
	valor |= MASCARA;  // Agora valor = 00001010
	printf("Valor: %d\n", valor);

	#define READ  (1 << 0)  // 00000001
	#define WRITE (1 << 1)  // 00000010
	#define EXEC  (1 << 2)  // 00000100

	int permissoes = READ | WRITE;  // Agora usuário pode ler e escrever (00000011)
	printf("Permissoes: %d\n", permissoes);


	return (0);
}