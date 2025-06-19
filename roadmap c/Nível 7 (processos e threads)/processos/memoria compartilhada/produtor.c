#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h> // Para strerror
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

    // 1. Obter/Criar o segmento de memória compartilhada
    // IPC_CREAT: Se não existe, cria. IPC_EXCL: Erro se já existe.
    // 0666: Permissões de leitura/escrita para todos.
    shmid = shmget(SHM_KEY, sizeof(shared_data_t), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Segmento de memória compartilhada com ID: %d\n", shmid);

    // 2. Anexar o segmento de memória compartilhada ao espaço de endereço do processo
    shared_mem = (shared_data_t *) shmat(shmid, NULL, 0);
    if (shared_mem == (void *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Memória compartilhada anexada ao endereço: %p\n", (void *)shared_mem);

    // Inicializa o contador (apenas uma vez, idealmente, ou com controle)
    shared_mem->counter = 0;
    printf("Contador inicializado em: %d\n", shared_mem->counter);

    // 3. Obter/Criar o conjunto de semáforos (usamos apenas um semáforo)
    // IPC_CREAT: Cria se não existe.
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        // Se a memória já foi criada, desanexa e remove
        shmdt(shared_mem);
        shmctl(shmid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    printf("Conjunto de semáforos com ID: %d\n", semid);

    // 4. Inicializar o semáforo (definir seu valor para 1, indicando que está livre)
    union semun arg;
    arg.val = 1; // 1 significa que o semáforo está livre
    if (semctl(semid, 0, SETVAL, arg) == -1) { // 0 é o índice do semáforo no conjunto
        perror("semctl SETVAL");
        shmdt(shared_mem);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID); // Remove o semáforo em caso de erro
        exit(EXIT_FAILURE);
    }
    printf("Semáforo inicializado com valor 1.\n");

    // 5. Operações de incremento com semáforo
    struct sembuf sb;
    sb.sem_num = 0; // Índice do semáforo no conjunto (o primeiro e único)
    sb.sem_flg = 0; // Nenhuma flag especial

    for (int i = 0; i < 10; ++i) {
        // Operação P (wait): Decrementa o semáforo, bloqueia se 0
        sb.sem_op = -1; // Decrementa o valor do semáforo
        if (semop(semid, &sb, 1) == -1) { // 1 é o número de operações
            perror("semop P");
            break;
        }
        printf("Processo Produtor: Semáforo adquirido. Contador atual: %d\n", shared_mem->counter);

        // Seção crítica: Acesso à memória compartilhada
        shared_mem->counter++;
        printf("Processo Produtor: Contador incrementado para: %d\n", shared_mem->counter);
        
        // Simula algum trabalho
        sleep(1); 

        // Operação V (signal): Incrementa o semáforo, libera o recurso
        sb.sem_op = 1; // Incrementa o valor do semáforo
        if (semop(semid, &sb, 1) == -1) {
            perror("semop V");
            break;
        }
        printf("Processo Produtor: Semáforo liberado.\n");
        sleep(1); // Espera antes da próxima iteração
    }

    // 6. Desanexar e remover a memória compartilhada e o semáforo
    printf("\nDesanexando memória compartilhada...\n");
    if (shmdt(shared_mem) == -1) {
        perror("shmdt");
    }

    printf("Removendo segmento de memória compartilhada...\n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
    }

    printf("Removendo conjunto de semáforos...\n");
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
    }

    printf("Produtor finalizado.\n");

    return 0;
}