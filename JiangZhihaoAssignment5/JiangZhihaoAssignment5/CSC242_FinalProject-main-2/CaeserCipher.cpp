/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 	CSC 242
** Assignment: 5 Comprehensive Program Challenge
** File: 	CaeserCipher.cpp
** Description: The purpose of this program is to encrypt or decrypt text files using a monoalphabetic substitution cipher based on a user-provided keyword. The program builds a cipher alphabet by taking the unique letters of the keyword followed by the remaining letters of the alphabet in reverse order. It then processes an input file character by character, applying the cipher transformation while preserving case and non-alphabetic characters.
**
** Author: 	Cody Currens, Armando Diaz, and Zhihao Jiang
** Date: 	6/16/2026
** -------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

// -------------------------------------------------------
// Builds the cipher alphabet from a keyword.
//
// Example with keyword "FEATHER":
//   Step 1 - uppercase and remove duplicates: FEATHR
//   Step 2 - append remaining letters in REVERSE order: ZYXWVUSQPONMLIKJGDCB
//   Result: FEATHRZYMXWVUSQPONMLIKJGDCB
//
// Plain:  ABCDEFGHIJKLMNOPQRSTUVWXYZ
// Cipher: FEATHRZYMXWVUSQPONMLIKJGDCB  
// -------------------------------------------------------
string buildCipherAlphabet(const string& keyword)
{
    string key = "";

    // Step 1: uppercase the keyword and remove duplicate letters
    for (char ch : keyword)
    {
        char upper = toupper(ch);
        if (isalpha(upper) && key.find(upper) == string::npos)
            key += upper;
    }

    // Step 2: append remaining alphabet letters in REVERSE order (Z down to A)
    for (char ch = 'Z'; ch >= 'A'; ch--)
    {
        if (key.find(ch) == string::npos)
            key += ch;
    }

    return key;  // this is the 26-letter cipher alphabet
}

// -------------------------------------------------------
// Prints the cipher table so the user can see the mapping
// -------------------------------------------------------
void printCipherTable(const string& cipher)
{
    cout << "Plain:  ABCDEFGHIJKLMNOPQRSTUVWXYZ" << endl;
    cout << "Cipher: " << cipher << endl;
    cout << "-----------------------------------" << endl;
}

// -------------------------------------------------------
// Encrypts a single character using the cipher alphabet.
// Preserves case and leaves non-alpha characters unchanged.
// -------------------------------------------------------
char encryptChar(char ch, const string& cipher)
{
    if (!isalpha(ch)) return ch;

    bool isLower = islower(ch);
    char upper   = toupper(ch);
    char encoded = cipher[upper - 'A'];   // map A=0, B=1, ... Z=25

    return isLower ? tolower(encoded) : encoded;
}

// -------------------------------------------------------
// Decrypts a single character using the cipher alphabet.
// Finds where the cipher letter appears and maps it back.
// -------------------------------------------------------
char decryptChar(char ch, const string& cipher)
{
    if (!isalpha(ch)) return ch;

    bool isLower = islower(ch);
    char upper   = toupper(ch);

    // find position of this letter in the cipher alphabet
    int pos = cipher.find(upper);
    char decoded = 'A' + pos;             // reverse map back to plain letter

    return isLower ? tolower(decoded) : decoded;
}

// -------------------------------------------------------
// Processes the input file and writes to output file
// -------------------------------------------------------
void processFile(const string& inputFile,
                 const string& outputFile,
                 const string& cipher,
                 bool decrypt)
{
    ifstream in_file;
    ofstream out_file;

    in_file.open(inputFile);
    if (!in_file.is_open())
    {
        cerr << "Error: Cannot open input file \"" << inputFile << "\"." << endl;
        exit(1);
    }

    out_file.open(outputFile);
    if (!out_file.is_open())
    {
        cerr << "Error: Cannot open output file \"" << outputFile << "\"." << endl;
        exit(1);
    }

    char ch;
    while (in_file.get(ch))
    {
        char processed = decrypt ? decryptChar(ch, cipher)
                                 : encryptChar(ch, cipher);
        out_file.put(processed);
    }

    in_file.close();
    out_file.close();
}

// -------------------------------------------------------
// Prints usage instructions
// -------------------------------------------------------
void printUsage()
{
    cout << "Usage:" << endl;
    cout << "  crypt -e -kKEYWORD input.txt output.txt   (encrypt)" << endl;
    cout << "  crypt -d -kKEYWORD input.txt output.txt   (decrypt)" << endl;
    cout << endl;
    cout << "Example:" << endl;
    cout << "  crypt -e -kFEATHER plain.txt encrypted.txt" << endl;
    cout << "  crypt -d -kFEATHER encrypted.txt decrypted.txt" << endl;
}

// -------------------------------------------------------
// Main: parse command-line arguments and run cipher
// -------------------------------------------------------
int main(int argc, char* argv[])
{
    // need at least 4 arguments: mode, keyword, input, output
    if (argc < 5)
    {
        cerr << "Error: Not enough arguments." << endl;
        printUsage();
        return 1;
    }

    // --- parse mode: -e (encrypt) or -d (decrypt) ---
    string modeArg = argv[1];
    bool decrypt = false;

    if (modeArg == "-e")
        decrypt = false;
    else if (modeArg == "-d")
        decrypt = true;
    else
    {
        cerr << "Error: First argument must be -e (encrypt) or -d (decrypt)." << endl;
        printUsage();
        return 1;
    }

    // --- parse keyword: must start with -k ---
    string keyArg = argv[2];
    if (keyArg.substr(0, 2) != "-k" || keyArg.length() < 3)
    {
        cerr << "Error: Keyword is required. Use -kKEYWORD (e.g. -kFEATHER)." << endl;
        printUsage();
        return 1;
    }
    string keyword = keyArg.substr(2);  // strip the "-k" prefix

    // --- input and output filenames ---
    string inputFile  = argv[3];
    string outputFile = argv[4];

    // --- build the cipher alphabet ---
    string cipher = buildCipherAlphabet(keyword);

    // --- display info ---
    cout << "\nMonoalphabet Cipher" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Mode    : " << (decrypt ? "Decrypt" : "Encrypt") << endl;
    cout << "Keyword : " << keyword << endl;
    printCipherTable(cipher);

    // --- process the file ---
    processFile(inputFile, outputFile, cipher, decrypt);

    cout << (decrypt ? "Decryption" : "Encryption") << " complete!" << endl;
    cout << "Output written to: " << outputFile << endl;

    return 0;
}