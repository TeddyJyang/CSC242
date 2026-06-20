/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #2
** File: 	source.cpp
** Description: This program reads a positive integer from the user and prints all of its binary digits. 
** The program repeatedly prints the remainder of number % 2, then replaces the number with number / 2 until the number becomes 0. 
** The binary digits are printed from least significant bit to most significant bit.
**
** Author: 	Zhihao Jiang
** Date: 	20260607
** -------------------------------------------------------------------------*/


#include <iostream>
using namespace std;

int main()
{
    // Variable declarations
    int number;           // The number to convert to binary
    int originalNumber;   // Store original number for display purposes

    // Display program purpose
    cout << "Binary Digit Converter" << endl;
    cout << "This program converts a decimal number to binary digits" << endl;
    cout << endl;

    // Prompt user for input
    cout << "Enter a positive integer: ";
    cin >> number;

    // Store the original number for display
    originalNumber = number;

    // Validate input
    if (number < 0)
    {
        cout << "Error: Please enter a positive number." << endl;
        return 1;  // Exit with error code
    }

    // Handle special case when number is 0
    if (number == 0)
    {
        cout << "Binary digits of 0:" << endl;
        cout << 0 << endl;
        return 0;
    }

    // Display header for output
    cout << "Binary digits of " << originalNumber
        << " (from least to most significant):" << endl;

    // Loop to extract and print binary digits
    // Continue until number becomes 0
    while (number > 0)
    {
        // Print the least significant bit (remainder when divided by 2)
        cout << number % 2 << endl;

        // Remove the least significant bit by integer division
        number = number / 2;
    }

    return 0;  // Successful program termination
}
