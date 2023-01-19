#include<stdio.h>
#include<stdlib.h>
struct node{
  int data;
  struct node *left;
  struct node *right;
   }*root=NULL;

struct node *getNode(int val)
{ struct node *newnode;
  newnode=malloc(sizeof(struct node));
  newnode->data=val;
  newnode->left=NULL;
  newnode->right=NULL;
  return newnode;
  }

struct node *insert(struct node *root,int val)
{ if(root==NULL)
   return getNode(val);
  if(root->data<val)
   root->right=insert(root->right,val);
  else
   root->left=insert(root->left,val);
  return root;
  }

int search(struct node *root,int key)
{ while(root!=NULL)
  { if(key==root->data)
      return 1;
    else if(key>root->data)
      root=root->right;
    else
      root=root->left;
    }
  return 0;
  }

struct node *minValueNode(struct node *node)
{ struct node *current=node;
  while(current->left!=NULL)
      current=current->left;
  return current;
  }

struct node *deleteNode(struct node *root,int key)
{ if(root==NULL)
   printf("Empty tree\n");
  if(key<root->data)
    root->left=deleteNode(root->left,key);
  else if(key>root->data)
    root->right=deleteNode(root->right,key);
  else
  { if(root->left==NULL)
    { struct node *temp=root->right;
      free(root);
      return temp;
      }
    else if(root->right==NULL)
    { struct node *temp=root->left;
      free(root);
      return temp;
      }
    else if(root->left==NULL && root->right==NULL)
    { free(root);
      return NULL;
      }
    struct node *temp=minValueNode(root->right);
    root->data=temp->data;
    root->right=deleteNode(root->right,temp->data);
    }
  return root;
  }

void inorder(struct node *root)
{ if(root==NULL)
    return;
  inorder(root->left);
  printf("\n%d",root->data);
  inorder(root->right);
  }

int main()
{ int ch,n,x,item;
  do{
    printf("\n\n1. Insertion \n2. Deletion \n3. Search \n4. Inorder Traversal \n5. Exit");
    printf("\nEnter your choice: ");
    scanf("%d",&ch);
    switch(ch)
    { case 1: printf("Enter the element to be inserted: ");
            scanf("%d",&n);
            root=insert(root,n);
            printf("Element inserted sucessfully.\n");
      break;

      case 2: printf("Enter the number to be deleted.\n");
            scanf("%d",&x);
            root=deleteNode(root,x);
            printf("Element deleted sucessfully.\n");
      break;

      case 3: printf("Enter the element to be searched: ");
            scanf("%d",&item);
            int found=search(root,item);
            if(found==1)
              printf("\n%d found in the tree.\n",item);
            else
              printf("\n%d not found.\n",item);
      break;

      case 4: inorder(root);
      break;

      case 5:
      break;

      default: printf("Wrong input\n");
      break;
       }
      }
    while(ch!=5);
    return 0;
}
