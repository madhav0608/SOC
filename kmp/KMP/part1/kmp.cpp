/*
In this problem, you will be implementing the Knuth Morris Pratt (KMP) algorithm as dicussed in class
Complete the functions 'computeLPSArray' and 'KMPSearch' where the former preprocesses the query
and the latter prints all occurences of the target pattern in the string. 

You can use the print statement already provided to match the output format (You can write your own print statement too)

Running Instructions
Run make to compile your code.
Run make test to test your code on the provided testcase

Input Format
2 line input.
First line contains pattern
Second line contains text.
No whitespace or newline characters withing either string.
(To add support for whitespace, you will have to change main.cpp, you can try doing this on your own OPTIONALLY)

Output Format
Provided in outputs/output0.txt.
Multiple occurences can be possible and will be printed on SEPARATE LINES in the same way.

Please also test the code with your OWN test cases.

- We will test both KMPSearch and computeKMPTable function.
  Please do not change their definitions.

- Please note that we will ONLY copy kmp.cpp to our auto-grader.
  Any modification to any other file will not be part of the
  evaluation of the submission. Please make sure that your
  submission continue to work with the original version of
  the other files.
*/


#include <iostream>
#include <cstring>

// Function to construct the KMP table (LPS array) which stores the length of the longest
// prefix that is also a suffix for each prefix of the pattern.
void computeKMPTable(string pat, int M, int* lps) {
    int i = 1;       // Start with the second character in the pattern
    int j = 0;       // Length of the current matching prefix

    // The first value of the LPS array is always 0 because there is no proper prefix for a single character
    lps[0] = 0;      

    // Loop through the pattern to populate the LPS array
    while (i < M) {
        if (pat[i] == pat[j]) {     // If characters match, extend the current matching prefix
            j++;
            lps[i] = j;             // Set the LPS value to the current length of the matching prefix
            i++;                    // Move to the next character in the pattern
        } else {
            if (j != 0) {           // If there is a previous matching prefix
                j = lps[j - 1];     // Recalculate the length of the matching prefix by using the previous LPS value
            } else {
                lps[i] = 0;         // If no matching prefix, set LPS value to 0
                i++;                // Move to the next character
            }
        }
    }
}

// Function to search for occurrences of the pattern in the text using the KMP algorithm
void KMPSearch(string pat, string txt, int line) {
    int M = pat.size();  // Length of the pattern
    int N = txt.size();  // Length of the text

    int lps[M];          // Array to store the LPS values for the pattern
    computeKMPTable(pat, M, lps);  // Construct the LPS array for the pattern

    int i = 0;  // Index for the text
    int j = 0;  // Index for the pattern

    // Loop through the text to search for the pattern
    while (i < N) {
        if (txt[i] == pat[j]) {  // If characters match, move both indices forward
            i++;
            j++;
        }

        if (j == M) {  // If the entire pattern has been matched
            cout << "Pattern found at line " << line << ", starting at index " << i - j << endl;
            j = lps[j - 1];  // Reset the pattern index using the LPS array
        } else if (i < N && txt[i] != pat[j]) {  // If characters do not match
            if (j != 0) {
                j = lps[j - 1];  // Use the LPS array to avoid unnecessary comparisons
            } else {
                i++;  // Move to the next character in the text
            }
        }
    }
}

