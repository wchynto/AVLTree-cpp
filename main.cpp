#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;
};

Node *createNode(int key)
{
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
};

int getHeight(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int counter = 1;

Node *insert(Node *root, int key)
{
    printf("Steps: %d\n", counter++);

    if (root == NULL)
    {
        Node *newNode = createNode(key);
        printf("New Node: %d\n", newNode->key);
        return newNode;
    }

    printf("Inserting: %d\n", key);

    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balanceFactor = getBalanceFactor(root);

    printf("Balance Factor: %d\n", balanceFactor);

    if (balanceFactor > 1)
    {
        if (getBalanceFactor(root->left) >= 0)
        {
            return rotateRight(root);
        }
        else
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    if (balanceFactor < -1)
    {
        if (getBalanceFactor(root->right) <= 0)
        {
            return rotateLeft(root);
        }
        else
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}

void printTree(Node *root, string indent, bool last)
{
    if (root != NULL)
    {
        cout << indent;
        if (last)
        {
            cout << "R----";
            indent += " ";
        }
        else
        {
            cout << "L----";
            indent += "| ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main()
{
    Node *root = NULL;

    root = insert(root, 5);
    root = insert(root, 20);
    root = insert(root, 30);

    printTree(root, "", true);

    return 0;
}