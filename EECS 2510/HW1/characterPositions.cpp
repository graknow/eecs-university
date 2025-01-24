#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream characterFS;

    characterFS.open("input.txt");

    if (!characterFS.is_open())
    {
        cout << "The input file input.txt could not be opened." << endl;
        return EXIT_FAILURE;
    }

    char searchChar;
    int searchCharCnt = 0;
    string currentLine;
    vector<int> searchCharIndices;

    cout << "Enter the character to search for: ";
    cin >> searchChar;

    getline(characterFS, currentLine);

    while (!characterFS.fail())
    {
        characterFS >> currentLine;

        for (int i = 0; i < currentLine.length(); i++)
        {
            if (currentLine[i] == searchChar)
            {
                searchCharCnt++;

                searchCharIndices.push_back(i);
            }
        }
    }

    cout << "The number of occurrences of the character " << searchChar << " is " << searchCharCnt << endl;

    if (0 != searchCharCnt)
    {
        cout << "The indices of the character positions are";

        for (int i = 0; i < searchCharIndices.size(); i++)
        {
            cout << " " << searchCharIndices.at(i);
        }

        cout << endl;
    }

    return 0;
}