#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include"linkedlist.h"

#define random(x,y) (rand()%(y-x) + x)

struct Node* createNode(struct Data input)
{
	struct Node* temp;
	temp=malloc(sizeof (struct Node));
	temp->obj.value = input.value;
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

struct List * createList()
{
	struct List * temp;
	temp = malloc(sizeof(struct List));
	temp->head = NULL;
	temp->tail = NULL;
	return temp;
}

void display(struct List *list)
{
	struct Node * temp;
	temp = list->head;//breaks if list is empty
	printf("\nHead..");
	while(temp!=NULL)
	{
		printf("%d-->",temp->obj.value);
		temp = temp->next;
	}
	printf("..Tail\n");
}
struct Node * insertData(struct List *list,int index,struct Data value)
{
	struct Node * temp_head = list->head;
	struct Node * temp;
	int count = 0;
	if(list->head != NULL)
	{
		while(count<index && temp_head->next != NULL )
		{
			temp = temp_head;
			temp_head = temp_head -> next;
			count++;
		}
	}
	else
	{
//		printf("Inserting first element\n");
		list->head = createNode(value);
		list->tail = list->head;
		return list->head;
	}

	if(index<0) 
	{
		printf("index out of bound ");
		return NULL;
	}
//Insert in between
	if(index == 0)
	{
		temp = createNode(value);
		temp->next = list->head;
		list->head->prev = temp;
		list->head = temp;
		return list->head;
	}
	if(count==index)
	{
//		printf("inserting not at last element");
		temp -> next = createNode(value);
		temp -> next -> prev = temp;
		temp -> next -> next = temp_head;
		temp_head -> prev = temp->next;
		return temp->next;

	}
//Insert at the end
	else if(temp_head->next == NULL)
	{
//		printf("Inserting at the end");
		temp_head -> next	= createNode(value);
		temp_head -> next->prev = temp_head;
		list->tail = temp_head->next;
		return temp_head-> next;
	}
}

int removeData(struct List *list,int index)
{
        struct Node * temp;
	struct Node * temp_head = list->head;
	int del_val;
        int count = 0;
        if(list->head != NULL)
        {
                while(count<index && temp_head->next != NULL )
                {
                        temp = temp_head;
                        temp_head = temp_head -> next;
                        count++;
                }
        }
        else
       {
//                printf("No elements to be delted");
                return INT_MAX;
        }

        if(index<0) 
        {
//                printf("index out of bound ");
                return INT_MAX;
        }

        if(index == 0 || list->head->next == NULL)
        {
                del_val = list->head->obj.value;
//if it's not the only element in the list
		if(list->head->next!=NULL)
		{
			list->head->next->prev = NULL;
			free(list->head);
			list->head = list->head->next;
		}
		else
		{
			free(list->head);
			list->head = NULL;
		} 
               return del_val;
        }

        if(temp_head->next == NULL)
        {
//Deleting the last element
		del_val = temp_head->obj.value;
		free(temp->next);
                temp->next = NULL;
                return del_val;

        }
        else if(index == count)
        {
                del_val = temp_head->obj.value;
		temp_head->next->prev = temp;
		temp->next = temp_head->next;
		free(temp_head);
		temp_head = NULL;
                return del_val;
        }

}
void searchForward(struct List *list,struct Data find)
{

        struct Node * temp;
	int count = 0;
        temp = list->head;//breaks if list is empty
	printf("%d",find.value);
        while(temp!=NULL)
        {
                if(find.value == temp->obj.value)
		{
			printf("Searching forward--%d found at %d\n",find.value,count);
			return;
		}
		count++;
                temp = temp->next;
        }
        printf("Element not found");


}

void searchBackward(struct List *list,struct Data find)
{

        struct Node * temp;
        int count = 0;
        temp = list->tail;//breaks if list is empty
        printf("%d",find.value);
        while(temp!=NULL)
        {
                if(find.value == temp->obj.value)
                {
                        printf("Searching Backward--%d found at %d\n",find.value,count);
                        return;
                }
                count++;
                temp = temp->prev;
        }
        printf("Element not found");


}

void dealloc(struct List *list)
{
	struct Node *temp;
	if(list->head!=NULL)
	{
		while(list->head!=NULL)
		{
			temp = list->head;
			list->head = list->head->next;
			free(temp);
		}
	}

}
struct Node * front (struct List *list)
{
	return list->head;
}
void push(struct Stack *stack,int value)
{
	struct Data insert;
	insert.value = value;
	insertData(stack->stack,0,insert);
}
int pop(struct Stack *stack)
{
	return removeData(stack->stack,0);
}

void enqueue(struct Queue *queue,int value)
{
	struct Data insert;
	insert.value = value;
	insertData(queue->queue,INT_MAX,insert);
}
int dequeue(struct Queue *queue)
{
	return removeData(queue->queue,0);
}

int main()
{
//performing some specific task, as per my requirement at this point, the functions are generic.
	int count=0,rand_num,rand_index;
	struct List *list1;

	struct Stack *stack1,*stack2;
	struct Queue *queue1,*queue2;

	struct Data num;

	list1 = createList();

	stack1 = malloc(sizeof(struct Stack));
	stack2 = malloc(sizeof(struct Stack));

	queue1 = malloc(sizeof(struct Queue));
	queue2 = malloc(sizeof(struct Queue));

	stack2->stack = createList();
	stack1->stack = createList();
	queue1->queue = createList();
	queue2->queue = createList();

	srand(time(NULL));

	while(count < 10)
	{
		rand_index = random(0,10); 
		rand_num   = random(0,1000);
		num.value = rand_num;
		insertData(list1,rand_index,num);
		count++;
		display(list1);

	}
	num.value = random(0,1000);

	insertData(list1,20,num);
	display(list1);

	printf("\nEnter the value to search :");
	scanf("%d",&num.value);

	searchBackward(list1,num);
	searchForward(list1,num);

	while(list1->head!=NULL)
	{
		removeData(list1,random(0,10));
		display(list1);
	}

	count = 0;
	printf("Enter 5 integers to insert into stack\n");
	while(count < 5)
	{
		scanf("%d",&num.value);
		push(stack1,num.value);
		count++;
	}
	display(stack1->stack);

	count = 0;

	while(count<5)
	{
		push(stack2,pop(stack1));
	//	printf("%d",pop(stack1));
		count++;
	}
	display(stack2->stack);

	printf("Enter 5 integers to insert into Queue\n");
	count = 0;
	while(count < 5)
	{
		scanf("%d",&num.value);
		enqueue(queue1,num.value);
		count++;
	}
	display(queue1->queue);
	count = 0;

	while(count<5)
	{
		printf("%d\t",dequeue(queue1));
		count++;
	}
//	display(queue2->queue);
	dealloc(list1);
	dealloc(queue1->queue);
	dealloc(queue2->queue);
	dealloc(stack1->stack);
	dealloc(stack2->stack);
	free(list1);
	free(queue1->queue);
	free(queue2->queue);
	free(stack1->stack);
	free(stack2->stack);;
	free(queue1);
	free(queue2);
	free(stack1);
	free(stack2);
}
 
