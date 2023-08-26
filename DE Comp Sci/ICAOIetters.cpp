
//adapted from cristina999 work on cplusplus.com
#include <iostream>
#include <string>
using namespace std;

int main()
{
  //establishing variables
  string inputWord;
  string outputWord = " ";
  int len;
  char letters;

  
  len = inputWord.length() ;
  
        
  //code which actually converts the input word into corresponding terms from the ICAO alphabet
  switch(toupper(letters))
    {
      case 'A':
      outputWord += " Alpha ";
      break;
    
      case 'B': case 'b':
        outputWord += " Bravo ";
        break;
      
      case 'C': case 'c':
        outputWord += " Charlie ";
        break;
      
      case 'D': case 'd':
        outputWord += " Delta ";
        break;
      
      case 'E': case 'e':
        outputWord += " Echo ";
        break;
      
      case 'F': case 'f':
        outputWord += "Foxtrot ";
        break;
      
      case 'G': case 'g':
          outputWord += " Golf ";
          break;
      
      case 'H': case 'h':
        outputWord += " Hotel ";
        break;
      
      case'I': case 'i':
        outputWord += " India ";
        break;
      
      case 'J': case 'j':
        outputWord += " Juliet ";
        break;
      
      case 'K': case 'k':
        outputWord += " Kilo ";
        break;
      
      case 'L': case 'l':
        outputWord += " Lima ";
        break;
      
      case 'M': case 'm':
        outputWord += " Mike ";
        break;
      case 'N': case 'n':
          outputWord += " November ";
          break;
      case 'O': case 'o':
        outputWord += " Oscar ";
        break;
      case'P': case 'p':
        outputWord += " Papa ";
        break;
      case 'Q': case 'q':
        outputWord += " Quebec";
        break;
      case 'R': case 'r':
        outputWord += " Romeo ";
        break;
      case 'S': case 's':
        outputWord += " Sierra ";
        break;
      case 'T': case 't':
        outputWord += " Tango ";
        break;
      case 'U': case 'u':
          outputWord += " Uniform ";
          break;
     case 'V': case 'v':
         outputWord += " Victor ";
         break;
      case 'W': case 'w':
        outputWord += " Whiskey ";
        break;
      case'X': case 'x':
        outputWord += " X-ray ";
        break;
      case 'Y': case 'y':
        outputWord += " Yankee ";
        break;
      case 'Z': case 'z':
        outputWord += " Zulu ";
        break;
    }
   
  //outputting the phonetic form of the word
    cout << "Here is '" << inputWord << "' in phonetic form: " << outputWord<< endl;
    return 0;

}

  