#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mutex_recurso = PTHREAD_MUTEX_INITIALIZER;  
pthread_cond_t cond_recurso = PTHREAD_COND_INITIALIZER;  
sem_t sem_prioridade;  // Semáforo para controlar prioridade

int recurso_disponivel = 0;  // 1 significa que o recurso está livre

void *processar_tarefa(void *arg) {
    int id = *(int *)arg;

    // 🎯 Evitando Starvation: Garantindo acesso justo com semáforo
    sem_wait(&sem_prioridade);  // Aguarda sua vez de processamento

    // 🔒 Mutex para evitar condição de corrida
    pthread_mutex_lock(&mutex_recurso);
    while (!recurso_disponivel) {
        printf("[Thread %d] Esperando recurso...\n", id);
        pthread_cond_wait(&cond_recurso, &mutex_recurso); // Espera até que o recurso seja liberado
    }
    
    // 🟢 Thread adquire o recurso
    recurso_disponivel = 0;
    printf("[Thread %d] Está processando o recurso!\n", id);
    sleep(1);  // Simula um processamento complexo

    // ✅ Libera o recurso e sinaliza outras threads
    recurso_disponivel = 1;
    pthread_cond_signal(&cond_recurso);  
    pthread_mutex_unlock(&mutex_recurso);
    
    sem_post(&sem_prioridade);  // Libera vaga no semáforo, garantindo justiça

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    sem_init(&sem_prioridade, 0, 2);  // Apenas 2 threads podem acessar o recurso de cada vez

    // Criando múltiplas threads
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, processar_tarefa, &ids[i]);
    }

    // 🔁 Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 🔚 Limpa recursos
    sem_destroy(&sem_prioridade);
    pthread_mutex_destroy(&mutex_recurso);
    pthread_cond_destroy(&cond_recurso);

    printf("Processamento concluído!\n");
    return 0;
}
