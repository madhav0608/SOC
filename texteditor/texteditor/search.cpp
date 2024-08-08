#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

void computeKMPTable(string pat, int M, int* h)
{

  int length = 0; 
  h[0] = 0;

  int i = 1;
  while (i < M) {
    if (pat[i] == pat[length]) {
      length++;
      h[i] = length;
      i++;
    } else { 
      if (length != 0) {
        length = h[length - 1];
      } else { 
        h[i] = 0;
        i++;
      }
    }
  }

}

// Prints occurrences of txt[] in pat[]
void KMPSearch(string pat, string txt,int line)
{ 

  int M = pat.size();
  int N = txt.size();

  int h[M];
  computeKMPTable(pat, M, h);

  int i = 0; // index for txt[]
  int j = 0; // index for pat[]
  while (i < N) {
    
    if (pat[j] == txt[i]) {
      i++;
      j++;
    }

    if (j == M) {
        //   printf("Found pattern at index %d \n", i - j);
        cout << line << " " << i-j << endl;
        j = h[j - 1];
    } else if (i < N && pat[j] != txt[i]) { // mismatch after j matches
        if (j != 0) {
            j = h[j - 1];
        } else {
            i = i + 1;
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