#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <chrono>
#include "RedBlackTree.h"
#include "AVLTree.h"

using namespace std;

void insert_and_sort(std::vector<double>& vec, double value)
{
    if (vec.empty())
    {
        vec.push_back(value);
        return;
    }
    if (value < vec.at(0))
    {
        vec.insert(vec.begin(), value);
        return;
    }
    for (int i = 0; i < vec.size() - 1; i++)
    {
        if (value >= vec.at(i) && value <= vec.at(i + 1))
        {
            vec.insert(vec.begin() + i + 1, value);
            return;
        }
    }
    vec.insert(vec.end(), value);
}

int main() {
    srand(time(0));

    int power;

    cin >> power;

    AVLTree avl;
    RedBlackTree rb;

    std::vector<double> doubles;

    for (int i = 0; i < pow(10, power); i++)
    {
        double random_double = ( (double)rand() / RAND_MAX );
        insert_and_sort(doubles, random_double);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < pow(10, power); i++)
    {
        double random_double = ( (double)rand() / RAND_MAX );
        avl.insert(new Node(doubles.at(i)));
    }
    auto end = std::chrono::high_resolution_clock::now();

    cout << "avl time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << endl;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < pow(10, power); i++)
    {
        double random_double = ( (double)rand() / RAND_MAX );
        rb.insert(new RBTNode(doubles.at(i)));
    }
    end = std::chrono::high_resolution_clock::now();

    cout << "rb time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << endl;
    cout << endl;

    cout << "avl: " << avl.getRoot()->height << endl;
    cout << "rb: " << rb.getRoot()->height << endl;

    return 0;
}