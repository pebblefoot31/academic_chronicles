//Nia Maheshwari
//UTK COSC 202
//Adam W Disney

#include <algorithm>
#include <vector>
#include <iostream>
#include "Support.h"
using namespace std;


bool isPrime(int n) { //function to determine if a number is prime 
   
    for (int i = 2; i*i <= n; i++) {
        if ((n % i) == 0) {
            return false;
        }
    }

    return true;
}


isprime::isprime(bool verbose) { //constructor for isprime class
    this->verbose = verbose;
    known_primes.push_back(2);
}


bool isprime::operator()(int n) {

    int i = known_primes.at((known_primes.size()-1)); //setting i to have the value of the element at the final index in known_primes vector 

    if (n < 2) //not considering any number less than 2
        return false;
    
    if (n > i) { //comparing with the last element of the known_primes vector
        expand_known_primes(n); //this function will only add the number to known_primes if it is prime!
    }
    
    return binary_search(known_primes.begin(), known_primes.end(), n); //binary search condition checking whether the number is present in known_primes
}


void isprime::expand_known_primes(int n) {

   //starting one value up from the largest value present in the known_primes (since we already covered it)
   int i = ((known_primes.at(known_primes.size()-1))+1);
   
   if (this->verbose) //for the -verbose option
        cout << "updating " << n << endl;

   //the loop that adds numbers to known_primes as necessary
   while (true) {

       if ((isPrime(i)) && i < n) {
           known_primes.push_back(i);
           if (this->verbose)
               cout << "** adding " << i << endl;
       }

       if ((isPrime(i)) && i >= n) {
           known_primes.push_back(i);
           if (this->verbose)
               cout << "** adding " << i << endl;

           break;
       }

       i++;
   }

   return;
}

