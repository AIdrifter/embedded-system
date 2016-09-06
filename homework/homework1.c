#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node{
	struct Node* next;
	int value;
} Node;

void add_front(Node** head, int value){
	Node* new_node = (Node *)malloc(sizeof(Node));
	new_node->value = value;
	if(!(*head)){
		new_node->next = NULL;
		(*head) = new_node;
	}else{
		new_node->next = (*head);
		(*head) = new_node;
	}
	return;
}

void remove_link(Node** head, int value_to_remove){
	Node* temp_node = NULL;
	Node* current_node = (*head);
	if((*head)->value == value_to_remove){
		(*head) = (*head)->next;
	}else{
		while(current_node){
			if(current_node->value == value_to_remove){
				temp_node = current_node->next;
				current_node->next = NULL;
				current_node = temp_node;
			}
			current_node = current_node->next;
		}
	}
	return;
}

void remove_duplicates(Node** head){
	Node* current_node = (*head);
	Node* previous_node = NULL;

	while(current_node->next){
		previous_node = current_node;
		current_node = current_node->next;
		if(previous_node->value == current_node->value){
			previous_node->next = current_node->next;
			current_node->next = NULL;
			current_node = previous_node;
		}
	}
	return;
}

void display_Node(Node* head){
	Node* current_node = head;
	printf("Linked Node:\n");
	while(current_node){
		printf("[%d]-->", current_node->value);
		current_node = current_node->next;
	}
	printf("NULL\n");
}


int swap(Node **head, Node **a1 , Node **b1)
{
	// head 要malloc空間
	assert(head);
	assert(a1);
	assert(b1);
	assert(a1!=b1);
	// c only 0 is true ;  -1 1 or others  is false 
	// assert only '0' will pass

	Node *curr = *head;
	Node *prevA = NULL; Node *prevB = NULL;
	Node *a=*a1;
	Node *b=*b1;

	// find a
	while (curr != a) {
		prevA = curr; curr = curr->next;
	}
	printf("prevA %d\n",prevA->value);
	printf("a %d\n",a->value);

	curr = *head;

	// find b
	while (curr != b) {
		prevB = curr; curr = curr->next;
	}
	printf("prevB %d\n",prevB->value);
	printf("b %d\n",b->value);

	// get a and b,swap it
//	if (prevA && prevB) {
//		prevA->next = b; prevB->next = a;
//		Node *tmp = a->next;
//		a->next = b->next;
//	}
	if (prevA && prevB) {
		Node *tmp = a->next;
		a->next=b->next;
		prevA->next=b;
		b->next=tmp;
		prevB->next=a;
	}

}

int main(int argc, char const *argv[])
{
	Node* head = NULL;

	int i ;
	for(i = 0; i<=10; i++)
	{
		add_front(&head, i);
	}
	display_Node(head);

	Node *num2 = head;
	// node 2
	for(i = 0; i<=2; i++)
	{
		num2 = num2->next;
	}

	// node 3
	Node *num3=head;
	for(i = 0; i<=5; i++)
	{
		num3 = num3->next;
	}

	swap(&head,&num2,&num3);
	display_Node(head);


//	remove_duplicates(&head);
//	remove_link(&head, 10);
//	display_Node(head);
	return 0;
}


