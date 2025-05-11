#pragma once

#include <iostream>

using namespace std;

template <typename T>
class AVLTree
{
private:
    struct Node
    {
        T value;
        Node* left;
        Node* right;
        int height;

        Node(T val)
        {
            value = val;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node* root;
    int nodeCount;

    int getHeight(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return node->height;
    }

    int getBalance(Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return x;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, T value)
    {
        if (node == nullptr)
        {
            nodeCount++;

            return new Node(value);
        }

        if (value < node->value)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = insert(node->right, value);
        }
        else
        {
            return node;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
        {
            return rotateRight(node);
        }

        if (balance < -1 && value > node->right->value)
        {
            return rotateLeft(node);
        }

        if (balance > 1 && value > node->left->value)
        {
            node->left = rotateLeft(node->left);

            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->value)
        {
            node->right = rotateRight(node->right);

            return rotateLeft(node);
        }

        return node;
    }

    Node* findMin(Node* node)
    {
        if (node->left == nullptr)
        {
            return node;
        }

        return findMin(node->left);
    }


    Node* remove(Node* node, T value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (value < node->value)
        {
            node->left = remove(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = remove(node->right, value);
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                Node* temp;

                if (node->left != nullptr)
                {
                    temp = node->left;
                }
                else
                {
                    temp = node->right;
                }

                delete node;

                nodeCount--;

                return temp;
            }
            else
            {
                Node* successor = findMin(node->right);
                node->value = successor->value;
                node->right = remove(node->right, successor->value);
            }
        }

        if (node == nullptr)
        {
            return nullptr;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
        {
            return rotateRight(node);
        }

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);

            return rotateRight(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
        {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);

            return rotateLeft(node);
        }

        return node;
    }

    Node* find(Node* node, T value)
    {
        if (node == nullptr || node->value == value)
        {
            return node;
        }

        if (value < node->value)
        {
            return find(node->left, value);
        }
        else
        {
            return find(node->right, value);
        }
    }

    void printInOrder(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        printInOrder(node->left);

        cout << node->value << " ";

        printInOrder(node->right);
    }

public:
    AVLTree()
    {
        root = nullptr;
        nodeCount = 0;
    }

    void insert(T value)
    {
        root = insert(root, value);
    }

    void remove(T value)
    {
        root = remove(root, value);
    }

    Node* find(T value)
    {
        return find(root, value);
    }

    int size()
    {
        return nodeCount;
    }

    void print()
    {
        printInOrder(root);

        cout << endl;
    }
};