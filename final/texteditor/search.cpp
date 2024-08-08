#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

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


int main(int argc, char *argv[]){

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open the file - '" << argv[1] << "'" << std::endl;
        return 0;
    }

    string line;
    int count = 1;
    while (std::getline(file, line)) {
        KMPSearch(argv[2],line,count);
        count++;
    }

    file.close();

    return 0;
}