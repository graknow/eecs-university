#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

void insertionSort(std::vector<int>& numbers)
{
    for (int i = 1; i < numbers.size(); i++)
    {
        int j = i;

        while (j > 0 && numbers[j] < numbers[j - 1])
        {
            int tmp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = tmp;
            j--;
        }
    }
}

void bucketSort(std::vector<int>& numbers, int numBuckets)
{
    if (numbers.size() < 1)
    {
        return;
    }
    
    std::vector<int>* buckets = new std::vector<int>[numBuckets];

    int max = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
    {
        if (numbers[i] > max)
        {
            max = numbers[i];
        }
    }

    for (int i = 0; i < numbers.size(); i++)
    {
        int index = floor(numbers[i] * numBuckets / (max + 1));
        buckets[index].push_back(numbers[i]);
    }

    int movedCount = 0;

    for (int i = 0; i < numBuckets; i++)
    {
        insertionSort(buckets[i]);

        for (int j = movedCount; j < movedCount + buckets[i].size(); j++)
        {
            numbers[j] = buckets[i][j - movedCount];
        }

        movedCount += buckets[i].size();
    }

    delete[] buckets;
}

// Returns the length, in number of digits, of an integer value
int radixGetLength(int value)
{
    if (value == 0) {
       return 1;
    }
       
    int digits = 0;
    while (value != 0) {
       digits++;
       value /= 10;
    }
    return digits;
}

void radixSort(std::vector<int>& numbers)
{
    int maxRadixLength = 0, copyBackIndex = 0;

    for (int i = 0; i < numbers.size(); i++)
    {
        int digitCount = radixGetLength(numbers[i]);

        if (digitCount > maxRadixLength)
        {
            maxRadixLength = digitCount;
        }
    }

    std::vector<int>* buckets = new std::vector<int>[10];
    
    int pow10 = 1;
    for (int digitIndex = 0; digitIndex < maxRadixLength; digitIndex++) {
       // Put numbers into buckets
        for (int i = 0; i < numbers.size(); i++)
        {
            int num = numbers[i];
            int bucketIndex = (abs(num) / pow10) % 10;
            buckets[bucketIndex].push_back(num);
        }
          
       // Copy buckets back into numbers array
       copyBackIndex = 0;
       for (int i = 0; i < 10; i++)
       {
            std::vector<int>& bucket = buckets[i];
            for (int j = 0; j < bucket.size(); j++)
            {
                numbers[copyBackIndex] = bucket[j];
                copyBackIndex++;
            }
            bucket.clear();
        }
       
       pow10 *= 10;
    }
 
    std::vector<int> negatives;
    std::vector<int> nonNegatives;
    for (int i = 0; i < numbers.size(); i++)
    {
        int num = numbers[i];
        if (num < 0)
        {
          negatives.push_back(num);
        }
        else
        {
            nonNegatives.push_back(num);
        }
    }
       
    // Copy sorted content to array - negatives in reverse, then non-negatives
    copyBackIndex = 0;
    for (int i = negatives.size() - 1; i >= 0; i--)
    {
        numbers[copyBackIndex] = negatives[i];
        copyBackIndex++;
    }
    for (int i = 0; i < nonNegatives.size(); i++)
    {
        numbers[copyBackIndex] = nonNegatives[i];
        copyBackIndex++;
    }

    delete[] buckets;
}

void generateRandomData(std::vector<int>& numbers)
{
    for (int i = 0; i < numbers.size(); i++)
    {
        numbers.at(i) = rand() % 1000;
    }
}

int main()
{
    srand(time(0));

    int count;

    std::cout << "Enter the count of data points to generate: ";
    std::cin >> count;

    std::vector<int> insertData(count);
    generateRandomData(insertData);
    std::vector<int> bucketData(insertData);
    std::vector<int> radixData(insertData);

    std::cout << "Insert start..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(insertData);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Insert done!  ";
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    std:: cout << "Bucket start..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    bucketSort(bucketData, 10);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Bucket done!  ";
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    std::cout << "Radix start..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    radixSort(radixData);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Radix done!  ";
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    return 0;
}