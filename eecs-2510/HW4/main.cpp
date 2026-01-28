#include <iostream>

#include "HybridList.h"

using namespace std;

int main()
{
    HybridList l(10);

    cout << l.block_size() << ' ' << l.capacity() << endl;

    for (int i = 0; i < 23; i++)
    {
        l.push_back(i);
    }

    auto l2 = l;
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.pop_back();
    l.pop_back();

    for (int i = 0; i < l.size(); i++)
    {
        cout << l.at(i) << ' ';
    }

    auto curr = l.front();
    
    cout << endl;

    while (curr != nullptr)
    {
        for (int i = 0; i < curr->size(); i++)
        {
            cout << curr->at(i) << ' ';
        }

        cout << endl;
        curr = curr->next;
    }

    cout << "Size: " << l.size() << endl;

    for (int i = 0; i < l2.size(); i++)
    {
        cout << l2.at(i) << ' ';
    }

    curr = l2.front();
    
    cout << endl;

    while (curr != nullptr)
    {
        for (int i = 0; i < curr->size(); i++)
        {
            cout << curr->at(i) << ' ';
        }

        cout << endl;
        curr = curr->next;
    }

    cout << "Size: " << l2.size() << endl;

    return 0;
}