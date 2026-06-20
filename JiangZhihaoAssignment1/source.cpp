/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Lesson #1
** File: 	source.cpp
** Description: Read a telephone number into a string variable, computes the formatted number, and prints it.
**
** Author: 	Zhihao Jiang
** Date: 	20260526
** -------------------------------------------------------------------------*/


#include <iostream>
#include <string>

using namespace std;


int main() {
	cout << "Enter the ten-digit phone number: ";
	string phone;
	cin >> phone;

	string sub1 = phone.substr(0,3);
	string sub2 = phone.substr(3,3);
	string sub3 = phone.substr(6,4);
	string formatted = "(" + sub1 + ") " + sub2 + "-" + sub3;

	cout << "The formatted number is: " << formatted << endl;
	return 0;
}