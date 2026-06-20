/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #4
** File: 	source.cpp
** Description: Develop an algorithm for finding the most frequently occurring 
** value in an array of numbers. Use a sequence of coins. Place paper clips 
** below each coin that count how many other coins of the same value are in the
** sequence. Give the pseudocode for an algorithm that yields the correct answer, 
** and describe how using the coins and paper clips helped you find the algorithm.
**
** Author: 	Zhihao Jiang
** Date: 	20260610
** -------------------------------------------------------------------------*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int size;

    cout << "How many numbers would you like to enter? ";
    cin >> size;

    vector<int> numbers(size);
    vector<int> frequency(size, 0);

    cout << "Enter the numbers:" << endl;

    for (int i = 0; i < size; i++)
    {
        cin >> numbers[i];
    }

    // Count how many times each number appears
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (numbers[i] == numbers[j])
            {
                frequency[i]++;
            }
        }
    }

    int maxFrequency = frequency[0];
    int mostFrequentValue = numbers[0];

    // Find the largest frequency
    for (int i = 1; i < size; i++)
    {
        if (frequency[i] > maxFrequency)
        {
            maxFrequency = frequency[i];
            mostFrequentValue = numbers[i];
        }
    }

    cout << "\nMost frequently occurring value: "
        << mostFrequentValue << endl;

    cout << "Number of occurrences: "
        << maxFrequency << endl;

    return 0;
}