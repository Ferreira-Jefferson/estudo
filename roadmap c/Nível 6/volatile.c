#include <stdio.h>

// A volatile diz ao compilador par ele não otimizar alguma variável, por N razões
// Pode ser que a memória referenciada é de um outro sistema e conforme ele se modifica, pode afetar o valor da variável que até então parecia imutável

// veja abaixo um exemplo de otimização, se usar gcc -O2 -c valitile.c ele comprime otimizando
// teste com o volvative e sem o volative, para ver o código gerado digite objdump -d volatile.o
int valor(){
	volatile int valor = 0x01;
	valor = 0x02;
	valor = 0x03;
	valor = 0x04;
	valor = 0x05;
	return (valor);
}

// Abaixo está um bom exemplo do que pode ocorrer: em m primeiro momento é só um loop infinito.
// que poderia ser otimizado para while(1);
// mas como o valor que define a parada é externo (clique de um botão por exemplo), o código não pode ser otimizado, é sempre necessário validar a condição
volatile int valorExterno;
int espera()
{
	while(valorExterno != 255);

	printf("fim da espera.");
}

// Só que pense um pouco a respeito, como a variável valorExterno é global,
// ela pode ser utilizada em outros trechos de código, mas só na função espera que ela não pode ser otimizada
// Neste caso o ideal seria usar um type cast para tornar a variável em volatile apenas no trecho desejado
// Assim em todos os outros trechos que a variável for utilizada ela será otimizada
int valorExterno2;
int espera_2()
{
	while(*(volatile*) &valorExterno != 255);

	printf("fim da espera 2.");
}

int main(){
	printf("valor: %d", valor());
	return (0);
}