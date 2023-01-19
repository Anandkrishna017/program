#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct vertex
{
	char id, colored;
	int distance;
} vertex;

typedef struct edge
{
	vertex *start, *end;
	int weight;
} edge;
//binomial heap is used to satisfy question
typedef struct node
{
	vertex *t;
	int degree;
	struct node *parent, *child, *sibling;
} node;

int num, no;
vertex *vertices, **t;
edge *edges;
node *root = NULL;

node *create(vertex *v)
{
	node *n = (node *)malloc(sizeof(node));
	n->t = v;
	n->degree = 0;
	n->parent = n->child = n->sibling = NULL;
	return n;
}
void link(node *h1, node *h2)
{
	h1->sibling = h2->child;
	h1->parent = h2;
	h2->child = h1;
	h2->degree++;
}
node *ins(node *h1, node *h2)
{
	node *h = NULL;
	if(h2 == NULL)
		return h1;
	h1->sibling = h2;
	h = h1;
	if(h1->degree == h2->degree)
	{
		if(h1->t->distance > h2->t->distance)
		{
			link(h1, h2);
			h = ins(h2, h2->sibling);
		}
		else
		{
			h1->sibling = h2->sibling;
			link(h2, h1);
			h = ins(h1, h1->sibling);
		}
	}
	return h;
}
node *find(node *h, vertex *v)
{
	node *res;
	if(h == NULL)
		return NULL;
	if(h->t == v)
		return h;

	res = find(h->child, v);
	if(res != NULL)
		return res;

	return find(h->sibling, v);
}
//decrease_key is used to maintain property of min heap
void decrease_key(vertex *v, int new_val)
{
	vertex *temp;
	node *x = find(root, v), *p;

	v->distance = new_val;
	for(p = x->parent; p != NULL && x->t->distance < p->t->distance; p = p->parent)
	{
		temp = p->t;
		p->t = x->t;
		x->t = temp;
		x = p;
	}
}
void display(vertex *v)
{
	int i;
	printf("\n%c", v->id);
	for(i = 0; i < num; i++)
	{
		if(vertices[i].colored)
		printf("\t");
		else if(vertices[i].distance == INT_MAX)
		printf("\t%c", 236);
		else
		printf("\t%d", vertices[i].distance);
	}
	v->colored = 1;
}
void output(int n)
{
	vertex *u = t[0], *v;
	int i, index;
	for(i = 0; i < n; i++)
		if(t[i]->distance < u->distance)
			u = t[i];

	if(n == 0)
		return;
	else
		display(u);

	for(i = 0; i < no; i++)
		if(u == edges[i].start)
		{
			v = edges[i].end;
			if(u->distance + edges[i].weight < v->distance)
				decrease_key(v, u->distance + edges[i].weight);
		}

	for(i = 0; i < n; i++)
		if(t[i] == u)
		{
			index = i;
			break;
		}
	for(i = index; i < n-1; i++)
		t[i] = t[i+1];

	output(--n);
}
void main()
{
	int i, v1, v2, w;
	printf("Enter no. of vertices:\t");
	scanf("%d", &num);
	vertices = (vertex *)calloc(num, sizeof(vertex));
	t = (vertex **)calloc(num, sizeof(vertex *));
	edges = (edge *)calloc(num * (num-1), sizeof(edge)); //num x num-1 = max. no. of edges

	printf("Enter vertex representations for vertex 0 to vertex %d\n", num-1);
	printf("example for a graph with 3 vertices:- A B C or a b c or 0 1 2 or 1 2 3 or any other\n");
	printf("Note:- Vertex 0 is considered as source vertex\n");
	for(i = 0; i < num; i++)
	{
		scanf(" %c", &vertices[i].id); //whitespace before %c necessary, otherwise newline or space is read as a new character
		vertices[i].colored = 0;
		vertices[i].distance = INT_MAX;
		t[i] = &vertices[i];
		root = ins(create(t[i]), root);
	}

	printf("Enter edges in following format: src_vertex desc_vertex edge_weight\n");
	printf("Example for an edge with weight 5 connecting vertices 0 and 1: 0 1 5\n");
	printf("Enter -1 to stop\n");
	for(no = 0; v1 != -1; no++)
	{
		printf("Edge %d:\t", no);
		scanf("%d", &v1);
		if(v1 == -1)
			break;
		scanf("%d", &v2);
		scanf("%d", &w);
		edges[no].start = &vertices[v1];
		edges[no].end = &vertices[v2];
		edges[no].weight = w;
	}
	edges = (edge *)realloc(edges, no*sizeof(edge));

	decrease_key(t[0], 0);
	for(i = 0; i < num; i++)
	printf("\t%c", vertices[i].id);
	output(num);
	printf("\n");
}
