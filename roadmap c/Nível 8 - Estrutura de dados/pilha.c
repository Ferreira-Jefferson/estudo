#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
	int value;
	struct node *next;
} Node;

// Criar/Inicializar a pilha
Node *create_node(int value)
{
	Node *new = (Node*) malloc(sizeof(Node));
	if(!new)
	{
		perror("Error in creating\n");
		return (NULL);
	}
	new->value = value;
	new->next = NULL;
	return(new);
}

// Verificar se a pilha está vazia
int is_empty(const Node *head)
{
	if(!head)
		return (1);
	return(0);
}

// Inserir um elemento (push)
void push(Node **head, int value)
{
	Node *new = create_node(value);
	if(!new)
		return ;
	new->next = *head;
	*head = new;
}

// Remover um elemento (pop)
void pop(Node **head)
{
	if(is_empty(*head))
		return ;
	Node *first = *head;
	*head = first->next;
	free(first);
}

// Acessar o elemento do topo (peek/top)
int top(const Node *head)
{
	if(is_empty(head))
	{
		perror("Error: Empty stack. Cannot peek at top element.\n");
		return (INT_MIN);
	}
	return head->value;
}

// Obter o tamanho da pilha
int size_stack(const Node *head)
{
	const Node *current = head;
	int i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

// Limpar/Liberar a pilha
void free_stack(Node **head)
{
	Node *current = *head;
	Node *to_free;
	while (current)
	{
		to_free = current;
		current = current->next;
		free(to_free);
	}
	free(*head);
	*head = NULL;
}

// Mostrar valores
void print_stack(const Node *head)
{
	Node *current = (Node*) head;
	int i = 0;
	int len = size_stack(head);
	if(is_empty(current))
	{
		printf("[]\n");
		return ;
	}
	printf("[");
	while(current)
	{
		printf("%d", current->value);
		if(i < len-1)
			printf(", ");
		current = current->next;
		i++;
	}
	printf("]\n");
}

int main(void)
{
	Node *stack = NULL;
	push(&stack, 20);
	push(&stack, 30);
	print_stack(stack);
	printf("IsEmpty: %d\n", is_empty(stack));
	printf("Top: %d\n", top(stack));
	printf("Size: %d\n", size_stack(stack));

	pop(&stack);
	pop(&stack);
	pop(&stack);
	pop(&stack);
	print_stack(stack);
	printf("IsEmpty: %d\n", is_empty(stack));
	printf("Top: %d\n", top(stack));
	printf("Size: %d\n", size_stack(stack));
	free_stack(&stack);

}