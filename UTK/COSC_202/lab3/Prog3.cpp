//Nia Maheshwari
//UTK COSC 202
//Adam W Disney

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "Support.h"
using namespace std;


int main(int argc, char *argv[]) {

    vector<int> primeNumbers; //the vector that will hold all prime numbers when we run Numbers* 
    string line;
    int currentNum;
    int numCount = 1;
    bool flag = true;
    bool verbose = false;
    bool sorted = false;

    for (int v = 0; v < argc; v++) { //checking if "-verbose" command has been presented in the terminal
        if ((strcmp(argv[v], "-verbose")) == 0) {
           verbose = true;
        }
    }
    
    isprime processPrime(verbose); //creating an instance of the isprime class 
								   //it takes into account the '-verbose' feature's status

    while (getline(cin, line)) { //reading in the output from executing Numbers* (line by line at first, and then by value)
        stringstream myStream(line);

        while (myStream >> currentNum) {

            if (processPrime(currentNum)) { //if the number is in the known_primes vector
                primeNumbers.push_back(currentNum); //it will be added to primeNumbers 
            }
        } 
     }
 

    //checking if "-help" command has been presented in the terminal as an argument (just in case)
    for (int h = 0; h < argc; h++) { 
        if ((strcmp(argv[h], "-help")) == 0) {
           cerr << "usage: ./Numbers [N M]" << endl; 
           flag = false;
        } 
    }

    //checking if "-sort" command has been presented in the terminal
    for (int i = 0; i < argc; i++) {
        if ((strcmp(argv[i], "-sorted")) == 0) {
            sort(primeNumbers.begin(), primeNumbers.end());
            sorted = true;
        }
    }

    //checking if "-unique" command has been presented in the terminal
    for (int j = 0; j < argc; j++) { 
        if ((strcmp(argv[j], "-unique")) == 0) {

            sort(primeNumbers.begin(), primeNumbers.end()); //will have to sort anyway for the unique function to work correctly
            auto new_end = unique(primeNumbers.begin(), primeNumbers.end()); 
            primeNumbers.resize(distance(primeNumbers.begin(),new_end));
            sorted = true;
        
        } 
    }



    //print everything out correctly formatted (only if the usage was correct.)
    if (flag) {

	//fixing spacing in the first line
        if (sorted) 
            cout << "   ";
        else
            cout << "  ";

        for (int m = 0; m < primeNumbers.size(); m++) {

            if (numCount >= 1 && numCount < 20) {
                cout << right << setfill(' ') <<  primeNumbers[m] << setw(5); //using iomanip features to set the inter-value spacing
            }

            if (numCount == 20) {
                cout << right << setfill(' ') <<  primeNumbers[m] << setw(4);
                cout << endl;
            }

            if (numCount == 21) {
                cout << right << setfill(' ') <<  primeNumbers[m] << setw(5);
                numCount = 1;
            } 

            numCount++; 

            if (m == (primeNumbers.size()-1)) //stop printing stuff when we reach the end of the primeNumbers vector
                cout << endl;
        } 
   } 
 

    return 0;
}

