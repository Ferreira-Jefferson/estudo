#include <stdlib.h>
#include <stdio.h>

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
		perror("Erro na criação./n");
		return (NULL);
	}
	node->value = value;
	node->index = 0;
	return (node);
}

void update_index(Node **head)
{
	if(!(*head))
		return ;

	Node *current = *head;
	size_t current_index = (*head)->index;
	while(current)
	{
		current->index = current_index++;
		current = current->next;
	}
}

void insert_in_begin(Node **head, int value)
{
	Node *new_node = create_node(value);
	if(!new_node)
		return ;
	
	if(!(*head))
	{
		*head = new_node;
		return ;
	}

	new_node->next = *head;
	*head = new_node;
	update_index(head);
}

void insert_in_end(Node **head, int value)
{
	Node *new_node = create_node(value);
	if(!new_node)
		return ;

	if(!(*head))
	{
		*head = new_node;
		return ;
	}

	Node *current = *head;
	while (current->next)
		current = current->next;
		
	current->next = new_node;
	update_index(head);
}

void insert_at_index(Node **head, int value, size_t index)
{
	Node *new_node = create_node(value);
	if(!new_node)
		return ;
	
	if(!(*head) || index == 0)
	{
		new_node->next = *head;
		*head = new_node;
		update_index(head);
		return ;
	}

	
	Node *current = *head;
	int i = 0;

	while(current->next != NULL && current->index < (index-1))
		current = current->next;
	
	new_node->next = current->next;
	current->next = new_node;

	update_index(head);

}

void update_by_index(Node **head, int value, size_t index)
{
	Node *current = *head;

	while (current != NULL && current->index != index)
		current = current->next;

	if(current == NULL)
		return ;

	current->value = value;
}

void print_node(const Node *head)
{
	while(head)
	{
		printf("[%ld]: %d\n", head->index, head->value);
		head = head->next;
	}
}

void remove_at_index(Node **head, size_t index)
{
	Node *current = *head;
	
	if(current == NULL)
		return ;

	if(index == 0)
	{	
		*head = (*head)->next;
		(*head)->index = 0;
		update_index(head);
		return ;
	}
	
	Node *prev = current;
	while(current->next != NULL && current->index < index)
	{
		prev = current;
		current = current->next;
	}
	
	if(current->index == index)
	{
		prev->next = current->next;
		free(current);
		update_index(head);
	}
}

void free_node(Node **head)
{
	Node *current = *head;
	Node *to_free;

	while(current)
	{
		to_free = current;
		current = current->next;
		free(to_free);
	}
	free(*head);
}

int	main(void)
{
	Node *node = create_node(1);
	insert_in_end(&node, 2);
	insert_in_begin(&node, 0);
	insert_in_end(&node, 3);
	insert_at_index(&node, 10, 3);
	update_by_index(&node, 20, 2);
	remove_at_index(&node, 2);

	print_node(node);
	return (0);
}