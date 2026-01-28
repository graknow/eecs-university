// disjointSetForest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <random>
#include <time.h>

class Node {
    public:
        int value = 0;
        int rank = 0;
        Node* parent = nullptr;
        Node(int value) { this->value = value; }
    };
    
    // Create a set given a single element
    void makeSet(Node* element);
    // Return root for set given an element, using path compression if
    // pathCompression is true
    Node* findSet(Node* element, bool pathCompression);
    // Take the union of two sets given an element from each set. Both union by
    // rank and path compression heuristics can be used or not used.
    void unionSet(Node* element1, Node* element2, bool unionByRank,
        bool pathCompression);
    
    void printAllElements(std::vector<Node*> elements);

    void worstCase(bool unionByRank, bool pathCompression) {
        for (int i = 2; i <= 4; i++)
        {
            std::vector<Node*> elements(pow(10, i));
            for (int j = 0; j < elements.size(); j++) {
                elements.at(j) = new Node(j);
                makeSet(elements.at(j));
            }

            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < elements.size() - 1; j++) {
                unionSet(elements.at(j), elements.at(j + 1), unionByRank, pathCompression);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();

            std::cout << "End union with exponent " << i << " after (micros) " << duration << std::endl;
        }
    }

    void averageCase(bool unionByRank, bool pathCompression) {
        srand(time(0));

        for (int i = 3; i <= 6; i++)
        {
            std::vector<Node*> elements(pow(10, i));
            for (int j = 0; j < elements.size(); j++) {
                elements.at(j) = new Node(j);
                makeSet(elements.at(j));
            }

            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < elements.size() - 1; j++) {
                int index1 = rand() % elements.size();
                int index2 = rand() % elements.size();
                while (index1 == index2) {
                    index2 = rand() % elements.size();
                }
                unionSet(elements.at(index1), elements.at(index2), unionByRank, pathCompression);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();

            std::cout << "End union with exponent " << i << " after (micros) " << duration << std::endl;
        }
    }
    
    int main()
    {
        bool unionByRank = true, pathCompression = true;
    
        // Test for correctness of functionality
        int numElements = 5;
        std::vector<Node*> elements(numElements);
        // Create vector of pointers to elements
        for (int i = 0; i < numElements; i++)
            elements.at(i) = new Node(i);
    
        // Make all singleton sets
        for (int i = 0; i < numElements; i++) {
            makeSet(elements.at(i));
        }
        printAllElements(elements);
    
        // Test a few unions ending up with a single set of all vertices
        unionSet(elements.at(0), elements.at(1), unionByRank, pathCompression);
        printAllElements(elements);
        unionSet(elements.at(0), elements.at(2), unionByRank, pathCompression);
        printAllElements(elements);
        unionSet(elements.at(3), elements.at(4), unionByRank, pathCompression);
        printAllElements(elements);
        unionSet(elements.at(0), elements.at(4), unionByRank, pathCompression);
        printAllElements(elements);

        averageCase(unionByRank, pathCompression);
    
        return 0;
    }
    
    void printAllElements(std::vector<Node*> elements) {
        std::cout << "Element  Parent  Set Representative" << std::endl;
        for (int i = 0; i < elements.size(); i++) {
            // Print element and its set representative (should be same as element)
            std::cout << elements.at(i)->value << "  "
                << elements.at(i)->parent->value << "  "
                << findSet(elements.at(i), false)->value << std::endl;
        }
    }

    void makeSet(Node* node) {
        node->parent = node;
        node->rank = 0;
    }

    Node* findSet(Node* element, bool pathCompression) {
        Node* currNode = nullptr;
        if (element != element->parent) {
            if (pathCompression) {
                element->parent = findSet(element->parent, pathCompression);
            }
            else {
                return findSet(element->parent, pathCompression);
            }
        }
        return element->parent;
    }

    void unionSet(Node* element1, Node* element2, bool unionByRank, bool pathCompression) {
        Node* x = findSet(element1, pathCompression);
        Node* y = findSet(element2, pathCompression);

        if (!unionByRank) {
            x->parent = y;
            return;
        }

        if (x->rank > y->rank) {
            y->parent = x;
        }
        else {
            x->parent = y;
            if (x->rank == y->rank) {
                y->rank++;
            }
        }
    }
    
    // Run program: Ctrl + F5 or Debug > Start Without Debugging menu
    // Debug program: F5 or Debug > Start Debugging menu
    
    // Tips for Getting Started: 
    //   1. Use the Solution Explorer window to add/manage files
    //   2. Use the Team Explorer window to connect to source control
    //   3. Use the Output window to see build output and other messages
    //   4. Use the Error List window to view errors
    //   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
    //   6. In the future, to open this project again, go to File > Open > Project and select the .sln file