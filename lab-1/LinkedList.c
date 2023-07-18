/*
    Author : Dhruba Sinha(21CS8051)
    @ GNU/Linux Users' Group , NIT DGP
*/

#include <stdio.h>
#include <stdlib.h>

//define Node structure
struct ListNode 
{
	int val;
	struct ListNode *next1, *next2;
};

typedef struct ListNode Node;


//function for creating List-1, returns the head of list-1
//TC: O(N)
Node* Create1(int x, int N) {
	Node *head = (Node *)malloc(sizeof(Node));
	Node *last = head;
	last->val = x;
	last->next1 = last->next2 = NULL;
	for(int m=x+x; m<=N; m+=x) {		//iterate through all the multiples of x
		Node *ptr = (Node *)malloc(sizeof(Node));
		ptr->val = m;
		last->next1 = ptr;
		last = ptr;
		last->next1 = last->next2 = NULL;
	}
	
	return head;
}


//function for creating List-2, returns the head of list-2
//TC: O(2N) == O(N)
Node* Create2(int x, int y, int N, Node* head1) {
	Node *dummy = (Node *)malloc(sizeof(Node));
	Node *last = dummy;
	last->next1 = last->next2 = NULL;
	for(int m=y; m<=N; m+=y) {
	
		////iterate through all the multiples of y and check if it is divisible by x, that
		// tells us that this node is already present in list-1
		
		if((m % x)) {
			//not divisible by x, we have to create new one
			Node *ptr = (Node *)malloc(sizeof(Node));
			ptr->val = m;
			last->next2 = ptr;
			last = ptr;
			last->next1 = last->next2 = NULL;
		}
		else {
			//divisible, find and connect
			while(head1->val != m) {
				head1 = head1->next1;
			}
			
			last->next2 = head1;
			last = head1;
			last->next2 = NULL;
		}
	}
	
	Node *head = dummy->next2;
	free(dummy);
	return head;
}


//function for printing Lists;
//TC: O(N)
void print(Node *ptr) {
	int which;
	printf("traversing both list : ");
	while(ptr) {
		printf("%d ", ptr->val);
		if(ptr->next1 && ptr->next2) {
			printf("\nselect direction : ");
			scanf("%d", &which);
			if(which == 1) ptr = ptr->next1;
			else ptr = ptr->next2; 
		}
		else if(ptr->next1) ptr = ptr->next1;
		else if(ptr->next2) ptr = ptr->next2;
		else ptr = NULL;
	}
	
	printf("\n");
	
}

//function for printing both in sorted order
//using algorithm from merge sort(merge phase)
//TC: O(N)
void printboth(Node *ptr1, Node *ptr2) {
	printf("both list in sorted order : ");
	while(ptr1 && ptr2) {
		if(ptr1 == ptr2) {
			printf("%d ", ptr1->val);
			ptr1 = ptr1->next1;
			ptr2 = ptr2->next2;
		}
		else if(ptr1->val < ptr2->val) {
			printf("%d ", ptr1->val);
			ptr1 = ptr1->next1;
		}
		else {
			printf("%d ", ptr2->val);
			ptr2 = ptr2->next2;
		}
	}
	
	while(ptr1) {
		printf("%d ", ptr1->val);
		ptr1 = ptr1->next1;
	}
	
	while(ptr2) {
		printf("%d ", ptr2->val);
		ptr2 = ptr2->next2;
	}
	
	printf("\n");
}



//driver
int main(void)
{
	int a, b, N;
	scanf("%d %d %d", &a, &b, &N); 
	
	//List-1
	Node * l1 = Create1(a, N);
	//List-2
	Node * l2 = Create2(a, b, N, l1);
	
	print(l1);
	printboth(l1, l2);
	
	return 0;
}
