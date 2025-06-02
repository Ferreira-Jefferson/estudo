#include <stdio.h>

typedef struct {
    int id;
    char especification[50];
    double price;
} Menu;

double getPrice(Menu lanches[], size_t size, int id)
{
    int i;

    i = 0;
    while(i < size)
    {
        if(lanches[i].id == id)
            return lanches[i].price;
        i++;
    }
    return 0;
}

int main(void)
{
    Menu lanches[5] = {
        {1, "Cachorro Quente", 4.00},
        {2, "X-Salada", 4.50},
        {3, "X-Bacon", 5.00},
        {4, "Torrada simples", 2.00},
        {5, "Refrigerante", 1.50},
    };
    int id;
    int quantity;
    double price;
    size_t size;

    scanf("%d %d", &id, &quantity);

    size = (sizeof(lanches)/sizeof(Menu));
    price = getPrice(lanches, size, id);

    printf("Total: R$ %.2lf\n", price * quantity);

    return (0);
}