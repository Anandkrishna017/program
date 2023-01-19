#include <stdio.h>
#include <stdlib.h>

struct node
{
int value, no_of_links;
char status;
struct node *link[10];
};

struct node **queue, **stack;
int front = 0, rear = 0, top = 0, no_of_nodes = 0;

struct node *create(int value)
{
int i;
struct node *new_node = (struct node *)malloc(sizeof(struct node));
new_node->status = 0;
new_node->value = value;
for(i = 0; i < 10; i++)
new_node->link[i] = NULL;
new_node->no_of_links = 0;
return new_node;
}
void bfs(struct node *n)
{
int i;
printf("%d ", queue[front]->value);
for(i = 0; n->link[i] != NULL; i++)
{
if(n->link[i]->status == 0)
{
queue[++rear] = n->link[i];
n->link[i]->status = 1;
}
}
front++;
if(front < no_of_nodes)
bfs(queue[front]);
}
void dfs(struct node *n)
{
int i, flag = 0;
if(n->status != 3)
printf("%d ", stack[top]->value);
n->status = 3;
for(i = 0; n->link[i] != NULL; i++)
{
if(n->link[i]->status == 1)
{
stack[++top] = n->link[i];
n->link[i]->status = 2;
flag = 1;
break;
}
}
if(flag == 0)
top--;
        if(top!=-1)
dfs(stack[top]);
}
void main()
{
struct node **nodes;
int i, v;
printf("Enter no. of nodes:\t");
scanf("%d", &no_of_nodes);
nodes = (struct node **)calloc(no_of_nodes, sizeof(struct node *));
queue = (struct node **)calloc(no_of_nodes, sizeof(struct node *));
stack = (struct node **)calloc(no_of_nodes, sizeof(struct node *));

for(i = 0; i < no_of_nodes; i++)
{
printf("Enter value of vertex %d:\t", i);
scanf("%d", &v);
nodes[i] = create(v);
}
for(i = 0; i < no_of_nodes; i++)
{
printf("Enter vertices adjacent to Vertex %d(Enter -1 to go to next):\t", i);
do
{
scanf("%d", &v);
if(v != -1)
nodes[i]->link[nodes[i]->no_of_links++] = nodes[v];
}while(v != -1);
}

printf("\nStarting from Vertex 0 Breadth First Traversal of the Graph is:\n");
queue[0] = nodes[0];
nodes[0]->status = 1;
bfs(queue[0]);
printf("\nStarting from Vertex 0 Depth First Traversal of the Graph is:\n");
stack[0] = nodes[0];
nodes[0]->status = 2;
dfs(stack[0]);
}
