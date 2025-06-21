#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int value;
	struct node *prev;
	struct node *next;
} Node;

// quantidade de itens
int get_size(const Node *head)
{
	int i = 0;

	while(head)
	{
		head = head->next;
		i++;
	}
	return (i);
}
// criar
Node *create(int value)
{
	Node *node = (Node*) malloc(sizeof(Node));
	if(!node)
	{
		perror("Error in creating");
		return (NULL);
	}

	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

// inserir no inicio
void insert_begin(Node **head, int value)
{
	Node *new = create(value);
	if(!new)
		return ;

	if(!(*head))
	{

		*head = new;
		return ;
	}

	(*head)->prev = new;
	new->next = (*head);
	*head = new;
}

// inserir no final
void insert_end(Node **head, int value)
{
	Node *new =  create(value);
	if(!new)
		return ;

	if(!(*head))
	{
		*head = new;
		return ;
	}

	Node *current = *head;		
	while (current->next)
		current = current->next;
	
	new->prev = current;
	current->next = new;
}

// inserir no index
void insert_in_index(Node **head, int value, size_t index)
{
	size_t i = 0;

	if(!(*head) && index != 0)
		return ;
	
	if(((int)index) > get_size(*head))
		return ;
	
	Node *new = create(value);
	if (index == 0)
	{
		if(head)
			(*head)->prev = new;
		new->next = *head;
		*head = new;	
		return ;
	}

	Node *current = *head;
	while((i+1) < index)
	{
		current = current->next;
		i++;
	}

	new->next = current->next;
	if(current->next)
		current->next->prev = new;
	new->prev = current;
	current->next = new;
}

// atualizar pelo index
void update_by_index(Node **head, int value, size_t index)
{
	Node *current = *head;
	size_t i = 0;

	if(!current)
		return;

	while(i < index)
	{
		current = current->next;
		i++;
	}

	current->value = value;
}

// remover do inicio
void remove_begin(Node **head)
{
	if(!(*head))
		return ;

	Node *to_free = *head;
	*head = (*head)->next;
	free(to_free);
}

// remover do final
void remove_end(Node **head)
{
	if(!(*head))
		return ;

	Node *current = *head;
	if(!current->next)
	{
		free(current);
		*head = NULL;
		return ;
	}

	while(current->next)
		current = current->next;

	if(current->prev)
		current->prev->next = NULL;
	free(current);
}

// remover pelo index
void remove_by_index(Node **head, size_t index)
{
	size_t i = 0;
	
	if(!(*head))
		return ;
	
	Node *current = *head;
	if(!current->next)
	{
		free(current);
		*head = NULL;
		return ;
	}

	if(index == 0)
	{
		current->next->prev = NULL;
		*head = current->next;
		free(current);
		return ;
	}

	while(current != NULL && i < index)
	{
		current = current->next;
		i++;
	}
	
	if(current != NULL && i == index)
	{
		if(current->prev)
			current->prev->next = current->next;
		if(current->next)
			current->next->prev = current->prev;
		free(current);
		current = NULL;
	}
}

// ver se tem o valor
int has_value(const Node *head, int value)
{
	int i = 0;

	while(head)
	{
		if(head->value == value)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

// imprimir valores
void print_list(const Node *head)
{
	int i = 0;
	while(head)
	{
		printf("[%d]: %d\n", i, head->value);
		head = head->next;
		i++;
	}
}

// liberar
void free_node(Node **head)
{
	Node *current = *head;
	while(current)
	{
		Node *to_free = current;
		current = current->next;
		free(to_free);
	}
	free(*head);
}

int main(void)
{
	Node *node = NULL;
	insert_begin(&node, 30);
	insert_begin(&node, 20);
	insert_begin(&node, 10);
	print_list(node);
	
	printf("\n");
	printf("size: %d\n", get_size(node));
	printf("has 5: %d\n", has_value(node, 5));
	printf("has 30: %d\n", has_value(node, 30));
	
	printf("\n");
	insert_end(&node, 40);
	insert_end(&node, 50);
	print_list(node);

	printf("\n");
	printf("size: %d\n", get_size(node));
	printf("has 50: %d\n", has_value(node, 50));
	
	printf("\n");
	insert_in_index(&node, 60, 2);
	update_by_index(&node, 70, 3);
	remove_begin(&node);
	remove_end(&node);
	remove_by_index(&node, 4);
	remove_by_index(&node, 3);
	print_list(node);

	return (0);
}