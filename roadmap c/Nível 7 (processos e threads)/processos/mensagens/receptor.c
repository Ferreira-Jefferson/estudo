#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

// Estrutura para a mensagem (deve ser a mesma do remetente)
struct mensagem {
	long tipo_msg;
	char texto_msg[256];
};

int main() {
	key_t chave;
	int id_fila;
	struct mensagem msg_recebida;

	// 1. Gera a mesma chave usada pelo remetente
	chave = ftok("remetente.c", 'A'); // IMPORTANTE: usa o mesmo arquivo e char
	if (chave == -1) {
		perror("ftok");
		exit(1);
	}

	// 2. Obtém o ID da fila de mensagens (ela já deve ter sido criada pelo remetente)
	id_fila = msgget(chave, 0666); // Não usa IPC_CREAT aqui
	if (id_fila == -1) {
		perror("msgget");
		exit(1);
	}

	printf("Fila de mensagens obtida com ID: %d\n", id_fila);

	// 3. Recebe a mensagem da fila (tipo 0 significa "qualquer tipo")
	if (msgrcv(id_fila, &msg_recebida, sizeof(msg_recebida.texto_msg), 0, 0) == -1) {
		perror("msgrcv");
		exit(1);
	}

	printf("Mensagem recebida: '%s'\n", msg_recebida.texto_msg);

	// 4. Remove a fila de mensagens após o uso (geralmente feito pelo processo que gerencia a fila)
	if (msgctl(id_fila, IPC_RMID, NULL) == -1) {
		perror("msgctl IPC_RMID");
		exit(1);
	}
	printf("Fila de mensagens removida.\n");

	return 0;
}