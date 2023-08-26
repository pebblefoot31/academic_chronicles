#include <iostream>
#include <ctype.h>
#include <iomanip>
using namespace std;

//establishing variables
char typeOfWood;
float totalCost;
float cost;
float amountOfWood;
float width; 
float height; 
float length;
string woodName;
bool flag = true;

//function to calculate the amount of the wood by finding the volume in inches and converting it to square feet
float WoodAmountCalc(float width, float height, float length)
{
  float areaOfBoard;
  
  length *= 12;
  areaOfBoard = (width*height*length)/144;

  return areaOfBoard;
 }



int main() {

  //obtaining the user's order of wood
  cout << "Enter item: " << endl;
  cin >> typeOfWood;
  typeOfWood = toupper(typeOfWood);
  cin >> amountOfWood;
  cin >> width;
  cin >> height;
  cin >> length;

  //entering a loop based on the user's response
  while (typeOfWood != 'T' && amountOfWood > 0 && width > 0 && height > 0 && length > 0) {

    
    //pine wood calculations
     if (typeOfWood == 'P') {
       cost = (WoodAmountCalc(width, height, length))*amountOfWood*0.89; //computing cost based on volume of the wood
       woodName = "Pine"; //establishing name of wood for later output
       cout << amountOfWood << " " << width << "x" << height << "x" << length << " " << woodName << ", cost: $" << setprecision(4) << cost << endl;
      totalCost += cost; //outputting the information
          }

       
     //fir wood calculations  
     else if (typeOfWood == 'F') {
       cost = (WoodAmountCalc(width, height, length))*amountOfWood*1.09;
      woodName = "Fir";
      cout << amountOfWood << " " << width << "x" << height << "x" << length << " " << woodName << ", cost: $" << setprecision (4) << cost << endl;
      totalCost += cost;
         }

       
    //cedar wood calculations
     else if (typeOfWood == 'C') {
       cost = (WoodAmountCalc(width, height, length))*amountOfWood*2.26;
      woodName = "Cedar";   
      cout << amountOfWood << " " << width << "x" << height << "x" << length << " " << woodName << ", cost: $" << setprecision (4) << cost << endl;
      totalCost += cost;
      }

       
    //maple wood calculations
     else if (typeOfWood == 'M') {
       cost = (WoodAmountCalc(width, height, length))*amountOfWood*4.50;
      woodName = "Maple";    
      cout << amountOfWood << " " << width << "x" << height << "x" << length << " " << woodName << ", cost: $" << setprecision (4) << cost << endl;
      totalCost += cost;
      }

       
    //oak wood calculations
    else if (typeOfWood == 'O') {
       cost = (WoodAmountCalc(width, height, length))*amountOfWood*3.10;
      woodName = "Oak";
      cout << amountOfWood << " " << width << "x" << height << "x" << length << " " << woodName << ", cost: $" << setprecision (4) << cost << endl;
      totalCost += cost;
      }

   //asking the user's order once again-- this time as a part of the program 
  cout<< "Enter item: " << endl;
  cin >> typeOfWood;
  typeOfWood = toupper(typeOfWood);
  cin >> amountOfWood;
  cin >> width;
  cin >> height;
  cin >> length;
    
  }   

  //output for when the user chooses 'T' followed by a random series of characters that are not integers
  cout << "Total cost: $" << totalCost << endl; 
  
}
    





