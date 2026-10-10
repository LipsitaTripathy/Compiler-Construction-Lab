#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    char data;
    struct node *left;
    struct node *right;
} Node;

Node *createNode(char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node *buildTree(char expr[])
{
    Node *nodes[100];
    char operators[100];
    int n = 0, top = -1;
    int i;

    for (i = 0; expr[i] != '\0'; i++)
    {
        char ch = expr[i];

        if (isspace((unsigned char)ch))
            continue;

        if (isalnum((unsigned char)ch))
        {
            nodes[n++] = createNode(ch);
        }
        else if (ch == '(')
        {
            operators[++top] = ch;
        }
        else if (ch == ')')
        {
            while (top >= 0 && operators[top] != '(')
            {
                char op = operators[top--];

                Node *right = nodes[--n];
                Node *left = nodes[--n];
                Node *newNode = createNode(op);

                newNode->left = left;
                newNode->right = right;
                nodes[n++] = newNode;
            }

            if (top >= 0)
                top--;
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/')
        {
            while (top >= 0 && operators[top] != '(' &&
                   ((operators[top] == '*' ||
                     operators[top] == '/') ||
                    ((ch == '+' || ch == '-') &&
                     (operators[top] == '+' ||
                      operators[top] == '-'))))
            {
                char op = operators[top--];

                Node *right = nodes[--n];
                Node *left = nodes[--n];
                Node *newNode = createNode(op);

                newNode->left = left;
                newNode->right = right;
                nodes[n++] = newNode;
            }

            operators[++top] = ch;
        }
    }

    while (top >= 0)
    {
        char op = operators[top--];

        Node *right = nodes[--n];
        Node *left = nodes[--n];
        Node *newNode = createNode(op);

        newNode->left = left;
        newNode->right = right;
        nodes[n++] = newNode;
    }

    return (n == 1) ? nodes[0] : NULL;
}

void printTree(Node *root, int space)
{
    int i;

    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");
    for (i = 5; i < space; i++)
        printf(" ");

    printf("%c\n", root->data);

    printTree(root->left, space);
}

int main()
{
    char expr[100];

    strcpy(expr, "a+b*c");

    printf("Parse Tree for the expression: %s\n", expr);
    printf("\nTree Representation:\n");

    Node *root = buildTree(expr);

    printTree(root, 0);

    printf("\nTherefore, the parse tree correctly represents "
           "the arithmetic expression a+(b*c).\n");

    return 0;
}