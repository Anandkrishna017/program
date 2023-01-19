#include <stdio.h>
#include <stdlib.h>

struct node
{
	int value, children, parents;
	struct node *link[10];
};

struct node **nodes;
int no_of_nodes;

struct node *create(int value)
{
	int i;
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->value = value;
	for(i = 0; i < 10; i++)
		new_node->link[i] = NULL;
	new_node->children = 0;
	new_node->parents = 0;	
	return new_node;	
}
void topological(int k)	//l is no of nodes printed
{
	int i, j;
	for(i = 0; i < no_of_nodes; i++)
	{
		if(nodes[i]->parents == 0)
		{
			printf("%d ", nodes[i]->value);
			for(j = 0; j < nodes[i]->children; j++)
				nodes[i]->link[j]->parents--;
			nodes[i]->parents = -1;
			k++;
		}
	}
	if(k < no_of_nodes)
		topological(k);
}
void main()
{
	int i, v;
	printf("Enter no. of nodes:\t");
	scanf("%d", &no_of_nodes);
	nodes = (struct node **)calloc(no_of_nodes, sizeof(struct node *));
	
	for(i = 0; i < no_of_nodes; i++)
	{
		printf("Enter value of vertex %d:\t", i);
		scanf("%d", &v);
		nodes[i] = create(v);
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
				nodes[v]->parents++;
			}
		}while(v != -1);
	}
	
	printf("\nTopological Sorting of the given graph is:\n");
	topological(0);
}
