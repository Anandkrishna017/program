#include <stdio.h>
#include <stdlib.h>

struct node
{
	int value, children, id;
	struct node *link[10];
};

struct node **nodes, **stack, **reverse;
int top = 0, no_of_nodes = 0, id1 = 0, id2 = 0, *visited;

struct node *create(int value, char c)
{
	int i;
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->value = value;
	for(i = 0; i < 10; i++)
		new_node->link[i] = NULL;
	new_node->children = 0;
	if(c == 0)
		new_node->id = id1++;
	else
		new_node->id = id2++;	
	return new_node;	
}
void dfs_util(int id)
{
	int i;
	printf("%d ", reverse[id]->value);	
	visited[id] = 1;
	
	for(i = 0; i < reverse[id]->children; i++)
		if(visited[reverse[id]->link[i]->id] == 0)
			dfs_util(reverse[id]->link[i]->id);
}
void fill_in_order(int k)
{
	int i;
	visited[k] = 1;
	
	for(i = 0; i < nodes[k]->children; i++)
	{
		if(visited[nodes[k]->link[i]->id] == 0)
			fill_in_order(nodes[k]->link[i]->id);
	}
			
	stack[top++] = nodes[k];		
}
void scc()
{
	int i;
	struct node *vertex = (struct node *)malloc(sizeof(struct node));
	
	for(i = 0; i < no_of_nodes; i++)
		if(visited[i] == 0)
			fill_in_order(i);
	
	for(i = 0; i < no_of_nodes; i++)
		visited[i] = 0;

	while(top != 0)
	{
		vertex = stack[--top];
		if(visited[vertex->id] == 0)
		{
			dfs_util(vertex->id);
			printf("\n");
		}
	}	
}
void main()
{
	int i, v;
	printf("Enter no. of nodes:\t");
	scanf("%d", &no_of_nodes);
	nodes = (struct node **)calloc(no_of_nodes, sizeof(struct node *));
	reverse = (struct node **)calloc(no_of_nodes, sizeof(struct node *));
	stack = (struct node **)calloc(no_of_nodes, sizeof(struct node *));
	visited = (int *)calloc(no_of_nodes, sizeof(int));
	
	for(i = 0; i < no_of_nodes; i++)
	{
		printf("Enter value of vertex %d:\t", i);
		scanf("%d", &v);
		nodes[i] = create(v, 0);
		reverse[i] = create(v, 1);
	}
	for(i = 0; i < no_of_nodes; i++)
	{
		printf("Enter end vertices of edges starting from vertex %d(Enter -1 to go to next):\t", i);
		do
		{
			scanf("%d", &v);
			if(v != -1)
			{
				nodes[i]->link[nodes[i]->children++] = nodes[v];
				reverse[v]->link[reverse[v]->children++] = reverse[i];
			}
		}while(v != -1);
	}
	
	printf("\nStrongly connected components of the given graph are:\n");
	scc();
}
