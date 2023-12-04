#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int val;
}node;

typedef struct
{
    node* head;
}Tree;

node* newNode(int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->left = nn->right = NULL;
    nn->val = val;
    return nn;
}

void preorder(node* root)
{
    if(!root)   return;
    printf("%d ",root->val);
    preorder(root->left);
    preorder(root->right);
}

void insertBT(node* head, char* str, int val)
{
    node* root = head;
    int flag = 0;
    for(int i = 0; i < strlen(str)-1; i++)
    {
        if(str[i] == 'L')
        {
            root = root->left;
        }
        else    
        {
            root = root->right;
        }
        if(!root)   { flag = 1; break;}
    }
    if(flag)   
    {
        printf("\nInvalid Location\n");
        return;
    }
    if(str[strlen(str)-1] == 'L')
    {
        if(root->left)
        {
            printf("\nInvalid Location\n");
            return;
        }
        root->left = newNode(val);
        root->left->parent = root;
    }
    else  
    {
        if(root->right)
        {
            printf("\nInvalid Location\n");
            return;
        }
        root->right = newNode(val);
        root->right->parent = root;
    }
}

node* maxVal(node* root)
{
    if(root->right)    root = root->right;
    return root;
}
node* minVal(node* root)
{
    if(root->left)  root = root->left;
    return root;
}

node* insucc(node* root)
{
    if(root->right) return minVal(root->right);
    node* temp = root->parent;
    while(temp && temp->right == root)
    {
        root = temp;
        temp = temp->parent;
    }
    return temp;
}

node* inpred(node* root)
{
    if(root->left)  return maxVal(root->left);
    node* temp = root->parent;
    while(temp && temp->left == root)
    {
        root = temp;
        temp = temp->parent;
    }
    return temp;
}

int main()
{
    int ch;
    Tree* t = (Tree*) malloc(sizeof(Tree));
    printf("\nEnter value of head node: ");
    scanf("%d",&ch);
    t->head = newNode(ch);
    do
    {
        printf("\n\nEnter the String (L and R): ");
        char* str = (char*) malloc(30*sizeof(char));
        scanf("%s",str);
        printf("\nEnter the value: ");
        int val;
        scanf("%d",&val);
        insertBT(t->head,str,val);
        printf("\nEnter 0 to exit: ");
        scanf("%d",&ch);
    }
    while(ch != 0);
    node* temp = t->head->left->right;
    node* succ = insucc(temp);
    node* pred = inpred(temp);
    if(succ)    printf("\nInorder Succ of %d: %d",temp->val, succ->val);
    if(pred)    printf("\nInorder Pred of %d: %d",temp->val, pred->val);
    printf("\nPreorder: ");
    preorder(t->head);
}