#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct Node
{
    string value;
    Node* left;
    Node* right;

    Node(string val)
    {
        value = val;
        left = right = nullptr;
    }
};

string expr;
int pos = 0;

Node* expression();
Node* term();
Node* factor();

Node* expression()
{
    Node* node = term();

    while (pos < (int)expr.length() &&
           (expr[pos] == '+' || expr[pos] == '-'))
    {
        char op = expr[pos++];
        Node* newNode = new Node(string(1, op));
        newNode->left = node;
        newNode->right = term();
        node = newNode;
    }

    return node;
}

Node* term()
{
    Node* node = factor();

    while (pos < (int)expr.length() &&
           (expr[pos] == '*' || expr[pos] == '/'))
    {
        char op = expr[pos++];
        Node* newNode = new Node(string(1, op));
        newNode->left = node;
        newNode->right = factor();
        node = newNode;
    }

    return node;
}

Node* factor()
{
    while (pos < (int)expr.length() &&
           isspace(static_cast<unsigned char>(expr[pos])))
        pos++;

    if (pos >= (int)expr.length())
        return nullptr;

    if (expr[pos] == '(')
    {
        pos++;
        Node* node = expression();

        while (pos < (int)expr.length() &&
               isspace(static_cast<unsigned char>(expr[pos])))
            pos++;

        if (pos < (int)expr.length() && expr[pos] == ')')
            pos++;

        return node;
    }

    if (isalnum(static_cast<unsigned char>(expr[pos])) ||
        expr[pos] == '_')
    {
        string operand;

        while (pos < (int)expr.length() &&
               (isalnum(static_cast<unsigned char>(expr[pos])) ||
                expr[pos] == '_'))
        {
            operand += expr[pos++];
        }

        return new Node(operand);
    }

    return nullptr;
}

void printTree(Node* root, int space = 0)
{
    if (root == nullptr)
        return;

    space += 5;

    printTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->value << endl;

    printTree(root->left, space);
}

int main()
{
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);

    pos = 0;
    Node* root = expression();

    if (root == nullptr || pos != (int)expr.length())
    {
        cout << "Invalid expression or unsupported syntax." << endl;
        return 1;
    }

    cout << "\nParse Tree (sideways):\n";
    printTree(root);

    return 0;
}
