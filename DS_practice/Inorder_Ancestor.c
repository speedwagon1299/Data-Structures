#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *left, *right, *parent;
    int val;
}node;

node* newNode(int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->left = nn->right = nn->parent = NULL;
    nn->val = val;
    return nn;
}

node* insert(node* root, int val)
{
    if(!root)   return newNode(val);
    if(val < root->val)
    {
        root->left = insert(root->left,val);
        root->left->parent = root;
    }
    else
    {
        root->right = insert(root->right,val);
        root->right->parent = root;
    }
    return root;
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

node* deleteNode(node* root, int val)
{
    if(!root)   return NULL;
    node* temp;
    if(val < root->val) root->left = deleteNode(root->left,val);
    else if(val > root->val)    root->right = deleteNode(root->right,val);
    else
    {
        if(!root->left)
        {
            temp = root->right;
            free(root);
            return temp;
        }
        else if(!root->right)
        {
            temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            temp = minVal(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right,temp->val);
        }
    }
}

int printAnc(node* root, int val)
{
    if(!root)   return 0;
    if(root->val == val)    return 1;
    if(printAnc(root->left,val)|| printAnc(root->right,val))
    {
        printf("%d ",root->val);
    }
}

int main()
{
    node* root = NULL, *temp, *succ, *pred;
    root = insert(root,20);
    root = insert(root,8);
    root = insert(root,22);
    root = insert(root,4);
    root = insert(root,12);
    root = insert(root,10);
    root = insert(root,14);
    temp = root->left->right->left;
    succ = insucc(temp);
    pred = inpred(temp);
    if(succ)    printf("\nInorder Succ of %d: %d",temp->val, succ->val);
    if(pred)    printf("\nInorder Pred of %d: %d",temp->val, pred->val);
    printf("\nAncestors of %d are: ",temp->val);
    printAnc(root,temp->val);
}