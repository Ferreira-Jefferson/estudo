#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("meu_fifo", O_RDONLY);
    char buffer[100];
    
    read(fd, buffer, sizeof(buffer));
    close(fd);
    printf("[Consumidor] Mensagem recebida: %s\n", buffer);

    return 0;
}
