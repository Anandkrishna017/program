#include <stdio.h>
#include <stdlib.h>
//look MFC
struct disjoint
{
	int vertex, set_rep;
} *sets;

struct edge
{
	int v1, v2, w;
} *edges;

int num, no, sum = 0;

void sort_by_weight()
{
	struct edge e;
	int i, j, min_idx;
	for(i = 0; i < no; i++)	//selection sort of edges by weight
	{
		min_idx = i;
		for(j = i+1; j < no; j++)
			if(edges[j].w < edges[min_idx].w)
				min_idx = j;
				
		e = edges[i];
		edges[i] = edges[min_idx];
		edges[min_idx] = e;		
	}
}
void output()
{
	int i, vj, vk;
	for(i = 0; i < no; i++)
	{
		vj = edges[i].v1;	//vj is sets[vj].vertex
		vk = edges[i].v2;	//vk is sets[vk].vertex
		if(sets[vj].set_rep != sets[vk].set_rep)
		{
			if(sets[vj].set_rep < sets[vk].set_rep)	//union operation
			{
				printf("%d - %d \t %d\n", vj, vk, edges[i].w);
				sets[vk].set_rep = sets[vj].set_rep;
			}
			else
			{
				printf("%d - %d \t %d\n", vk, vj, edges[i].w);
				sets[vj].set_rep = sets[vk].set_rep;
			}
			sum += edges[i].w;
			num--;
			break;		
		}
	}
	if(num == 1) //num-1 edges to be printed
		return;
	output();
}
void main()
{
	int i, v1, v2, w;
	printf("Enter no. of vertices:\t");
	scanf("%d", &num);
	sets = (struct disjoint *)calloc(num, sizeof(struct disjoint));
	edges = (struct edge *)calloc(num * (num-1), sizeof(struct edge));	//num x num-1 = max. no. of edges
	for(i = 0; i < num; i++)
		sets[i].set_rep = sets[i].vertex = i;
	
	printf("Enter edges in following format: src_vertex desc_vertex edge_weight\n");
	printf("Example for an edge with weight 5 connecting vertices 0 and 1: 0 1 5\n");
	printf("Enter -1 to stop\n");
	no = 0;
	do
	{
		printf("Edge %d:\t", no);
		scanf("%d", &v1);
		if(v1 == -1)
			break;
		scanf("%d", &v2);
		scanf("%d", &w);
		edges[no].v1 = v1;
		edges[no].v2 = v2;
		edges[no].w = w;
		no++;
	} while(v1 != -1);
	edges = (struct edge *)realloc(edges, no*sizeof(struct edge));
	
	sort_by_weight();
	printf("Edges\tWeight\n");
	output();
	printf("Minimum Cost Spanning Tree: %d", sum);
}
