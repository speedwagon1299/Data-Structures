#include <stdio.h>
#include <stdlib.h>
#define MAX 15

typedef struct Node
{
    int val;
    struct Node* right;
    struct Node* left;
}node;

typedef struct 
{
    node* head;
}Tree;

typedef struct StackNode
{
    node* nn;
    struct StackNode* next;
}StackNode;

typedef struct
{
    StackNode* head;
    int top;
}STACK;

typedef struct QueueNode
{
    node* nn;
    struct QueueNode* next;
}QueueNode;

typedef struct
{
    QueueNode *rear,*front;
}QUEUE;


void initStack(STACK* p)
{
    p->top = -1;
    p->head = (StackNode*) malloc(sizeof(StackNode));
    p->head->next = NULL;
}

StackNode* insert(StackNode* prev, node* nn)
{
    StackNode* temp = (StackNode*) malloc(sizeof(StackNode));
    temp->nn = nn;
    temp->next = prev->next;
    prev->next = temp;
    return temp;
}

void push(STACK* p, node* nn)
{
    if(p->top == MAX - 1)
    {
        printf("Stack Overflow");
        return;
    }
    p->top++;
    insert(p->head, nn);
}

int isEmpty(STACK* p)
{
    return p->top == -1;
}

node* top(STACK* p)
{
    return p->head->next->nn;
}

void pop(STACK* p)
{
    if(p->top == -1)
    {
        printf("Stack Underflow");
        return;
    }
    p->top--;
    StackNode* temp = p->head->next;
    p->head->next = temp->next;
    free(temp);
}

void initQueue(QUEUE* p)
{
    p->rear = (QueueNode*) malloc(sizeof(QueueNode));
    p->front = (QueueNode*) malloc(sizeof(QueueNode));
    p->rear->nn = (node*) malloc(sizeof(node));
    p->front->nn = (node*) malloc(sizeof(node));
    p->rear->nn->val = p->front->nn->val = -1;
    p->front->next = p->rear->next = NULL;
}

QueueNode* insertQ(QueueNode* prev, node* nn)
{
    QueueNode* temp = (QueueNode*) malloc(sizeof(QueueNode));
    temp->next = prev->next;
    prev->next = temp;
    temp->nn = nn;
    return temp;
}

void enqueue(QUEUE* p, node* nn)
{
    if(p->rear->nn->val == MAX - 1)
    {
        printf("Queue Overflow");
        return;
    }
    if(p->rear->nn->val == p->front->nn->val)
    {
        p->front->next = insertQ(p->rear,nn);
        p->rear->nn->val++; 
        return;
    }
    p->rear->next = insertQ(p->rear->next,nn);
    p->rear->nn->val++;
}

node* qtop(QUEUE* p)
{
    return p->front->next->nn;
}

void dequeue(QUEUE* p)
{
    if(p->rear->nn->val == p->front->nn->val)
    {
        printf("Queue Underflow");
        return;
    }
    QueueNode* temp = p->front->next;
    p->front->next = temp->next;
    free(temp);
    p->front->nn->val++;
}


void initTree(Tree* t)
{
    t->head = NULL;
}

node* create(int val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->left = nn->right = NULL;
    nn->val = val;
    return nn;
}

void preorder(Tree* t)
{
    node* root = t->head;
    if(!root)   return;
    STACK* p = (STACK*) malloc(sizeof(STACK));
    initStack(p);
    push(p,root);
    while(!isEmpty(p))
    {
        root = top(p); pop(p);
        printf("%d ",root->val);
        if(root->right) push(p,root->right);
        if(root->left)  push(p,root->left);
    }
    free(p);
}

void inorder(Tree* t)
{
    node* root = t->head;
    if(!root)   return;
    STACK* p = (STACK*) malloc(sizeof(STACK));
    initStack(p);
    do
    {
        while(root)
        {
            push(p,root);
            root = root->left;
        }
        if(isEmpty(p))   break;
        root = top(p);  pop(p);
        printf("%d ",root->val);
        root = root->right;
    }
    while(root || !isEmpty(p));
    free(p);
}

void postorder(Tree* t)
{
    node* root = t->head;
    if(!root) return;
    STACK* p = (STACK*) malloc(sizeof(STACK));
    initStack(p);
    do
    {
        while(root)
        {
            push(p,root);
            root = root->left;
        }
        if(isEmpty(p))  break;
        node* temp = top(p)->right;
        if(temp)    root = temp;
        else
        {
            temp = top(p); pop(p);
            printf("%d ",temp->val);
            while(!isEmpty(p) && top(p)->right == temp)
            {
                temp = top(p); pop(p);
                printf("%d ",temp->val);
            }
        }
    } 
    while(root || !isEmpty(p));
    free(p);
}

void levelorder(Tree* t)
{
    node* root = t->head;
    if(!root)   return;
    QUEUE* p = (QUEUE*) malloc(sizeof(QUEUE));
    initQueue(p);
    enqueue(p,root);
    while(p->rear->nn->val != p->front->nn->val)
    {
        root = qtop(p); dequeue(p);
        printf("%d ",root->val);
        if(root->left)  enqueue(p,root->left);
        if(root->right) enqueue(p,root->right);
    }
}

int search(node* root, int val)
{
    static int found = 0;
    if(root->val == val)    {found = 1; return 0;}
    if(root->left && !found)  search(root->left,val);
    if(root->right && !found) search(root->right,val);
    return found;
}

node* copy(node* root)
{
    if(!root)   return NULL;
    node* temp = create(root->val);
    temp->left = copy(root->left);
    temp->right = copy(root->right);
    return temp;
}

int max(int a, int b) { if(a>b) return a; return b;}

int height(node* root)
{
    if(!root)   return 0;
    return 1 + max(height(root->left),height(root->right));
}

int nodes(node* root)
{
    if(!root)   return 0;
    return 1 + nodes(root->left) + nodes(root->right);
}

int leaves(node* root)
{
    if(!root)   return 0;
    if(!root->left && !root->right) return 1;
    return leaves(root->left) + leaves(root->right);
}

int equal(node* root1, node* root2)
{
    return (!root1 && !root2) || (root1 && root2 && (root1->val == root2->val) && equal(root1->left,root2->left) && equal(root1->right,root2->right));
}

int printAnc(node* root, int val)
{
    if(!root)   return 0;
    if(root->val == val)    return 1;
    if(printAnc(root->left,val)|| printAnc(root->right,val))
    {
        printf("%d ",root->val);
        return 1;
    }
}

int main()
{
    Tree* t = (Tree*) malloc(sizeof(Tree));
    initTree(t);
    t->head = create(5);
    t->head->left = create(3);
    t->head->right = create(8);
    t->head->left->left = create(4);
    // t->head->left->right = create(4);
    t->head->right->left = create(2);
    t->head->right->right = create(9);
    printf("\nPre Order: "); preorder(t);
    printf("\nIn Order: ");   inorder(t);
    printf("\nPost Order: "); postorder(t);
    printf("\nLevel Order: ");  levelorder(t);
    Tree* n = (Tree*) malloc(sizeof(Tree));
    initTree(n);
    n->head = copy(t->head);
    printf("\n");
    printf("\nPresence of element 2: %d",search(n->head,8));
    printf("\nHeight: %d ",height(n->head));
    printf("\nNumber of Nodes: %d ",nodes(n->head));
    printf("\nNumber of Leaves: %d ",leaves(n->head));
    printf("\nEquality: %d",equal(n->head,t->head));
    node* nn = (node*) malloc(sizeof(node));
    nn->val = 10; nn->left = nn->right = NULL;
    n->head->left->right = nn;
    printf("\nNew Equality: %d",equal(n->head,t->head));
    node* temp =  t->head->left->left;
    printf("\nAncestors of %d are: ",temp->val);
    printAnc(t->head,temp->val);
    return 0;
}