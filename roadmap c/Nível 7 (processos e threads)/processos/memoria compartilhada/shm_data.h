// Em um arquivo de cabeçalho, como "shm_data.h"
#ifndef SHM_DATA_H
#define SHM_DATA_H

typedef struct {
    int counter;
} shared_data_t;

#define SHM_KEY 1234  // Chave para a memória compartilhada
#define SEM_KEY 5678  // Chave para o semáforo

#endif