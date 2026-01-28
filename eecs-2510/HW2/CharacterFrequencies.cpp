#include "CharacterFrequencies.h"

CharacterFrequencies::CharacterFrequencies()
{
}

CharacterFrequencies::CharacterFrequencies(string line)
{
    readString(line);
}

void CharacterFrequencies::readString(string line)
{
    for (int i = 0; i < line.length(); i++)
    {
        int j;

        for (j = 0; j < frequencies.size(); j++)
        {
            if (frequencies[j].first == line[i])
            {
                frequencies[j].second++;
                break;
            }
        }

        if (j == frequencies.size())
        {
            frequencies.push_back(make_pair(line[i], 1));
        }
    }
}

// Reset all character frequencies to 0
void CharacterFrequencies::reset()
{
    for (int i = 0; i < frequencies.size(); i++)
    {
        frequencies[i].second = 0;
    }
}

// Return the frequency of character c
int CharacterFrequencies::getFrequency(char c)
{
    for (int i = 0; i < frequencies.size(); i++)
    {
        if (frequencies[i].first == c)
        {
            return frequencies[i].second;
        }
    }

    return 0;
}

// Print the frequencies of all characters with non-zero frequencies to
// the console in the following format:
// r: 4
// o: 8
// w: 2
// n: 2
// Do not print a line for any element that has 0 frequency!
void CharacterFrequencies::printFrequencies()
{
    for (int i = 0; i < frequencies.size(); i++)
    {
        if (frequencies[i].second != 0)
        {
            cout << frequencies[i].first << ": " << frequencies[i].second << '\n';
        }
    }
}

int main()
{
    string line2 = "Twinkle twinkle little star, how I wonder what you are.";
    cout << line2 << endl;
    CharacterFrequencies line2CharFreq(line2);
    line2CharFreq.printFrequencies();
    line2CharFreq.readString(line2);
    line2CharFreq.printFrequencies();
}