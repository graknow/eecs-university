#ifndef AVLTREE_H
#define AVLTREE_H

// A node in the AVL tree that stores a double
class Node {
public:
    double key;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;

    Node(double nodeKey) {
        key = nodeKey;
    }
};

enum RotateDirection
{
    LEFT,
    RIGHT
};

// An AVL tree that can insert with and without rebalancing
class AVLTree
{
public:
    AVLTree() {};
    ~AVLTree();

    // Insert a new element and rebalance the tree
    void insert(Node* node);
    // Insert a new element without rebalancing the tree
    void insertWithoutRebalance(Node* node);

private:
    Node* root = nullptr;
    void deleteTree(Node* node);
    void adjustParentHeights(Node* node);
    int getBalanceFactor(Node* node);
    void rotate(Node* node, RotateDirection dir);
};

#endif // !AVLTREE_H