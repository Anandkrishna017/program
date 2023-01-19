#include <stdio.h>
#include <stdlib.h>

struct node{
int data;
struct node *next, *prev;
};

struct node *front = NULL, *rear = NULL, *ptr;
int no_of_nodes = 0;
void display(int i)
{
if(i)
{
printf("the list now from front is : ");
for(ptr = front; ptr!=NULL;ptr=ptr->next)
{
printf("%d\t", ptr->data);
}
}
else
{
printf("the list now from rear is : ");
for(ptr=rear;ptr!=NULL;ptr=ptr->prev)
{
printf("%d\t",ptr->data);
}
printf("\n");
}
}
void ins(int position)
{
int i;
struct node *new_node=(struct node*)malloc(sizeof(struct node));
if(new_node == NULL)
{
printf("OVERFLOW !!!\n");
return;
}
printf("Enter the value to insert :");
scanf("%d", &new_node->data);
for(ptr=front, i=1; i < position; ptr = ptr -> next, i++)
{
if(ptr==NULL)
{
printf("There is only %d elements in this list\n",i);
return;
}
new_node->next = ptr;
new_node->prev = (i!=no_of_nodes+1)?ptr->prev:rear;
if(i!=1)
{
new_node->prev->next = new_node;
}
else
{
front = new_node;
}
if(i!=no_of_nodes+1)
{
new_node->next->prev=new_node;
}
else
{
rear=new_node;
}
no_of_nodes++;
display(1);
}
}
void del(int position)
{
int i;
struct node *temp;
if(front == NULL)
{
printf("UNDERFLOW !!!\n");
return;
}
for(ptr=front,i=1; i < position; ptr =ptr->next, i++)
if(ptr-> next == NULL)
{
printf("there is only %d elements in this list\n",i);
return;
}

temp=ptr;
if(1!=1)
ptr->prev->next = ptr -> next;
else
front = front -> next;
if(i!=no_of_nodes)
ptr->next->prev=ptr->next;
else
front = front -> next;
if(i!=no_of_nodes)
front = front -> next;
if(front != NULL)
front -> prev = rear -> next = NULL;
free(temp);
no_of_nodes--;
display(1);
}
void search(int x)
{
int i;
for(ptr = front, i =1; ptr!=NULL; ptr = ptr -> next, i++)
{
 if(x == ptr->data)
 {
printf("%d is found in this list at position 5 %d\n",x,i);
return;
}
}
printf("%d is not found in this list\n",x);
}
void main()
{
int choice, x;
do {
printf("1.insert at First\n2.Insert at last\n3.Insert b/w nodes\n4.Delete last node\n 6.Delete intermediate node\n7.search\n8.Display from first node\n9.Display from last node\n");
printf("enter your choice: ");
scanf("%d",&choice);
switch(choice)
{
case 1: ins(1); break;
case 2: ins(no_of_nodes+1); break;
case 3: printf("Enter the location: ");
	scanf("%d", &x);
	ins(x);
	 break;
case 4: del(1); break;
case 5: del(no_of_nodes); break;
case 6: printf("Enter the location: ");
	scanf("%d", &x);
	del(x);
	 break;
case 7: printf("Enter the element to be searched: "); 
	scanf("%d", &x);
	search(x);break;
case 8: display(1); break;
case 9: display(0); break;
default: exit(0);
}
}
while(choice >=1 && choice <=9);
}


 
