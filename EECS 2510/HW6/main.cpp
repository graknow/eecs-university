#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include "AVLTree.h"

using namespace std;

int main()
{
    vector<int> balance_heights;
    vector<int> no_balance_heights;

    srand(time(0));

    int power;

    cin >> power;

    for (int j = 0; j < 10; j++)
    {
        AVLTree balance;
    AVLTree no_balance;

    for (int i = 0; i < pow(10, power); i++)
    {
        double random_double = ( (double)rand() / RAND_MAX );
        balance.insert(new Node(random_double));
        no_balance.insertWithoutRebalance(new Node(random_double));
    }
    balance_heights.push_back(balance.getRoot()->height);
    no_balance_heights.push_back(no_balance.getRoot()->height);
    }

    cout << endl;

    for (auto i: balance_heights)
    {
        cout << " " << i;
    }
    cout << endl;

    for (auto i: no_balance_heights)
    {
        cout << " " << i;
    }
}