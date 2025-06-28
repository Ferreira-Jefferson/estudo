#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
	int value;
	struct node *next;
} Node;

typedef struct stack {
	Node *top;
	int size;
} Stack;

typedef struct queue {
	Node *head;
	Node *tail;
	int size;
} Queue;

Stack	*create_stack();
Node	*s_create_node(int value);
void	push(Stack *s, int value);
int		pop(Stack *s);
int		top(const Stack *s);
int		s_is_empty(const Stack *s);
int		s_get_size(const Stack *s);
void	free_stack(Stack **s);

Queue	*create_queue();
Node	*q_create_node(int value);
void	enqueue(Queue *q, int value);
int		dequeue(Queue *q);
int		peek(const Queue *q);
int		q_is_empty(const Queue *q);
int		q_get_size(const Queue *q);
void	free_queue(Queue **q);

void	print(const Node *n);

Stack	*create_stack(void)
{
	Stack *s = (Stack*) calloc(1, sizeof(Stack));
	if(!s)
	{
		perror("Error in stack create\n");
		return (NULL);
	}
	return (s);
}

Node	*s_create_node(int value)
{
	Node *node = (Node*) calloc(1, sizeof(Node));
	if(!node)
	{
		perror("Error in node create\n");
		return (NULL);
	}
	node->value = value;
	return (node);
}

void	push(Stack *s, int value)
{
	Node *new_node = s_create_node(value);
	if(!new_node)
		return ;

	new_node->next = s->top;
	s->top = new_node;
	s->size++;	
}

int	pop(Stack *s)
{
	if(s_is_empty(s))
		return (INT_MIN);

	Node *to_pop = s->top;
	int value = to_pop->value;
	s->top = s->top->next;
	s->size--;

	free(to_pop);
	return (value);	
}

int	top(const Stack *s)
{
	if(s_is_empty(s))
		return (INT_MIN);
	return (s->top->value);
}

int	s_is_empty(const Stack *s)
{
	return (s == NULL || s->top == NULL);
}

int	s_get_size(const Stack *s)
{
	if(s_is_empty(s))
		return (0);
	return (s->size);
}

void	free_stack(Stack **s)
{
	if(s == NULL || *s == NULL)
		return ;

	Node *current = (*s)->top;
	Node *to_free;
	while(current)
	{
		to_free = current;
		current = current->next;
		free(to_free);
	}
	free(*s);
	*s = NULL;
}

Queue *create_queue(void)
{
	Queue *q = (Queue*) calloc(1, sizeof(Queue));
	if(!q)
	{
		perror("Error in queue create\n");
		return (NULL);
	}
	return (q);
}

Node *q_create_node(int value)
{
	Node *node = (Node*) calloc(1, sizeof(Node));
	if(!node)
	{
		perror("Error in node create\n");
		return (NULL);
	}
	node->value = value;
	return(node);
}

void	enqueue(Queue *q, int value)
{
	Node *new_node = q_create_node(value);
	if(!new_node)
		return ;

	if(q_is_empty(q))
	{
		q->head = new_node;
		q->tail = q->head;
		q->size++;
		return ;
	}

	q->tail->next = new_node;
	q->tail = new_node;
	q->size++;	
}

int	dequeue(Queue *q)
{
	if(q_is_empty(q))
		return (INT_MIN);

	Node *to_dequeue = q->head;
	int value = to_dequeue->value;
	q->head = q->head->next;
	q->size--;

	free(to_dequeue);
	return (value);
}

int	peek(const Queue *q)
{
	if(q_is_empty(q))
		return (INT_MIN);
	return (q->head->value);
}

int q_is_empty(const Queue *q)
{
	return (q == NULL || q->size == 0);
}

int q_get_size(const Queue *q)
{
	if(q_is_empty(q))
		return (0);
	return (q->size);
}

void	free_queue(Queue **q)
{
	if(q == NULL || *q == NULL)
		return ;

	Node *current = (*q)->head;
	Node *to_free;
	while(current)
	{
		to_free = current;
		current = current->next;
		free(to_free);
	}
	free(*q);
	*q = NULL;
}

void	print(const Node *n)
{
	if(n == NULL)
		return ;

	int i = 0;
	while(n)
	{
		printf("[%d]: %d\n", i, n->value);
		n = n->next;
		i++;
	}	
}

int main(void) 
{
	Stack *s = create_stack();
	push(s, 100);
	push(s, 200);
	push(s, 300);
	print(s->top);
	free_stack(&s);

	printf("\n");

	Queue *q = create_queue();
	enqueue(q, 10);
	enqueue(q, 20);
	enqueue(q, 30);
	print(q->head);
	free_queue(&q);
	return (0);
}