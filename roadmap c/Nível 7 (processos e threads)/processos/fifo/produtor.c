#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd = open("meu_fifo", O_WRONLY); 
	char mensagem[] = "Olá, consumidor!";

	write(fd, mensagem, sizeof(mensagem));
	close(fd);
	printf("[Produtor] Mensagem enviada!\n");

	return 0;
}
