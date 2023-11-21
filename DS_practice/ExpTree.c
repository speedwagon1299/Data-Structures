#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node 
{
    char data;
    struct Node* left;
    struct Node* right;
}node;

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

STACK* initStack()
{
    STACK* p = (STACK*) malloc(sizeof(STACK));
    p->head = (StackNode*) malloc(sizeof(StackNode));
    p->head->next = NULL; p->head->nn = NULL;
    p->top = -1;
    return p;
}

StackNode* insert(StackNode* prev, node* nn)
{
    StackNode* temp = (StackNode*) malloc(sizeof(StackNode));
    temp->next = prev->next;
    prev->next = temp;
    temp->nn = nn;
    return temp;
}

void push(STACK* p, node* nn)
{
    if(p->top == 14)
    {
        printf("Stack Overflow");
        return;
    }
    insert(p->head,nn);
    p->top++;
}

node* top(STACK* p)
{
    return p->head->next->nn;
}

node* pop(STACK* p)
{
    if(p->top == -1)
    {
        printf("Stack Underflow");
        return NULL;
    }
    p->top--;
    StackNode* temp = p->head->next;
    p->head->next = temp->next;
    return temp->nn;
}

node* create(char val)
{
    node* nn = (node*) malloc(sizeof(node));
    nn->left = nn->right = NULL;
    nn->data = val;
}

node* createExpressionTree(char* postfix) 
{
    STACK* p = initStack();
    for(int i = 0; postfix[i] != '\0'; i++) 
    {
        node* nn = create(postfix[i]);
        if (isdigit(postfix[i])) 
        {
            push(p,nn);
        } 
        else 
        {
            nn->right = pop(p);
            nn->left = pop(p);
            push(p, nn);
        }
    }
    return pop(p);
}

int evaluateExpressionTree(node* root) {
    if (root == NULL) {
        return 0;
    }

    if (isdigit(root->data)) {
        return root->data - '0';
    }

    int leftValue = evaluateExpressionTree(root->left);
    int rightValue = evaluateExpressionTree(root->right);

    switch (root->data) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return leftValue / rightValue;
        default: return 0; // Handle invalid operators as needed
    }
}

void freeExpressionTree(node* root) {
    if (root != NULL) {
        freeExpressionTree(root->left);
        freeExpressionTree(root->right);
        free(root);
    }
}

int main() {
    char postfixExpression[] = "23*5+6-";
    
    node* root = createExpressionTree(postfixExpression);

    if (root!= NULL) {
        printf("Postfix Expression: %s\n", postfixExpression);
        printf("Result: %d\n", evaluateExpressionTree(root));

        // Free the memory used by the expression tree
        freeExpressionTree(root);
    } else {
        printf("Failed to create expression tree.\n");
    }

    return 0;
}
