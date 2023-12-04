#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
}node;

int search(char* str, int start, int end, char val)
{
    for(int i = start; i <= end; i++)
    {
        if(str[i] == val)   return i;
    }
    return -1;
}

node* create(char val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->data = val;
    nn->left = nn->right = NULL;
    return nn;
}

node* constructTree(char pre[], char post[], int* preInd, int postStart, int postEnd, int size) //pre,post
{
    if(*preInd >= size || postStart > postEnd) return NULL;
    node* nn = (node*) malloc(sizeof(node));
    nn->left = nn->right = NULL;
    nn->data = pre[*preInd];
    (*preInd)++;        //iterate onward through prefix
    if(postStart == postEnd)    return nn;
    
    int postInd = search(post, postStart, postEnd, pre[*preInd]);
    if(postInd != -1)
    {
        nn->left = constructTree(pre,post,preInd,postStart,postInd,size);       //postStart to postInd
        nn->right = constructTree(pre,post,preInd,postInd+1,postEnd-1,size);    //postInd+1 to postEnd-1
    }
    return nn;
}

node* constructTree2(char* pre, char* in, int inStart, int inEnd, int size)
{
    static int preInd = 0;
    if(preInd >= size || inStart > inEnd)   return NULL;
    node* nn = create(pre[preInd++]);  
    if(inStart == inEnd)    return nn;
    int inInd = search(in,inStart,inEnd,nn->data);
    if(inInd != -1)
    {
        nn->left = constructTree2(pre,in,inStart,inInd-1,size);
        nn->right = constructTree2(pre,in,inInd+1,inEnd,size);
    }
    return nn;
}

// node* constructTree3(char* post, char* in, int inStart, int inEnd, int size)
// {
//     static int postInd = 0;
//     if(inStart > inEnd || postInd >= size)
//     return NULL;
//     node* nn = create(post[size - postInd++ - 1]);
//     if(inStart == inEnd)    return nn;
//     int inInd = search(in,inStart,inEnd,nn->data);
//     if(inInd != -1)
//     {
//         nn->left = constructTree3(post,in,inStart,inInd-1,size);
//         nn->right = constructTree3(post,in,inInd+1,inEnd,size);
//     }
//     return nn;
// }

// node* constructTree2(char pre[], char in[], int* preInd, int inStart, int inEnd, int size)  //pre,in
// {
//     if (*preInd >= size || inStart > inEnd) {
//         return NULL;
//     }

//     node* nn = (node*)malloc(sizeof(node));
//     nn->left = nn->right = NULL;
//     nn->data = pre[*preInd];
//     (*preInd)++;        //iterate onward through prefix

//     if (inStart == inEnd) {
//         return nn;
//     }

//     int inInd = search(in, inStart, inEnd, nn->data);

//     if (inInd != -1) {
//         nn->left = constructTree2(pre, in, preInd, inStart, inInd - 1, size);       //inStart to inInd-1
//         nn->right = constructTree2(pre, in, preInd, inInd + 1, inEnd, size);        //inInd+1 to inEnd
//     }

//     return nn;
// }

node* constructTree3(char in[], char post[], int* postInd, int inStart, int inEnd, int size) //In,Post
{
    if (*postInd < 0 || inStart > inEnd) {
        return NULL;
    }

    node* nn = (node*)malloc(sizeof(node));
    nn->left = nn->right = NULL;
    nn->data = post[*postInd];
    (*postInd)--;       //backward interation through postfix

    if (inStart == inEnd) {
        return nn;
    }

    int inInd = search(in, inStart, inEnd, nn->data);

    if (inInd != -1) {
        nn->right = constructTree3(in, post, postInd, inInd + 1, inEnd, size);
        nn->left = constructTree3(in, post, postInd, inStart, inInd - 1, size);
    }

    return nn;
}

void printInorder(node* root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%c ", root->data);
        printInorder(root->right);
    }
}

void freeTree(node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    // char preOrder[] = "ABCD";
    char postOrder[] = "974528631";
    char inOrder[] = "794251368";
    int preIndex = 0;
    // char preOrder2[] = "ABDECF";
    // char inOrder2[] = "DBEAFC";
    // int size = sizeof(preOrder) / sizeof(preOrder[0]);
    int size = sizeof(postOrder) / sizeof(postOrder[0]);
    // node* root = constructTree(preOrder, postOrder, &preIndex, 0, size - 1, size);
    // preIndex = 0;
    // printf("Inorder Traversal of Constructed Tree:\n");
    // printInorder(root);
    // printf("\n");

    // node* root2 = constructTree2(preOrder2, inOrder2, 0, size2 - 1, size2);
    node* root = constructTree3(postOrder, inOrder,&preIndex, 0, size - 1, size);
    printf("Inorder Traversal of Constructed Tree:\n");
    printInorder(root);
    
    // freeTree(root);
    freeTree(root);

    return 0;
}