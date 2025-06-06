#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Processos filhos são cópias independentes de seus pais. Ele copia toda a memória do pai,
// arquivos podem ser herdados, mas algumas operações precisam de sincronização.

// O processo filho inicia a execução a partir do linha em que foi criado,
// em paralelo o processo pai também está execurando a mesma linha o que pode ocosionar erros,
// por isso é necessário identificar em qual processo está antes de executar qualquer ação

// A não ser que o programa precise que um processo fique rodando mesmo após o programa ser encerrado,
// é importante fazer o proceso pai espera os filhos terminarem antes de encerrarem para não ter processos orfãos

// wait() espera a todos os filhos
// waitid() espera por um filho em específico

int main(void)
{
	int pid = fork();
	int pid2;
	if(pid == -1)
		printf("Erro na criacao do processo.\n");
	
	printf("Antes: %d\n", pid); // Pai e filho estão executando em paralelo

	if(pid == 0)
		printf("Processo Filho.\n");

	if(pid > 0)
	{
		pid2 = fork();

		if(pid2 == 0)
		{
			printf("Executando filho 2\n");
			sleep(1);
		}
		else
		{
			waitpid(pid2, NULL, 0);
			printf("Filho 2 terminou\n");
			
			wait(NULL); // Pai espera o filho 1 terminar
			printf("Processo Pai.\n");
		}
		

	}

	return (0);
}