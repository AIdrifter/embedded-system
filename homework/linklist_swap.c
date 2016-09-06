#include <stdio.h>
#include <stdlib.h>

typedef struct _List {
    struct _List *next;
    int val;
} List;


// same
// 1 empty
// 2 empty

int swap(List **head, List *a , List *b)
{
	// a or b is null
	if( a == NULL || b == NULL )
		printf("a or b is NULL\n");

	List *tmp = &a;
	List *tmp = *head;
	if(tmp)

}

int add(List **head, int val)
{
	List *tmp = *head;
	if(tmp == NULL)
	{
		tmp = malloc(sizeof(List));
		tmp->next = NULL;
		tmp->val = val;
	}

	if(tmp!=NULL)
	{
		while(tmp->next!=NULL)
			tmp = tmp->next;

		tmp->next = malloc(sizeof(List));
		tmp = tmp->next;
		tmp->val=val;
		tmp->next=NULL;
	}
}


int print_list(List **head){
	List *tmp = *head;
	while ( tmp->next!=NULL )
		printf("%d ",tmp->val);
	puts("");
}

int main()
{
	List *head = NULL;
	add(&head,1);
	add(&head,2);
	add(&head,3);
	printf("here\n");
	print_list(&head);

}
