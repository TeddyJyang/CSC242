/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 5 Comprehensive Program Challenge
** File: 	SpellChecker.cpp
** Description: The purpose of this program is to read a dictionary file and a user-specified text file, then check each word in the text file against the dictionary. It will report any misspelled or unrecognized words, ignoring case and punctuation. The program uses a vector to store the dictionary words and binary search for efficient lookups.
**
** Author: 	Cody Currens, Armando Diaz, and Zhihao Jiang
** Date: 	6/13/2026
** -------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// converts a word to lowercase for case-insensitive comparison
string toLower(string word)
{
    for (int i = 0; i < word.length(); i++)
        word[i] = tolower(word[i]);
    return word;
}

// strips punctuation from the edges of a word (e.g. "hello," becomes "hello")
string stripPunctuation(string word)
{
    while (!word.empty() && ispunct(word.front()))
        word.erase(word.begin());
    while (!word.empty() && ispunct(word.back()))
        word.pop_back();
    return word;
}

int main()
{
    // -------------------------------------------------------
    // Step 1: Open the dictionary file
    // -------------------------------------------------------
    ifstream dict_file;
    dict_file.open("/usr/share/dict/words");

    if (!dict_file.is_open())
    {
        cout << "Error: Could not open dictionary file." << endl;
        cout << "Make sure /usr/share/dict/words exists on your system." << endl;
        return 1;
    }

    // -------------------------------------------------------
    // Step 2: Define a vector of strings called words
    // Step 3: For each word in the dictionary, append to vector
    // -------------------------------------------------------
    vector<string> words;
    string dictWord;

    while (dict_file >> dictWord)
    {
        words.push_back(toLower(dictWord));  // store all words in lowercase
    }
    dict_file.close();

    // sort the vector so we can use binary search for fast lookups
    sort(words.begin(), words.end());

    cout << "Dictionary loaded: " << words.size() << " words found." << endl;
    cout << "-----------------------------------" << endl;

    // -------------------------------------------------------
    // Step 4: Open the file to be checked
    // -------------------------------------------------------
    ifstream check_file;
    string filename;

    cout << "Enter the filename to spell check: ";
    cin >> filename;

    check_file.open(filename);

    if (!check_file.is_open())
    {
        cout << "Error: Could not open file \"" << filename << "\"." << endl;
        return 1;
    }

    // -------------------------------------------------------
    // Step 5: For each word in the file, check if it's in the vector
    // -------------------------------------------------------
    string fileWord;
    int misspelledCount = 0;

    cout << "\nMisspelled or unrecognized words:" << endl;
    cout << "-----------------------------------" << endl;

    while (check_file >> fileWord)
    {
        // clean the word before checking
        fileWord = stripPunctuation(fileWord);
        fileWord = toLower(fileWord);

        // skip empty strings and pure numbers
        if (fileWord.empty() || isdigit(fileWord[0]))
            continue;

        // use binary search for fast lookup in the sorted vector
        if (!binary_search(words.begin(), words.end(), fileWord))
        {
            cout << fileWord << endl;
            misspelledCount++;
        }
    }
    check_file.close();

    // -------------------------------------------------------
    // Summary report of all misspelled words found in the file.
    // -------------------------------------------------------
    cout << "-----------------------------------" << endl;
    if (misspelledCount == 0)
        cout << "No misspelled words found!" << endl;
    else
        cout << "Total unrecognized words: " << misspelledCount << endl;

    return 0;
}