//Nia Maheshwari
//COSC 202
//Professor Adam Disney
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include "Support.h"
using namespace std;

int main(int argc, char *argv[]) {

    prime_partition goldbach;
    int number;
    bool forward = false;

    if (argc < 2 || argc > 4) { //ensuring that the right number of cmndline arguments are given
		cerr << "usage: ./Prog8 -forward|reverse [-verbose]" << endl;
        return 1;
    }

    //processing command line arguments
    for (int h = 0; h < argc; h++) { 

	   if ((strcmp(argv[h], "-forward")) == 0) {
            forward = true; 
       }
	}

	if (!forward) {
		cerr << "usage: ./Prog8 -forward|reverse [-verbose]" << endl;
		return 1;
	}

    for (int v = 0; v < argc; v++) { //checking for verbose

       if ((strcmp(argv[v], "-verbose")) == 0) {
           goldbach.set_verbose();
       }
	}

    while (true) { //entering infinite loop of prompting user to enter a number 

        cout << "number = ";
        cin >> number;

        //check for end-of-file to exit infinite loop
		if (cin.eof()) {
			cout << endl;
			return 0;
		}
        
        //checking if number is large enough before proceeding to find its Goldbach partition 
        if (number >= 6) {

            if (forward) {
                goldbach.find_partition(number);
            }
        }

        else {
            cerr << "Too small. Try again." << endl;
        }
	}

	return 0;

}
