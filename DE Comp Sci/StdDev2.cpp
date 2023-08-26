#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

int main() {

  int count;
  float inputNum;
  float standardDev;
  float sum;
  float mean;
  float sumOfSq;
  float sqOfSum;
  float numOfValues = 14;
  ifstream inFile;
  string fileInput;

  inFile.open("modscores.dat");
  for (count = 0; count <= 13; count++) {
    getline(inFile, fileInput);
    inputNum = stoi(fileInput);
    sum += inputNum;
    sumOfSq += pow(inputNum, 2);
  }

  sqOfSum = pow(sum, 2);
  mean = sum / numOfValues;

  standardDev = sqrt(sumOfSq - sqOfSum);

  cout << sumOfSq << endl;
  cout << sqOfSum << endl;
  cout << "The standard deviation is " << standardDev << endl;

  return 0;
}