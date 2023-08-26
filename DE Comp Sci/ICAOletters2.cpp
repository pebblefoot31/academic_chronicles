// adapted from cristina999 work on cplusplus.com#include <iostream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  // establishing variables
  string inputWord;
  string outputWord = " ";
  char letters;

  // getting the word inputted by the user
  cout << " Enter a word: ";
  cin >> inputWord;

  for (int n = 0; n < inputWord.length(); n++) {
    letters = inputWord.at(n);

    // code which actually converts the input word into corresponding terms from
    // the ICAO alphabet
    switch (toupper(letters)) {
    case 'A':
      outputWord += " Alpha ";
      break;

    case 'B':
      outputWord += " Bravo ";
      break;

    case 'C':
      outputWord += " Charlie ";
      break;

    case 'D':
      outputWord += " Delta ";
      break;

    case 'E':
      outputWord += " Echo ";
      break;

    case 'F':
      outputWord += "Foxtrot ";
      break;

    case 'G':
      outputWord += " Golf ";
      break;

    case 'H':
    case 'h':
      outputWord += " Hotel ";
      break;

    case 'I':
      outputWord += " India ";
      break;

    case 'J':
      outputWord += " Juliet ";
      break;

    case 'K':
      outputWord += " Kilo ";
      break;

    case 'L':
      outputWord += " Lima ";
      break;

    case 'M':
      outputWord += " Mike ";
      break;

    case 'N':
      outputWord += " November ";
      break;

    case 'O':
      outputWord += " Oscar ";
      break;

    case 'P':
      outputWord += " Papa ";
      break;

    case 'Q':
      outputWord += " Quebec";
      break;

    case 'R':
      outputWord += " Romeo ";
      break;

    case 'S':
      outputWord += " Sierra ";
      break;

    case 'T':
      outputWord += " Tango ";
      break;

    case 'U':
      outputWord += " Uniform ";
      break;

    case 'V':
      outputWord += " Victor ";
      break;

    case 'W':
      outputWord += " Whiskey ";
      break;

    case 'X':
      outputWord += " X-ray ";
      break;

    case 'Y':
      outputWord += " Yankee ";
      break;

    case 'Z':
      outputWord += " Zulu ";
      break;
    }
  }
  // outputting the phonetic form of the word
  cout << "Here is '" << inputWord << "' in phonetic form: " << outputWord
       << endl;

}