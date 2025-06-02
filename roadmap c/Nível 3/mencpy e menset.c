#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
} User;

int main(void)
{
    User user1 = {10, "Jefferson"};
    User user_cpy;

    memset(user_cpy.nome, '*', sizeof(user_cpy.nome));
    user_cpy.nome[sizeof(user_cpy.nome) - 1] = '\0';

    printf("Nome cpy: %s\n\n",  user_cpy.nome);

    printf("id: %d\n",  user1.id);
    printf("Nome: %s\n\n",  user1.nome);

    memcpy(&user_cpy, &user1, sizeof(User));

    printf("id cpy: %d\n",  user_cpy.id);
    printf("Nome cpy: %s\n\n",  user_cpy.nome);

    return (0);    
}