#include<stdio.h>
#include<stdlib.h>
struct node
 {
    int key;
    struct node *left, *right;
 }*root=NULL;

struct node* newNode(int item)
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
struct node* insert(struct node* node, int key)
{
    if (node == NULL)
        return newNode(key);
  
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
  
    return node;
}
struct node* minValueNode(struct node* node)
{
    struct node* current = node;
  
    while (current && current->left != NULL)
        current = current->left;
  
    return current;
}
struct node* deleteNode(struct node* root, int key)
{
    // base case
    if (root == NULL){
        printf("Item not found!");
        return root;
    }
    
    else if (key < root->key)
        root->left = deleteNode(root->left, key);
  
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
  
    else {
       
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
  
        struct node* temp = minValueNode(root->right);
  
        root->key = temp->key;
  
       
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
int iterativeSearch(struct node* node, int key)
{
// Traverse untill root reaches to dead end
while (node != NULL)
{
if(key == node->key){
return 1;
} // if the key is found return 1

// pass right subtree as new tree
else if (key > node->key)
node = node->right;

// pass left subtree as new tree
else
node = node->left;
}
return 0;
}

int main(){
int ch,res,elt,item;
printf( "* MENU *");
printf("\n 1.Insertion ");
printf("\n 2.Search ");
printf("\n 3.Deletion ");
printf("\n 4.Inorder Traversal ");
printf("\n 0.Exit");
while(1)
{
    printf("\nEnter the choice : \n");
    scanf("%d", &ch);
    switch(ch){
        case 1:
            printf("\nEnter element to insert: ");
            scanf("%d",&elt);
            root = insert(root,elt);
            printf("%d , inserted! ",elt);
            break;
        case 2:
            printf("Enter the data to be searched:\t");
            scanf("%d",&item);
            res = iterativeSearch(root,item);
            if(res==1){
                printf("\nkey found!\n");
            }
            else{
                printf("\nkey not found!\n");
            }
            break;
        case 3:
             if(root == NULL)
                printf("empty binary search tree! \n");
             else{
               printf("Enter the data to delete:\t");
               scanf("%d",&item);
               root = deleteNode(root, item);
             }
            break;
        case 4:
               if(root == NULL)
                printf("empty binary search tree! \n");
               else{
               printf("Inorder traversal of the given tree \n");
               inorder(root);
               }
              break;
        case 0:
            printf("\nExited!\n");
            exit(0);
            }
        }
}
