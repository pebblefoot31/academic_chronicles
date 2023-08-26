//Nia Maheshwari
//niakmaheshwari@gmail.com
//phone number: (865)-232-7482
//Linux OS
//Terminal 
//Source File: modscores.dat (attached in comments alongside submission)
//Chapter 6 - Exercise 5
//***************************************************************************************************
//Summary + Logic
//The purpose of this program is to looping skills to compute and output the standard deviation of a
//data set. The file was called 'scores.dat', and contained names and corresponding test scores. To
//simplify the programming process, I created another version of the data file known as 'modscores.dat'
//which only contains the scores. This was much simpler to parse through using code as I did not need
//to implement code that would ignore the characters in the names. From there, I used features provided 
//by the cmath library to compute the standard deviation. I used a different formula from that given 
//in the textbook as the textbook version was giving me a nonreal answer somehow.                                             
//***************************************************************************************************

#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;


int main() {

  //establishing variables
  int count; //for loop counter
  float inputNum; //scores used as floats in calculation
  float standardDev; //std dev
  float sum; //sum- used to calculate the meam
  float variance; //term for mean subtracted from input number, then squared
  float numOfValues = 14; //amount of scores
  string fileInput;
  ifstream inFile;
  inFile.open("modscores.dat"); //loading the file
   

  //calculating the sum
  for (count = 0; count <= 13; count++) {
    getline(inFile, fileInput);
    inputNum = stoi(fileInput); //converting fileInput (which is initially string) into integers (to use in mathematical computation)
    sum += inputNum;
  }
  

  //calculating the square of the sum
  float mean = sum/14;  


  //calculating the sum of squares
  inFile.open("modscores.dat"); //loading file
  for (count = 0; count <= 13; count++) {
    getline(inFile, fileInput);
    inputNum = stoi(fileInput);
    variance += pow((inputNum - mean), 2);
  }
  
  
  //computing the standard dev
  standardDev = sqrt(variance/(numOfValues)); 
  

  //outputting the std. dev
  cout << "The standard deviation is " << standardDev << setprecision(3) << endl;
  
  return 0;

}