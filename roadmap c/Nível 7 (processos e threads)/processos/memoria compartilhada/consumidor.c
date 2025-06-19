#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include "shm_data.h" // Inclui a definição de shared_data_t, SHM_KEY, SEM_KEY

// Para o semáforo (union semun não é definida em sys/sem.h por padrão no Linux)
union semun {
    int val;                /* valor para SETVAL */
    struct semid_ds *buf;   /* buffer para IPC_STAT & IPC_SET */
    unsigned short *array;  /* array para GETALL & SETALL */
    struct seminfo *__buf;  /* buffer para IPC_INFO */
};

int main() {
    int shmid;
    shared_data_t *shared_mem;
    int semid;

    // 1. Obter o segmento de memória compartilhada (não cria, apenas anexa ao existente)
    shmid = shmget(SHM_KEY, sizeof(shared_data_t), 0666);
    if (shmid == -1) {
        perror("shmget");
        fprintf(stderr, "Certifique-se de que o produtor está rodando primeiro e criando a memória compartilhada.\n");
        exit(EXIT_FAILURE);
    }
    printf("Segmento de memória compartilhada com ID: %d\n", shmid);

    // 2. Anexar o segmento de memória compartilhada
    shared_mem = (shared_data_t *) shmat(shmid, NULL, 0);
    if (shared_mem == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Memória compartilhada anexada ao endereço: %p\n", (void *)shared_mem);

    // 3. Obter o conjunto de semáforos
    semid = semget(SEM_KEY, 1, 0666);
    if (semid == -1) {
        perror("semget");
        shmdt(shared_mem); // Desanexa a memória compartilhada
        fprintf(stderr, "Certifique-se de que o produtor está rodando primeiro e criando o semáforo.\n");
        exit(EXIT_FAILURE);
    }
    printf("Conjunto de semáforos com ID: %d\n", semid);

    // 4. Operações de decremento com semáforo
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_flg = 0;

    for (int i = 0; i < 10; ++i) {
        // Operação P (wait): Decrementa o semáforo, bloqueia se 0
        sb.sem_op = -1;
        if (semop(semid, &sb, 1) == -1) {
            perror("semop P");
            break;
        }
        printf("Processo Consumidor: Semáforo adquirido. Contador atual: %d\n", shared_mem->counter);

        // Seção crítica: Acesso à memória compartilhada
        shared_mem->counter--;
        printf("Processo Consumidor: Contador decrementado para: %d\n", shared_mem->counter);
        
        // Simula algum trabalho
        sleep(1);

        // Operação V (signal): Incrementa o semáforo, libera o recurso
        sb.sem_op = 1;
        if (semop(semid, &sb, 1) == -1) {
            perror("semop V");
            break;
        }
        printf("Processo Consumidor: Semáforo liberado.\n");
        sleep(1); // Espera antes da próxima iteração
    }

    // 5. Desanexar a memória compartilhada (o produtor será responsável por remover)
    printf("\nDesanexando memória compartilhada...\n");
    if (shmdt(shared_mem) == -1) {
        perror("shmdt");
    }

    printf("Consumidor finalizado.\n");

    return 0;
}