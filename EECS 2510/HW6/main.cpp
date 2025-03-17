#include <iostream>
#include "AVLTree.h"

using namespace std;

int main()
{
    // Single rotate left
    AVLTree b;
    Node* bRoot = new Node(2);
    Node* root = new Node(4);
    b.insert(bRoot);
    b.insert(new Node(1));
    b.insert(new Node(3));
    b.insert(root);
    b.insert(new Node(5));
    b.insert(new Node(6));
    cout << endl;
    cout << root->key << endl;
    cout << root->left->key << " " << root->right->key << " " << root->right->right->key << endl;
    cout << root->left->left->key << " " << root->left->right->key << endl;
    // Rotate left then right
    AVLTree c;
    Node* cRoot = new Node(4);
    c.insert(cRoot);
    c.insert(new Node(3));
    c.insert(new Node(5));
    c.insert(new Node(1));
    c.insert(new Node(2));
    cout << cRoot->key << endl;
    cout << cRoot->left->key << " " << cRoot->right->key << endl;
    cout << cRoot->left->left->key << " " << cRoot->left->right->key << endl;
}