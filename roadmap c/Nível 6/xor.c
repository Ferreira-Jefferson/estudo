#include <stdio.h>
#include <limits.h>


// O xor é um interruptor de bits, ele sempre inverte um resultado
// se fizer uma máscara com zeros e uns, os locais com uns terão o valor invertido
// Ele é útil para mascarar informações e depois voltar para o original
// Isso permite também a troca de informações de lugar, como um swap sem precisar de uma variável auxiliar

void swap_xor(int *a, int *b) {
    if (a != b) {  // Verifica se não é a mesma variável
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

int prot_ex(int dado, int hash)
{
	int hash_validator = dado ^ 0b101;
	return (hash_validator == hash);
}

int main(void)
{

	int x = 5;  // Binário: 00000101
	int y = 3;  // Binário: 00000011
	int resultado = x ^ y;  // Faz a operação bit a bit 00000110

	printf("x: %d ^ y: %d = resultado: %d\n", x, y, resultado);

	int valor = 0b01010;  // Binário: 00001010
	int MASCARA = 0b010;  // Binário: 00000010
	valor ^= MASCARA;  // Alterna o segundo bit
	printf("valor ^= MASCARA = %d\n", valor);

	int a = 5, b = 3, c=7;
	//trocando a com b
	a = a ^ b;  
	b = a ^ b;  
	a = a ^ b;  

	//trocando a com c
	c = a ^ c;  
	a = a ^ c;  
	c = a ^ c; 
	
 
	printf("Novo a: %d, Novo b: %d c: %d\n", a, b, c);

		char letra = 'A';  // Representação ASCII
		char chave = 0b01; // Chave de encriptação

		char cifrado = letra ^ chave;  // Cifra com XOR
		char decifrado = cifrado ^ chave;  // Decifra com XOR
		printf("Cifrado: %c, Decifrado: %c\n", cifrado, decifrado);


    int xx = INT_MAX;  // 2,147,483,647
    int yy = INT_MIN;  // -2,147,483,648
    
    swap_xor(&xx, &yy);
    printf("xx = %d, yy = %d\n", xx, yy);  // xx = -2,147,483,648, yy = 2,147,483,647
    

	int dado = 55;
	int key = 0b101;
	int hash = dado ^ key;

	printf("Dado valido? %d\n", prot_ex(dado, hash));
	return (0);
}
