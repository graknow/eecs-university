#include "AVLTree.h"
#include <algorithm>
#include <iostream>

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::insert(Node* node)
{
    insertWithoutRebalance(node);

    if (node == root)
    {
        return;
    }

    Node* currNode = node->parent;

    while (currNode->parent != nullptr)
    {
        Node* nextParent = currNode->parent;
        int currBal = getBalanceFactor(currNode);
        int parentBal = getBalanceFactor(currNode->parent);

        if (currBal == 1 && parentBal == 2)
        {
            rotate(nextParent, RIGHT);
            nextParent = nextParent->parent;
        }
        else if (currBal == -1 && parentBal == 2)
        {
            rotate(currNode, LEFT);
            rotate(nextParent, RIGHT);
            nextParent = nextParent->parent;
        }
        else if (currBal == -1 && parentBal == -2)
        {
            rotate(nextParent, LEFT);
            nextParent = nextParent->parent;
        }
        else if (currBal == 1 && parentBal == -2)
        {
            rotate(currNode, RIGHT);
            rotate(nextParent, LEFT);
            nextParent = nextParent->parent;
        }

        currNode = nextParent;
    }
}

void AVLTree::insertWithoutRebalance(Node* node)
{
    if (root == nullptr)
    {
        root = node;
        return;
    }

    Node* currNode = root;

    while (currNode != nullptr)
    {
        if (currNode->key <= node->key)
        {
            if (currNode->right == nullptr)
            {
                currNode->right = node;
                node->parent = currNode;
                break;
            }

            currNode = currNode->right;
        }
        else
        {
            if (currNode->left == nullptr)
            {
                currNode->left = node;
                node->parent = currNode;
                break;
            }

            currNode = currNode->left;
        }
    }

    // error
    if (currNode == nullptr)
    {
        exit(1);
    }

    adjustParentHeights(node);
}

void AVLTree::deleteTree(Node* node) {
    // Recursively remove all nodes in the BST (used by the destructor). 
    // By doing this recursively, we start removing nodes from the bottom
    // of the tree (leaf nodes), which is most efficiently because it does
    // not require replacing any nodes.

    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void AVLTree::adjustParentHeights(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    if (!node->left && !node->right)
    {
        node->height = 0;
    }
    else if (!node->left)
    {
        node->height = node->right->height + 1;
    }
    else if (!node->right)
    {
        node->height = node->left->height + 1;
    }

    while (node->parent != nullptr)
    {
        if (node->parent->height <= node->height)
        {
            node->parent->height = node->height + 1;
        }

        node = node->parent;
    }
}

int AVLTree::getBalanceFactor(Node* node)
{
    return (node->left ? node->left->height : -1 ) - (node->right ? node->right->height : -1);
}

void AVLTree::rotate(Node* node, RotateDirection dir)
{
    Node *newHead, *newLeft, *newRight, *innerChild;

    if (dir == LEFT)
    {
        innerChild = node->right->left;
        newHead = node->right;
        newLeft = node;
        newRight = node->right->right;

        if (node == root)
        {
            root = newHead;
            newHead->parent = nullptr;
        }
        else if (node->parent->left == node)
        {
            node->parent->left = newHead;
            newHead->parent = node->parent;
        }
        else if (node->parent->right == node)
        {
            node->parent->right = newHead;
            newHead->parent = node->parent;
        }

        newHead->right = newRight;
        if (newRight)
        {
            newRight->parent = newHead;
        }

        newHead->left = newLeft;
        if (newLeft)
        {
            newLeft->parent = newHead;
        }

        newLeft->right = innerChild;
        if (innerChild)
        {
            innerChild->parent = newLeft;
        }

        adjustParentHeights(newLeft);
        adjustParentHeights(newRight);

        return;
    }
    // Right rotation
    innerChild = node->left->right;
    newHead = node->left;
    newLeft = node->left->left;
    newRight = node;

    if (node->parent->left == node)
    {
        node->parent->left = newHead;
        newHead->parent = node->parent;
    }
    else
    {
        node->parent->right = newHead;
        newHead->parent = node->parent;
    }

    newHead->right = newRight;
    if (newRight)
    {
        newRight->parent = newHead;
    }

    newHead->left = newLeft;
    if (newLeft)
    {
        newLeft->parent = newHead;
    }

    newRight->left = innerChild;
    if (innerChild)
    {
        innerChild->parent = newRight;
    }

    adjustParentHeights(newLeft);
    adjustParentHeights(newRight);
}