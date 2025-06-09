#include <stdio.h>
#include <unistd.h>
#include <string.h>

// pipe anônimos permitem a comunicação unidimensional de processos, sempre entre pai e filho e morrem junto ao processo
// o fd que não está sendo usando deve ser sempre fechado, para que o outro processo o use sem problemas
// fd significa: file descriptor - identificador de arquivos e recursos

int main()
{
	int fd[2];
	char mensagem[10] = "Ola mundo!";
	char buffer[100];
	
	pipe(fd);
	int p = fork();

	if(p == -1)
		printf("Erro.");
	
	if(p == 0)
	{
		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		printf("Filho: %s\n", buffer);
		close(fd[0]);
	}
	else
	{
		printf("Pai\n");
		close(fd[0]);
		write(fd[1], mensagem, strlen(mensagem) + 1);
		close(fd[1]);
	}
}