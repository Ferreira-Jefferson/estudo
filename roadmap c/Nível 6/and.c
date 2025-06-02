#include <stdio.h>

#define READ  0b001  // Permissão de leitura
#define WRITE 0b010  // Permissão de escrita
#define EXEC  0b100  // Permissão de execução

enum Direcoes {
	CIMA = 0b00000001,
	BAIXO = 0b00000010,
	DIREITA = 0b00000100,
	ESQUERDA = 0b00001000
};

typedef struct {
	int vertical;
	int horizontal;
} POS;


// Usado para verificar se um determinado bit ou conjunto de bits estão ativos
// Usado para comparar bits

int main(void)
{
	int usuario_permissao = READ | WRITE;  // Usuário pode ler e escrever (0b011)
	
	if (usuario_permissao & READ) {
		printf("Usuário pode LER arquivos.\n");
	}

	if (usuario_permissao & WRITE) {
		printf("Usuário pode ESCREVER arquivos.\n");
	}

	if (usuario_permissao & EXEC) {
		printf("Usuário pode EXECUTAR arquivos.\n");
	} else {
		printf("Usuário NÃO pode executar arquivos.\n");
	}

	unsigned char decisao = 0b00001011;
	POS posicao = {0,0};
	
	if(decisao & CIMA)
		posicao.vertical++;
	if(decisao & BAIXO)
		posicao.vertical--;
	if(decisao & DIREITA)
		posicao.horizontal++;
	if(decisao & ESQUERDA)
		posicao.horizontal--;

	printf("vertical: %d | horizontal: %d \n", posicao.vertical, posicao.horizontal); // vertical: 0 | horizontal: -1
    		


	return (0);
}