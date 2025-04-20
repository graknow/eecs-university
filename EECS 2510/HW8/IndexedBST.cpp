#include "IndexedBST.h"
#include <iostream>

Node* IndexedBST::search(double desiredKey) {
    Node* cur = root;
    while (cur != nullptr) {
        // Return the node if the key matches
        if (cur->key == desiredKey) {
            return cur;
        }

        // Navigate to the left if the search key is 
        // less than the node's key.
        else if (desiredKey < cur->key) {
            cur = cur->left;
        }

        // Navigate to the right if the search key is 
        // greater than the node's key.
        else {
            cur = cur->right;
        }
    }

    // The key was not found in the tree.
    return nullptr;
}

void IndexedBST::insert(Node* node) {
    if (!root)
    {
        root = node;
        return;
    }

    Node* currNode = root;

    while (currNode)
    {
        if (currNode->key <= node->key)
        {
            if (!currNode->right)
            {
                currNode->right = node;
                node->parent = currNode;
                break;
            }

            currNode = currNode->right;
        }
        else
        {
            currNode->leftSize++;
            if (!currNode->left)
            {
                currNode->left = node;
                node->parent = currNode;
                break;
            }

            currNode = currNode->left;
        }
    }

    // error
    if (!currNode)
    {
        exit(1);
    }
}

void IndexedBST::decrementIndeces(Node* node) {
    auto succ = node->parent;

    while (succ) {
        if (succ->left == node) {
            succ->leftSize--;
        }

        node = succ;
        succ = node->parent;
    }
}

bool IndexedBST::remove(double key) {
    Node* parent = nullptr;
    auto currentNode = root;
   while (currentNode != nullptr) {
      // Check if currentNode has an equal key
      if (currentNode->key == key) {
         if (!currentNode->left && !currentNode->right) {
            decrementIndeces(currentNode);
            // Remove leaf

            if (!parent) { // Node is root
               root = nullptr;
            }
            else if (parent->left == currentNode) {
               parent->left = nullptr;
            }
            else {
               parent->right = nullptr;
            }
            delete currentNode;
            return true; // Node found and removed
         }
         else if (!currentNode->right) {
            decrementIndeces(currentNode);
            // Remove node with only left child
            
            if (!parent) { // Node is root
               root = currentNode->left;
            }
            else if (parent->left == currentNode) {
               parent->left = currentNode->left;
            }
            else {
               parent->right = currentNode->left;
            }
            delete currentNode;
            return true; // Node found and removed
         }
         else if (!currentNode->left) {
            decrementIndeces(currentNode);
            // Remove node with only right child
            
            if (!parent) { // Node is root
               root = currentNode->right;
            }
            else if (parent->left == currentNode) {
               parent->left = currentNode->right;
            }
            else {
               parent->right = currentNode->right;
            }
            delete currentNode;
            return true; // Node found and removed
         }
         else {
            // Remove node with two children
            
            // Find successor (leftmost child of right subtree)
            auto successor = currentNode->right;
            while (successor->left) {
               successor = successor->left;
            }

            // Copy successor's key to current node
            currentNode->key = successor->key;
            parent = currentNode;

            // Reassign currentNode and key so that loop continues with new key
            currentNode = currentNode->right;
            key = successor->key;
         }
      }
      else if (currentNode->key < key) {
         // Search right
         parent = currentNode;
         currentNode = currentNode->right;
      }
      else {
         // Search left
         parent = currentNode;
         currentNode = currentNode->left;
      }
   }
   return false; // Node not found
}

Node* IndexedBST::at(int index) {
    Node* cur = root;
    while (cur != nullptr) {
        if (index == cur->leftSize)
            return cur;     // Found
        else if (index < cur->leftSize)
            cur = cur->left;    // index is in left subtree
        else {
            // index is in right subtree
            index = index - cur->leftSize - 1;
            cur = cur->right;
        }
    }

    return nullptr;
}
