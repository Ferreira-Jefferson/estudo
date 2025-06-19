#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

// Estrutura para a mensagem
struct mensagem {
    long tipo_msg;
    char texto_msg[256];
};

int main() {
    key_t chave;
    int id_fila;
    struct mensagem msg_enviar;

    // 1. Gera uma chave única para a fila de mensagens
    chave = ftok("remetente.c", 'A');
    if (chave == -1) {
        perror("ftok");
        exit(1);
    }

    // 2. Cria ou obtém o ID da fila de mensagens
    id_fila = msgget(chave, 0666 | IPC_CREAT);
    if (id_fila == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Fila de mensagens criada/obtida com ID: %d\n", id_fila);

    // 3. Prepara a mensagem para envio
    msg_enviar.tipo_msg = 1; // Tipo da mensagem
    strcpy(msg_enviar.texto_msg, "Ola, Jefferson! Esta eh uma mensagem da fila!");

    // 4. Envia a mensagem para a fila
    if (msgsnd(id_fila, &msg_enviar, sizeof(msg_enviar.texto_msg), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Mensagem enviada: '%s'\n", msg_enviar.texto_msg);

    // 5. (Opcional) Remove a fila de mensagens após o uso
    // Geralmente, a remoção é feita pelo processo receptor ou por um gerenciador.
    // Para este exemplo, vou deixar comentado para que o receptor possa ler.
    // if (msgctl(id_fila, IPC_RMID, NULL) == -1) {
    //     perror("msgctl IPC_RMID");
    //     exit(1);
    // }
    // printf("Fila de mensagens removida.\n");

    return 0;
}