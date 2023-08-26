//Nia Maheshwari
//niakmaheshwari@gmail.com
//phone number: (865)-232-7482
//Linux OS
//Terminal 
//Chapter 11 - Exercise 4
//***************************************************************************************************
//Summary + Logic
//The purpose of this program is to convert the letters of a word inputted by the user into phonetic
//form based on the ICAO alphabet using an array. For instance, "Hello" would be Hotel  Echo  Lima 
// Lima  Oscar. All I did was reformat the assignment from chapter 7 into an associative array, or a 
//dictionary (hopefully that is the correct definition of a dicionary).  A challenge I faced was the 
//understanding the steps to initializing this kind of dictionary; apparently, the constructor is a 
// 'map'. After doing some brief research, I understood the format and how to create a key with char
// data type that refers to a value with string type. However, creating a dictionary was certainly 
//not my first attempt at tackling this problem. My first thought was to create a two-dimensional 
//array; however, I figured that at that point, creating a dictionary would make sense. Hopefully this
//approach meets the criteria of this assignment even as I did not 'index the array by the position of
//the letters of the alphabet' by number (i.e. 'Alpha' being at index 1). To be frank, I did not quite
//understand that portion of the crieteria, as connect a number to its corresponding letter of the 
//alphabet which is finally associated with its respective ICAO word seemed a bit excessive (beating
// around the bush in terms of code). Thus, I coded the following program.
//****************************************************************************************************

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {

  //initializing variables
  string inputWord;
  string outputWord = " ";
  char letters;
  
  //getting the inputWord from the user
  cout << "Enter string: ";
  cin >> inputWord;

  //initializing a dictionary
  map<char, string> icao;
    
    //assigning corresponding ICAO words to the correct alphabetical index in the dictionary 
    icao['A'] = "Alpha";
    icao['B'] = "Bravo";
    icao['C'] = "Charlie";
    icao['D'] = "Delta";
    icao['E'] = "Echo";
    icao['F'] = "Foxtrot";
    icao['G'] = "Golf";
    icao['H'] = "Hotel";
    icao['I'] = "India";
    icao['J'] = "Juliet";
    icao['K'] = "Kilo";
    icao['L'] = "Lima";
    icao['M'] = "Mike";
    icao['N'] = "November";
    icao['O'] = "Oscar";
    icao['P'] = "Papa";
    icao['Q'] = "Quebec";
    icao['R'] = "Romeo";
    icao['S'] = "Sierra";
    icao['T'] = "Tango";
    icao['U'] = "Uniform";
    icao['V'] = "Victor";
    icao['W'] = "Whiskey";
    icao['X'] = "X-Ray";
    icao['Y'] = "Yankee";
    icao['Z'] = "Zulu";
      
  //initializing an iterator to use in the 'for' loop  
  map<char, string>::iterator n;
  
  //for loop which cycles through the dictionary according to the inputted string and appends the correct word to the outputWord string
  for (int n = 0; n < inputWord.length(); n++) {
      letters = inputWord.at(n);
      outputWord += icao[toupper(letters)];
      outputWord += " ";
    }

  //final statement that prints out the phonetic form of the inputted word (so the final result)
  cout << "The phonetic form of " << inputWord << " is: " << outputWord;
}