#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node 
{
    char data;
    struct Node* left;
    struct Node* right;
}node;

// Define a stack structure for the tree nodes
typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// Stack functions
StackNode* createStackNode(TreeNode* treeNode) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->treeNode = treeNode;
    node->next = NULL;
    return node;
}

void push(StackNode** top, TreeNode* treeNode) {
    StackNode* newNode = createStackNode(treeNode);
    newNode->next = *top;
    *top = newNode;
}

TreeNode* pop(StackNode** top) {
    if (*top == NULL) {
        return NULL;
    }
    TreeNode* treeNode = (*top)->treeNode;
    StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

// Expression tree functions
TreeNode* createExpressionTree(char postfix[]) {
    StackNode* stack = NULL;

    for (int i = 0; postfix[i] != '\0'; i++) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = postfix[i];
        newNode->left = newNode->right = NULL;

        if (isdigit(postfix[i])) {
            push(&stack, newNode);
        } else {
            newNode->right = pop(&stack);
            newNode->left = pop(&stack);
            push(&stack, newNode);
        }
    }

    return pop(&stack);
}

int evaluateExpressionTree(TreeNode* root) {
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

void freeExpressionTree(TreeNode* root) {
    if (root != NULL) {
        freeExpressionTree(root->left);
        freeExpressionTree(root->right);
        free(root);
    }
}

int main() {
    char postfixExpression[] = "23*5+";
    
    TreeNode* expressionTree = createExpressionTree(postfixExpression);

    if (expressionTree != NULL) {
        printf("Postfix Expression: %s\n", postfixExpression);
        printf("Result: %d\n", evaluateExpressionTree(expressionTree));

        // Free the memory used by the expression tree
        freeExpressionTree(expressionTree);
    } else {
        printf("Failed to create expression tree.\n");
    }

    return 0;
}
