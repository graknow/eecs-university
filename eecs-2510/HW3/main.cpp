#include <iostream>
#include <cstdio>
#include "BoundedArray.h"

using namespace std;

void print_barray(BoundedArray& b, string name)
{
    cout << "Bounded Array: " << name << '\n';
    cout << "Capacity: " << b.capacity() << '\n';
    cout << "Logical Size: " << b.size() << '\n';
    for (int i = 0; i < b.size(); i++)
    {
        if (0 == i)
        {
            cout << "Elements: " << '\n';
        }

        printf("%7.1f", b[i]);

        if (i % 5 == 4)
        {
            cout << '\n';
        }
    }

    cout << endl;
}

int main()
{
    BoundedArray b1(20, 200);
    BoundedArray b2(0, 200);
    BoundedArray b3(b1);

    for (int i = 0; i < 90; i++)
    {
        b1.push_back(i);
        b2.push_back(i + 0.5);
        b2.push_back(i + 0.75);
    }

    b1[0] = 100;

    print_barray(b2, "First");
    b2.resize(200);
    print_barray(b2, "First");
    
    return 0;
}