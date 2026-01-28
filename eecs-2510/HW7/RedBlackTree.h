#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

enum RBRotateDirection {
    RBLEFT, RBRIGHT
};

// A node in the red-black tree that stores a double
class RBTNode {
public:
    double key;
    // Whether the node is red (false denotes black)
    bool red = true;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;
    int height = 0;

    RBTNode(double nodeKey) {
        key = nodeKey;
    }
};

// A red-black tree that can only insert
class RedBlackTree
{
public:
    RedBlackTree() {};
    ~RedBlackTree();
	
    // Insert a new element and rebalance the tree
    void insert(RBTNode* node);
    RBTNode* getRoot();

private:
    RBTNode* root = nullptr;
    void deleteTree(RBTNode* node);

    void insertWithoutRebalancing(RBTNode* node);
    void adjustParentHeights(RBTNode* node);

    void rebalance(RBTNode* node);
    void rotate(RBTNode* node, RBRotateDirection dir);
};

#endif // !REDBLACKTREE_H