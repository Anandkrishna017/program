#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct node
{
	int data;
	char color;
	struct node *left, *right, *parent;
} *root = NULL, *temp = NULL, *nil;

typedef struct node node;

void left_rotate(node *x, node *y)
{
	y->right = x->left;
	if(x->left != NULL)
		x->left->parent = y;
	x->parent = y->parent;
	if(y == root)
		root = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;	
	x->left = y;
	y->parent = x;
}
void right_rotate(node *x, node *y)
{
	y->left = x->right;
	if(x->right != NULL)
		x->right->parent = y;
	x->parent = y->parent;
	if(y == root)
		root = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;	
	x->right = y;
	y->parent = x;
}
void fix_color1(node *x)
{
	node *p, *u, *gp;
	p = x->parent;
	gp = p->parent;	
	if(gp == NULL)
		return;
	if(p == gp->left)
			u = gp->right;
		else
			u = gp->left;
	if(u != NULL && u->color == RED)
	{
		p->color = u->color = BLACK;
		gp->color = RED;
		if(gp != root)
			fix_color1(gp);
	}
	else
	{
		gp->color = RED;
		if(x == p->left && p == gp->left)
		{
			p->color = BLACK;
			right_rotate(p, gp);
		}
		else if(x == p->right && p == gp->right)
		{
			p->color = BLACK;
			left_rotate(p, gp);
		}
		else if(x == p->right && p == gp->left)
		{
			x->color = BLACK;
			left_rotate(x, p);
			right_rotate(x, gp);
		}
		else
		{
			x->color = BLACK;
			right_rotate(x, p);
			left_rotate(x, gp);
		}	
	}
}
node *red_child(node *n)
{
	if(n->right != NULL && n->right->color == RED)
		return n->right;
	if(n->left != NULL && n->left->color == RED)
		return n->left;
	return NULL;		
}
node *nil_to_null(node *x, node*p)
{
	if(x != nil)
		return x;	
	if(x == p->left)
		p->left = NULL;	
	else
		p->right = NULL;
	return NULL;	
}
void fix_color2(node *x)
{
	node *s, *p, *r;
	if(x == root)
		return;
	p = x->parent;
	s = (x == p->right)? p->left : p->right;		
	if(x->color == RED)
		x->color = BLACK;
	else if(s == NULL)
	{
		x = nil_to_null(x, p);
		fix_color2(p);
	}
	else if(s->color == RED)
	{
		p->color = RED;
		s->color = BLACK;
		if(s == p->left)
			right_rotate(s, p);
		else
			left_rotate(s, p);
		fix_color2(x);		
	}
	else if(red_child(s) == NULL)
	{
		s->color = RED;
		if(p->color == RED)
			p->color = BLACK;
		else
		{
			x = nil_to_null(x, p);
			fix_color2(p);
		}
	}
	else
	{
		r = red_child(s);
		r->color = BLACK;
		if(p->left == s && s->left == r)
			right_rotate(s, p);
		else if(p->right == s && s->right == r)
			left_rotate(s, p);
		else if(p->left == s && s->right == r)
		{
			s->color = RED;
			left_rotate(s, p);
			fix_color2(x);
		}
		else
		{
			s->color = RED;
			right_rotate(s, p);
			fix_color2(x);
		}
	}
	x = nil_to_null(x, p);
}
node *ins(node *current, node *parent, int val)
{
	if(current == NULL)
	{
		current = (node *)malloc(sizeof(node));
		current->data = val;
		current->color = RED;
		current->left = current->right = NULL;
		current->parent = parent;
		//below statement should be written inside, otherwise it executes even if current != NULL
		if(parent != NULL && parent->color == RED)
			temp = current;
	}
	else if(val < current->data)
		current->left = ins(current->left, current, val);
	else
		current->right = ins(current->right, current, val);
		
	return current;
}
node *largest(node *element)
{
	if(element->right == NULL)
		return element;
	return largest(element->right);	
}
node *del(node *ele, int val)
{
	node *t;
	if(ele == NULL)
		printf("%d is not found in this tree\n", val);
	else if(val < ele->data)
		ele->left = del(ele->left, val);
	else if(val > ele->data)
		ele->right = del(ele->right, val);
	else if(ele->left != NULL && ele->right != NULL)
	{
		t = largest(ele->left);
		ele->data = t->data;
		ele->left = del(ele->left, t->data);
	}	
	else
	{	
		t = ele;
	    if(ele->left == NULL && ele->right == NULL)
	    {
	    	if(ele->color != RED)
	    	{
	    		nil->parent = ele->parent;
	    		ele = nil;
			}
			else
				ele = NULL;
		}
		else if(ele->left == NULL)
		{
			ele->right->parent = ele->parent;
			ele = ele->right;
		}
		else
		{
			ele->left->parent = ele->parent;
			ele = ele->left;
		}	
		temp = ele;
		free(t);
	}
	return ele;		
}
int search(node *element, int val, int level)
{
	if(element == NULL)
		return -1;
	else if(val == element->data)
		return level;
	else if(val < element->data)
		return search(element->left, val, level+1);
	else
		return search(element->right, val, level+1);		
}
void inorder(node *element)
{
	if(element == NULL)
		return;
	inorder(element->left);
	printf("%d ", element->data);
	inorder(element->right);
}
int height(node *n, int i)
{
	int lh, rh;
	if(n == NULL)
		return i;
	lh = height(n->left, i + 1);
	rh = height(n->right, i + 1);
	if(lh > rh)
		return lh;
	else
		return rh;		
}
void levelorderhelper(node *element, int current_level, int traversing_level)
{
	char *c[2] = {"RED", "BLACK"};
	if(element == NULL)
		return;
	if(current_level == traversing_level)
	{
		printf("%d", element->data);
		if(element != root)
		{
			if(element == element->parent->left)
				printf("(%s)[left of %d]\t", c[element->color], element->parent->data);
			else
				printf("(%s)[right of %d]\t", c[element->color], element->parent->data);		
		}
		else
			printf("(BLACK)");
		return;
	}
	levelorderhelper(element->left, current_level + 1, traversing_level);
	levelorderhelper(element->right, current_level + 1, traversing_level);	
}
void levelorder(node *element)
{
	int i;
	for(i = 0; i < height(root, 0); i++)
	{
		printf("level %d: ", i);
		levelorderhelper(root, 0, i);
		printf("\n");
	}
}
void main()
{
	int i, n, data;
	nil = (node *)malloc(sizeof(node));
	nil->color = BLACK;
	nil->left = nil->right = nil->parent = NULL;
	do
	{
		printf("1.Insert\t 2.Delete\t 3.Search\t (Input any other no. to exit):\t");
		scanf("%d", &i);
		switch(i)
		{
			case 1: printf("Enter no. of nodes to insert:\t");
					scanf("%d", &n);
					printf("Input %d numbers\n", n);
					for(; n > 0; n--)
					{
						scanf("%d", &data);
						root = ins(root, NULL, data);
						if(temp != NULL)
							fix_color1(temp);
						temp = NULL;	
						root->color = BLACK;
					}
					printf("Inorder traversal of tree now is:\t");
					inorder(root);
					printf("\nLevelorder traversal of tree now is:\n");
					levelorder(root);
					printf("\n");
					break;
			case 2: printf("Enter the data to be deleted:\t");
					scanf("%d", &data);
					root = del(root, data);
					if(temp != NULL)
						fix_color2(temp);	
					temp = NULL;
					if(root == nil)
						root = NULL;	
					printf("Inorder traversal of tree now is:\t");
					inorder(root);
					printf("\nLevelorder traversal of tree now is:\n");
					levelorder(root);
					printf("\n");
					break;
			case 3: printf("Enter the number to search:\t");
					scanf("%d", &data);
					n = search(root, data, 0);
					if(n == -1)
						printf("%d is not found in this tree\n", data);
					else
						printf("%d is found in this tree at level %d\n", data, n);
					break;
			default: exit(0);				
		}
	} while(i >= 1 && i <= 3);
}
