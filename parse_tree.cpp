#include <iostream>
#include <string>
using namespace std;

struct Node
{
    char data;
    Node *left, *right;
};

Node* createNode(char data)
{
    Node* node = new Node();
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* buildTree(string expr)
{
    Node* nodes[100];
    char operators[100];
    int n = 0, top = -1;

    for (int i = 0; i < (int)expr.length(); i++)
    {
        char ch = expr[i];

        if (ch == ' ')
            continue;

        if (ch == '(')
        {
            operators[++top] = ch;
        }
        else if (ch == ')')
        {
            while (top >= 0 && operators[top] != '(')
            {
                char op = operators[top--];

                Node* right = nodes[--n];
                Node* left = nodes[--n];

                Node* node = createNode(op);
                node->left = left;
                node->right = right;
                nodes[n++] = node;
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

                Node* right = nodes[--n];
                Node* left = nodes[--n];

                Node* node = createNode(op);
                node->left = left;
                node->right = right;
                nodes[n++] = node;
            }

            operators[++top] = ch;
        }
        else
        {
            nodes[n++] = createNode(ch);
        }
    }

    while (top >= 0)
    {
        char op = operators[top--];

        Node* right = nodes[--n];
        Node* left = nodes[--n];

        Node* node = createNode(op);
        node->left = left;
        node->right = right;
        nodes[n++] = node;
    }

    return n == 1 ? nodes[0] : NULL;
}

void printTree(Node* root, string indent = "", bool last = true)
{
    if (root == NULL)
        return;

    cout << indent;

    if (last)
    {
        cout << "`-- ";
        indent += "    ";
    }
    else
    {
        cout << "|-- ";
        indent += "|   ";
    }

    cout << root->data << endl;

    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
}

int main()
{
    string expr;

    cout << "Enter arithmetic expression: ";
    cin >> expr;

    Node* root = buildTree(expr);

    cout << "\nParse Tree:\n";
    printTree(root);

    return 0;
}
