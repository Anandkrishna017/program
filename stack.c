#include <stdio.h>
#include <stdlib.h>
struct node
{
int data; 
struct node *next;
};

struct node *top, *ptr;
void display()
{
printf("the stack is now ");
for(ptr = top; ptr != NULL; ptr = ptr->next)
printf("%d ", ptr -> data);
printf(" NULL\n");
}

void push()
{
struct node *new_node=(struct node*)malloc(sizeof(struct node));

if(new_node == NULL)
printf("over flow\n");
else
{
printf("enter the value to insert: ");
scanf("%d", &new_node -> data);
new_node -> next = top;
top = new_node;
}

display();

}

void pop()
{
if(top == NULL)
printf("Under flow\n");
else
{
ptr = top;
top = top -> next;
free(ptr);
}

display();

}

void search(int x)
{
int i;
for(ptr = top,i = 1; ptr!= NULL; ptr = ptr -> next, i++)
{
if(x==ptr->data)
{
printf("Found at position %d\n",i);
return;
}
}
printf("Not Found\n");
}


void main()
{
int choice,ele;
top  = NULL;
do 
{
printf("1.Insert 2.Delete 3.Search\n");
scanf("%d", &choice);
switch(choice)
{
case 1: push();
	break;
case 2: pop();
	break;
case 3: printf("enter element: ");
	scanf("%d", &ele);
	search(ele);
	break;
}
}
while(choice >=1 && choice <= 3);
}
