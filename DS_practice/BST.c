#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node *left, *right;
}node;

node* createNode(int value) 
{
    node* nn = (node*)malloc(sizeof(node));
    nn->data = value;
    nn->left = nn->right = NULL;
    return nn;
}

node* insert(node* root, int value) 
{
    if (root == NULL)   return createNode(value);
    if (value < root->data) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    return root;        //think of it as putting all the pieces back together
}

node* findMin(node* nn) 
{
    while (nn->left) nn = nn->left;
    return nn;
}

node* deleteNode(node* root, int val)
{
    if(!root)   return NULL;
    if(val < root->data) root->left = deleteNode(root->left,val);
    else if(val > root->data)    root->right = deleteNode(root->right,val);
    else
    {
        if(!root->left)
        {
            node* temp = root->right;
            free(root);
            return temp;
        }
        else if(!root->right)
        {
            node* temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}








// Function to perform inorder traversal of the BST
void inorderTraversal(node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    node* root = NULL;

    // Insert nodes into the BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Original BST: ");
    inorderTraversal(root);
    printf("\n");

    // Delete a node from the BST
    int keyToDelete = 30;
    root = deleteNode(root, keyToDelete);

    printf("BST after deleting %d: ", keyToDelete);
    inorderTraversal(root);
    printf("\n");

    return 0;
}