#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int nid;
	struct node  *next;
	struct block *blocks
}node_t;

typedef struct block
{
	char* bid;
	struct block *next;
}block_t;

void print_linked_list(node_t* head)
{
	node_t* temp = head;

	while(temp != NULL)
	{
		printf("%d - ", temp->value);
		temp = temp->next;

	}
	printf("\n");
}

void free_the_list(node_t* head)
{
	node_t *n = head;
	while(n)
	{
	   	node_t *n1 = n;
	   	n = n->next;
	   	free(n1);
	}
}

node_t* create_new_node(int value)
{
	node_t* result = malloc(sizeof(node_t));
	result->value = value;
	result->next = NULL;
	return result;
}

void insert_head(int value, node_t** head, node_t **tail) // inserts new head;
{
	node_t* temp;
	temp = create_new_node(value);
	if(*head == NULL)
	{
		*head = temp;
		*tail = *head;
	}
	else
	{
		temp -> next = *head;
		*head = temp;
	}
}

node_t* pop_head(node_t** head) // removes head
{
	if (*head == 0)
		return NULL;
	node_t* temp;
	temp = *head;
	*head = (*head) -> next;
	return temp;
}

void push(int value, node_t** head, node_t** tail)// inserts item to the end of list
{
	node_t* temp;
	temp = create_new_node(value);
	if(*head == NULL)
	{
		*head = temp;
		*tail = *head;
	}
	else
	{
		(*tail) -> next = temp;
		*tail =  temp;
	}
}

node_t* pop_tail(node_t** head, node_t** tail) // pops last item
{
	if (*head == NULL)
		return NULL;
	node_t *current = *head;
	node_t *new_tail = current;

	while(current->next)
	{
		new_tail = current;
		current = current->next;
	}
	
	if (*head == *tail)
	{
		*head = NULL;
		*tail = NULL;
	}
	*tail = new_tail;
	(*tail) -> next = NULL;

	return current;
}

node_t* find_node(node_t* head, int value)
{
	node_t* tmp = head;
	while(tmp != NULL)
	{
		if(tmp->value == value) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void insert_after_node(node_t* node_to_insert, node_t* new_node)
{
	new_node->next = node_to_insert->next;
	node_to_insert->next = new_node;
}

node_t* remove_node(int value, node_t** head, node_t** tail)
{
	node_t *temp = find_node(*head, value);
	if (temp == NULL)
		return NULL;

	if(*head == temp)
	{
		temp = pop_head(head);
		return temp;
	}
	if(*tail == temp)
	{
		temp = pop_tail(head,tail);
		return temp;
	}

	node_t *current = *head;
	node_t *before = current;

	while(current->next)
	{
		if (current -> next == temp)
			break;	
		current = current->next;
	}

	before->next = temp->next;
	return temp;
}

int main(int ac, char *av[])
{
	node_t* head = NULL;
	node_t* tail = head;
	node_t* temp;
	
	push(1, &head, &tail);

	push(2, &head, &tail);
 	
 	push(3, &head, &tail);

	temp = remove_node(3,&head,&tail);
 	

	print_linked_list(head);
	free_the_list(head);
	
	return 0;
}


/* use info 
	//  insert_tail(1, &head, &tail);

	// insert_tail(2, &head, &tail);
 	
 	// insert_tail(3, &head, &tail);

	//temp = create_new_node(25);
	//insert_head(&head,temp);

 	[s0]> add node 12 

 	add new node into list
 	increment the length of the list
 	if it is the node is 1 it is synced 
 	else if node is 2 or more display [-2] list is not synced
 	add block to node 12
 	sync nodes, means check the get the 


	
   	// head -> n1(1) -> n2(2) -> n3(3) -> NULL
   	// tmp -> head;
	//insert_tail(1,&head,&tail);
	// tmp = create_new_node(1);
	// insert_head(&head, tmp);

	*/
