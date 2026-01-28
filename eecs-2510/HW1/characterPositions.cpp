/*
*   Author: Grant Knowlton
*   Date: 1/24/2025
*
*   Description:
*   Counts the occurrences of a user-specified character
*   and the index of each occurrence.  Then it prints the
*   results to the standard output.
*/

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

    // Only one line expected, no need to loop through file contents.
    getline(characterFS, currentLine);

    for (int i = 0; i < currentLine.length(); i++)
    {
        if (currentLine[i] == searchChar)
        {
            searchCharCnt++;

            searchCharIndices.push_back(i);
        }
    }

    cout << "The number of occurrences of the character " << searchChar << " is " << searchCharCnt << endl;

    // Only print indeces when there are instances of searchChar found.
    if (0 != searchCharCnt)
    {
        cout << "The indices of the character positions are";

        for (int i = 0; i < searchCharIndices.size(); i++)
        {
            cout << " " << searchCharIndices.at(i);
        }

        cout << endl;
    }

    characterFS.close();

    return EXIT_SUCCESS;
}