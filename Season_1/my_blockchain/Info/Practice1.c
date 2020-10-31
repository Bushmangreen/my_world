#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int value;
	struct node *next;
}node_t;

void print_nodes(node_t* head)
{
	while(head != NULL)
	{
		printf(" %d ->", head->value);
		head = head->next;
	}

	printf("\n");
}

void free_nodes(node_t *head)
{
	node_t *now = head;
	node_t *prev;

	while(now != NULL)
	{
		prev = now;
		now = now->next;
		free(prev);
	}	
}

node_t* new_node(int value)
{
	node_t *temp = malloc(sizeof(node_t));
	temp->value = value;
	temp->next = NULL;
	return temp;
}

void push(int value, node_t** head, node_t** tail)
{
	node_t *temp = new_node(value); 

	if(*head == NULL)
	{
		*head = temp;
		*tail = *head;
	}
	else
	{
		(*tail)->next = temp;
		*tail = temp;
	}

}

void push2(int value, node_t** head)
{
	node_t *temp = new_node(value);


	if(*head == NULL)
	{
		*head = temp;
	}
	else 
	{
		node_t *now = *head;
		node_t* prev;
		while(now != NULL)
		{
			prev = now;
			now = now ->next;
		}

		prev->next = temp;
		prev = temp;
	}
}

void reverse(node_t** head, node_t** tail)
{
	// 1->2->3->4->5
    // t<-2
    //       p   
    node_t *prev_node = NULL;
    node_t *next_node;
    node_t *now = *head;

	*head = *tail;
	*tail = now;
	

	while(now != NULL)
	{
		next_node = now->next;
		now->next = prev_node;

		prev_node = now;
		now = next_node;	
	}

 	

}

int main(int argc, char const *argv[])
{
	node_t *head = NULL;
	node_t *tail = head;

	for (int i = 1; i < 6; i++)
		push(i, &head, &tail);
	
	reverse(&head, &tail);
	print_nodes(head);
	free_nodes(head);
	return 0;
}