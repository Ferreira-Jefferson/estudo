#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

typedef struct queue {
    Node *top;
    int size;
} Queue;

// Criar/Inicializar a fila
Node *create_node(int value)
{
	Node *node = (Node*) malloc(sizeof(Node));
	if(!node)
	{
		perror("Error in node creating\n");
		return (NULL);
	}
	node->value = value;
	node->next = NULL;
	return (node);
}

Queue *create_queue()
{
	Queue *q = (Queue*) malloc(sizeof(Queue));
	if(!q)
	{
		perror("Error in queue creating\n");
		return (NULL);
	}
	q->top = NULL;
	q->size = 0;
}

int is_empty(const Queue *head)
{
	return (head == NULL || head->top == NULL);
}

// Inserir um elemento no final (enqueue)
void enqueue(Queue *q, int value)
{
	if (q == NULL) {
        fprintf(stderr, "Erro: Pilha nao inicializada (NULL).\n");
        return;
    }
	Node *new = create_node(value);
	if(!new)
		return ;
	
	new->next = q->top;
	q->top = new;
	q->size++;
}

// Remover um elemento do início (dequeue)
int dequeue(Queue *q)
{
	if(is_empty(q))
		return (INT_MIN);
	
	int value = q->top->value;
	Node *to_free = q->top;
	q->top = q->top->next;
	free(to_free);
	q->size--;
	return (value);
}

// Acessar o elemento do início (peek/front)
int peek(Queue *q)
{
	if(is_empty(q))
		return (INT_MIN);
	return (q->top->value);
}

// Obter o tamanho da fila
int size_queue(const Queue *q)
{
	if (is_empty(q))
		return (0);
	return q->size;
}

// Mostrar valores
int print_queue(const Queue *q)
{
	Node *node = q->top;
	int size = q->size;

	printf("[");
	while(size)
	{
		printf("%d", node->value);
		if(size > 1)
			printf(", ");

		node = node->next;
		size--;
	}
	printf("]\n");
}

// Limpar/Liberar a fila
void free_enqueue(Queue **q)
{
	Node *current = (*q)->top;
	Node *to_free;

	while(current)
	{
		to_free = current;
		current = current->next;
		free(to_free);
	}
	free(*q);
}

int main(void)
{
	Queue *queue = create_queue();
	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);
	print_queue(queue);
	printf("size: %d\n", size_queue(queue));

	dequeue(queue);
	dequeue(queue);
	print_queue(queue);
	printf("size: %d\n", size_queue(queue));
	
	int value = peek(queue);
	printf("peek: %d\n", value);
	
	free_enqueue(&queue);
	return (0);
}