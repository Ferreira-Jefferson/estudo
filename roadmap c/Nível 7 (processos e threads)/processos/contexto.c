#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// Apesar do filho ter uma cópia da memória do pai, suas variáveis, 
// tanto locais, quanto globais, não são compartilhadas ou afetadas pelo outro.

// Tudo o que for criado ou aberto antes de se criar o processo, será compatilhado pelos filhos (arquivos, sockets...)

// Sistemas modernos como Linux utilizam Copy-on-Write (COW)
// O COW permite que todos os processos compartilhem a mesma memória, até que algum queira modificar algo
// para este processo é criada uma memória separada, o que aumenta a eficiência do sistema
// se nenhum processo tentar modificar algo, apenas a memória pai é usada, economizando recursos.

int var_global = 10;

int main(void)
{
	int var_local = 20;
	int var_compartilhada = 50;

	int pid = fork();

	if(pid == -1)
		printf("Erro.\n");
	
	if(pid > 0)
	{
		printf("Processo filho [PP]:\n");
		printf("[PP] &var_compartilhada: %p\n", &var_compartilhada);
	} else {
		printf("Processo filho [PF]:\n");
		printf("[PF] &var_compartilhada: %p\n", &var_compartilhada);
	}

	if(pid == 0)
	{
		var_global += 100;
		var_local += 100;

		printf("\n");
		printf("Processo filho [PF]:\n");
		printf("[PF] var_global: %d\n", var_global);
		printf("[PF] var_local: %d\n", var_local);
	}

	if(pid > 0)
	{
		wait(NULL);
		printf("\n");
		printf("Processo pai [PP]:\n");
		printf("[PP] var_global: %d\n", var_global);
		printf("[PP] var_local: %d\n", var_local);
	}


	return (0);
}
