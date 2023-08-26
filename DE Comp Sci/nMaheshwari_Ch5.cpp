//Nia Maheshwari
//niakmaheshwari@gmail.com
//Chapter 5 
//***************************************************************************************************
//The purpose of this program is to use functional decompostition to output a month based on the 
//user's input value. For instance, if '1' is inputted, then 'January' should be the correct output.                                                
//***************************************************************************************************

#include <iostream>
using namespace std;

int main() {

    //asking user to enter a number
    int userNum = 0;
    cout << "Please enter a number from 1-12 in numeric form. In other words, do not spell it out like a word when entering: " << endl;
    cin >> userNum;

    //asking the user to re-enter a number within the range should they choose a number that is not within the appropriate range
    while (userNum <= 0 or userNum > 12) {
        cout << "Oops! The number was out of range. Please enter a number from 1-12: " << endl;
        cin >> userNum;
    }

    if (userNum == 1) {
        cout << "January" << endl;
    }

    else if (userNum == 2) {
        cout << "February" <<endl;
    }

    else if (userNum == 3) {
        cout << "March" <<endl;
    }

    else if (userNum == 4) {
        cout << "April" <<endl;
    }

    else if (userNum == 5) {
        cout << "May" <<endl;
    }

    else if (userNum == 6) {
        cout << "June" <<endl;
    }

    else if (userNum == 7) {
        cout << "July" <<endl;
    }
    else if (userNum == 8) {
        cout << "August" <<endl;
    }

    else if (userNum == 9) {
        cout << "September" <<endl;
    }

    else if (userNum == 10) {
        cout << "October" <<endl;
    }

    else if (userNum == 11) {
        cout << "November" <<endl;
    }

    else if (userNum == 12) {
        cout << "December" <<endl;
    }

}