#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	size_t index;
	struct node *next;	
} Node;

Node *create_node(int value)
{
	Node *node = (Node*) malloc(sizeof(Node));

	if(!node)
	{
		fprintf(stderr, "Error: fail in memory alocation.\n");
		return (NULL);
	}

	node->value = value;
	node->next = NULL;
	return (node);
}

void update_index(Node **head)
{
	if(!(*head))
		return ;

	size_t current_index = (*head)->index;
	Node *next = (*head)->next;

	while(next != NULL)
	{
		next->index = ++current_index;
		next = next->next;
	}
}

void insert_in_begin(Node **head, int value)
{
	Node *node_aux = create_node(value);
	if (*head == NULL)
	{
		*head = node_aux;
		(*head)->index = 0;
		return ;
	}

	node_aux->index = 0;
	node_aux->next = *head;
	*head = node_aux;
	update_index(head);
}

void insert_in_end(Node **head, int value)
{
	Node *node_aux = create_node(value);
	if (*head == NULL)
	{
		*head = node_aux;
		(*head)->index = 0;
		return ;
	}

	Node *node_current = *head;
	while(node_current->next != NULL)
	{
		node_current = node_current->next;
	}
	node_aux->index = node_current->index + 1;
	node_current->next = node_aux;
}

void print_node(const Node *head)
{
	int i = 0;
	while (head != NULL)
	{
		printf("[%d]: %d\n", (int)head->index, head->value);
		head = head->next;
		i++;		
	}	
}

void free_node(Node **head)
{
	Node *current = *head;
	Node *next;

	while(current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

int main(void)
{
	Node *my_node = create_node(5);
	insert_in_begin(&my_node, 10);
	insert_in_end(&my_node, 15);
	insert_in_end(&my_node, 20);
	insert_in_begin(&my_node, 1);

	print_node(my_node);

	free_node(&my_node);
	return (0);
}
