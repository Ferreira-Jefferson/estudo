/*
🚦 Exercício: Controle de Entrada em uma Biblioteca
Imagine que você está programando um sistema para gerenciar o acesso de estudantes a uma biblioteca. A biblioteca só pode acomodar até 3 estudantes simultaneamente, pois há espaço limitado. No entanto, vários estudantes podem tentar entrar ao mesmo tempo.

Objetivo do exercício
1️⃣ Criar 5 threads, representando estudantes que querem entrar na biblioteca. 2️⃣ Usar um semaforo (sem_t) para limitar o número máximo de estudantes dentro da biblioteca a 3 por vez. 3️⃣ Cada estudante deve entrar na biblioteca, ficar por alguns segundos e depois sair, liberando espaço para outro.

Perguntas para reflexão enquanto desenvolve:
🔹 O que acontece se um estudante tentar entrar quando a biblioteca já está cheia? 🔹 Como garantir que apenas 3 estudantes por vez fiquem dentro? 🔹 O que acontece se você não usar um semáforo nesse cenário?

Esse exercício ajudará a entender o controle de acesso em sistemas concorrentes de forma eficiente! 🚀
*/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_acessos_permitidos;

void *biblioteca(void *args)
{
	char nome_estudante[20];
	strcpy(nome_estudante, (char *) args);

	sem_wait(&sem_acessos_permitidos);

		printf("nome: %s\n", nome_estudante);
		sleep(2);

	sem_post(&sem_acessos_permitidos);

	return (NULL);
}

int main(void)
{
	int quantidade_estudantes = 5;
	pthread_t threads[quantidade_estudantes];
	char estudantes[10][10] = {
		"Jose", "Maria", "Pedro", "Luiza", "Paulo",
		"Bia", "Enzo", "Mateu", "Ana", "Betina",
	};
	int i = 0;

	sem_init(&sem_acessos_permitidos, 0, 3);
	while(i < quantidade_estudantes)
	{
		pthread_create(&threads[i], NULL, biblioteca, estudantes[i]);
		i++;
	}

	i = 0;
	while(i < quantidade_estudantes)
		pthread_join(threads[i++], NULL);

	return (0);
}