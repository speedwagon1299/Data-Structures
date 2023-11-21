#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left, *right, *parent;
    int val;
}node;

node* minValue(node* root)
{
    node* curr = root;
    while(curr->left)   curr = curr->left;
    return curr;
}

node* InorderSucc(node* nn)
{
    if(nn->right)   return minValue(nn->right);
    node* temp = nn->parent;
    while(temp && temp->right == nn)
    {
        nn = temp;
        temp = temp->parent;
    }
    return temp;
}

node* maxVal(node* nn)
{
    node* curr = nn;
    if(curr->right)  curr = curr->right;
    return curr;
}

node* InorderPred(node* nn)
{
    if(nn->left) return maxVal(nn->right);
    node* temp = nn->parent;
    while(temp && temp->left == nn)
    {
        nn = temp;
        temp = temp->parent;
    }
    return temp;
}

node* create(int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->left = nn->right = nn->parent = NULL;
    nn->val = val;
    return nn;
}

node* insert(node* root, int val)
{
    if(!root)   return create(val);
    node* temp;
    if(val < root->val)
    {
        temp = insert(root->left, val);
        root->left = temp;
        temp->parent = root;
    }
    else
    {
        temp = insert(root->right, val);
        root->right = temp;
        temp->parent = root;
    }
    return root;
}

int printAnc(node* root, int val)
{
    if(!root) return 0;
    if(root->val == val)    return 1;
    if(printAnc(root->left,val)||printAnc(root->right,val)) printf("%d ",root->val);
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
    succ = InorderSucc(temp);
    pred = InorderPred(temp);
    if(succ)    printf("\nInorder Succ of %d: %d",temp->val, succ->val);
    if(pred)    printf("\nInorder Pred of %d: %d",temp->val, pred->val);
    printf("\nAncestors of %d are: ",temp->val);
    printAnc(root,temp->val);
}