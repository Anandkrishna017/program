#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
struct node
{
	int val, degree;
	struct node *parent, *child, *sibling;
} *root = NULL;

typedef struct node node;

void print(node *start, node *prev)
{
	node *p;
	if(root == NULL)
	{
		printf("\nHEAP EMPTY\n");
		return;
	}
	if(start == NULL)
	{
		for(p = prev; p != NULL; p=p->parent)
			if(p->sibling != NULL)
				break;
		if(p != NULL && p->sibling != NULL)		
			print(p->sibling->child, p->sibling);
		return;	
	}
	if(start == root)
		printf("The root nodes are:	");
	else
		printf("Child of %d: ", start->parent->val);	
	for(p = start; p != NULL; p=p->sibling)
		printf("(%d , %d)--> ",p->val, p->degree);
	printf("NULL\n");
	print(start->child, start);				
}
void link(node *h1, node *h2)
{
	h1->sibling = h2->child;
	h1->parent = h2;
	h2->child = h1;
	h2->degree++;
}
node *create(int val)
{
	node *n = (node *)malloc(sizeof(node));
	n->val = val;
	n->degree = 0;
	n->parent = n->child = n->sibling = NULL;
	return n;
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
		if(h1->val > h2->val)
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
void revertList(node *h)	
{
	if(h->sibling != NULL)
	{
		revertList(h->sibling);
		h->sibling->sibling = h;
	}
	else
		root = h;
}
node *merge(node *h1, node *h2)
{
	node *a, *b, *c;
	if(h1 == NULL)
		return h2;
	if(h2 == NULL)
		return h1;
		
	a = h1;
	b = h2;
	h1 = (a->degree <= b->degree)? a: b;
	if(h1 == NULL)
		return NULL;
	if(h1 == b)
		b = a;
	a = h1;
	while(b != NULL)
	{
		if(a->sibling == NULL)
		{
			a->sibling = b;
			return h1;
		}
		else if(a->sibling->degree < b->degree)
			a = a->sibling;
		else
		{
			c = b->sibling;
			b->sibling = a->sibling;
			a->sibling = b;
			a = a->sibling;
			b = c;
		}	
	}
	return h1;		
}
node *extractMin(node *h)
{
	int min;
	node *min_node_prev = NULL, *min_node = h, *curr, *prev, *next, *res;
	if(h == NULL)
		return NULL;
	min = h->val;
	//minimum value is present only in root nodes
	for(curr = h; curr->sibling != NULL; curr = curr->sibling)
		if(curr->sibling->val < min)
		{
			min = curr->sibling->val;
			min_node_prev = curr;
			min_node = curr->sibling;
		}
		
	if(min_node_prev == NULL && min_node->sibling == NULL)
		h = NULL;
	else if(min_node_prev == NULL)
		h = min_node->sibling;	
	else
		min_node_prev->sibling = min_node->sibling;
		
	if(min_node->child != NULL)
	{
		revertList(min_node->child);	//root is changed
		min_node->child->sibling = NULL;
	}

	if(h == NULL && root == NULL)
		return NULL;
		
	res = merge(h, root);
	prev = NULL;
	curr = res;
	next = curr->sibling;
	
	while(next != NULL)
	{
		if(curr->degree != next->degree || (next->sibling != NULL && next->sibling->degree == curr->degree))
		{
			prev = curr;
			curr = next;
		}
		else if(curr->val <= next->val)
		{
			curr->sibling = next->sibling;
			link(next, curr);
		}
		else
		{
			if(prev == NULL)
				res = next;
			else
				prev->sibling = next;
			link(curr, next);
			curr = next;		
		}
		next = curr->sibling;
	}
	
	return res;
}
node *find(node *h, int val)
{
	node *res;
	if(h == NULL)
		return NULL;
	if(h->val == val)
		return h;
	
	res = find(h->child, val);
	if(res != NULL)
		return res;
	
	return find(h->sibling, val);			
}
void decrease_key(int val, int new_val)
{
	int temp;
	node *x = find(root, val), *p;
	if(x == NULL)	//return if not present
	{
		printf("Value not present in this heap !");
		return;
	}
		
	x->val = new_val;
	for(p = x->parent; p != NULL && x->val < p->val; p = p->parent)
	{
		temp = p->val;
		p->val = x->val;
		x->val = temp;
		x = p;
	}	
}
node *del(int val)
{
	if(root == NULL)
		return NULL;
	decrease_key(val, INT_MIN);
	return extractMin(root);	
}
void main()
{
	int i, n, data;
	do
	{
		printf("1.Insert\t 2.Delete\t 3.Extract-Min\t 4.Decrease Key (Input any other no. to exit):\t");
		scanf("%d", &i);
		switch(i)
		{
			case 1: printf("Enter no. of values to insert:\t");
					scanf("%d", &n);
					printf("Input %d numbers\n", n);
					for(; n > 0; n--)
					{
						scanf("%d", &data);
						root = ins(create(data), root);
					}
					printf("(Key-Value , Degree)\n");
					print(root, NULL);
					printf("\n");
					break;
			case 2: printf("Enter the data to be deleted:\t");
					scanf("%d", &data);
					root = del(data);
					printf("(Key-Value , Degree)\n");
					print(root, NULL);
					printf("\n");
					break;
			case 3: root = extractMin(root);
					printf("(Key-Value , Degree)\n");
					print(root, NULL);
					printf("\n");
					break;
			case 4: printf("Enter the key to be decreased and its new value respectively:\t");
					scanf("%d", &n);
					scanf("%d", &data);
					decrease_key(n, data);
					printf("(Key-Value , Degree)\n");
					print(root, NULL);
					printf("\n");
					break;		
			default: exit(0);				
		}
	} while(i >= 1 && i <= 4);	
}
