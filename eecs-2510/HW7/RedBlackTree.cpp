#include "RedBlackTree.h"
#include <algorithm>

#define MAX(a, b) ((a) < (b) ? a : b)

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

RBTNode* RedBlackTree::getRoot() {
    return root;
}

void RedBlackTree::deleteTree(RBTNode* node) {
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

void RedBlackTree::insert(RBTNode* node) {
    insertWithoutRebalancing(node);
    node->red = true;

    adjustParentHeights(node);

    rebalance(node);
}

void RedBlackTree::adjustParentHeights(RBTNode* node)
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
    else
    {
        node->height = MAX(node->left->height, node->right->height) + 1;
    }

    while (node->parent)
    {
        if (node->parent->height <= node->height)
        {
            node->parent->height = node->height + 1;
        }

        node = node->parent;
    }
}

void RedBlackTree::rebalance(RBTNode* node) {
    if (!node->parent) {
        node->red = false;
        return;
    }

    if (!node->parent->red) return;

    RBTNode* parent = node->parent;
    RBTNode* grandparent = node->parent ? node->parent->parent : nullptr;
    RBTNode* uncle = !grandparent ? nullptr 
        : grandparent->left == node->parent ? grandparent->right 
        : grandparent->left;
    
    if (uncle && uncle->red) {
        parent->red = uncle->red = false;
        grandparent->red = true;
        rebalance(grandparent);
        return;
    }
    if (node == parent->right && parent == grandparent->left) {
        rotate(parent, RBLEFT);
        node = parent;
        parent = node->parent;
    }
    else if (node == parent->left && parent == grandparent->right) {
        rotate(parent, RBRIGHT);
        node = parent;
        parent = node->parent;
    }

    parent->red = false;
    grandparent->red = true;
    if (node == parent->left)
        rotate(grandparent, RBRIGHT);
    else
        rotate(grandparent, RBLEFT);
}

void RedBlackTree::rotate(RBTNode* node, RBRotateDirection dir) {
    RBTNode *newHead, *newLeft, *newRight, *innerChild;

    if (dir == RBLEFT)
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

    newRight->left = innerChild;
    if (innerChild)
    {
        innerChild->parent = newRight;
    }

    adjustParentHeights(newLeft);
    adjustParentHeights(newRight);
}

void RedBlackTree::insertWithoutRebalancing(RBTNode* node) {
    if (!root) {
        root = node;
        return;
    }

    RBTNode* currNode = root;

    while (currNode) {
        if (node->key <= currNode->key) {
            if (!currNode->left) {
                currNode->left = node;
                node->parent = currNode;
                return;
            }
            currNode = currNode->left;
        }
        else if (node->key > currNode->key) {
            if (!currNode->right) {
                currNode->right = node;
                node->parent = currNode;
                return;
            }
            currNode = currNode->right;
        }
    }
}