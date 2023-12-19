//Nia Maheshwari
//COSC 202
//Professor Adam Disney
#include <iostream>
#include <iterator>
#include <cmath>
#include <vector>
#include <set>
#include "Support.h"
using namespace std;

prime_partition::prime_partition() { //constuctor

  num_terms = 3;
  pset.insert(2);
  verbose = false;
  pset_max = 2;
  pset_min = 2; 

}

void prime_partition::set_verbose() { //setter function for verbose mode
    verbose = true;
}

void prime_partition::find_partition(int number) {

	int prev_pset_max = pset_max; //used to determine whether or not we want to output contents of pset in verbose

    if (pset_max < number) { //checking if we need to expand pset if the current number 
                             //is greater than the biggest number in pset
        expand_pset(number);
    }

    if (verbose && number > prev_pset_max) { //using an iterator to print contents of pset when verbose mode is called

		if (pset.size() <= 20) { //if pset is not too large, we print all elements

			set<int>::iterator it;

			for (it = pset.begin(); it != pset.end(); it++) {
				cout << *it << " ";
			}

			if (it == pset.end()) {
				cout << endl;
			}
		}

		else { //if pset is too large, we only want to print the first 10 and last 5 elements

			set<int>::iterator it;

			int forward_count = 0;

			for (it = pset.begin(); it != pset.end(); it++) { //first 10 elements

				if (forward_count == 10) {
					break;
				}

				cout << *it << " ";

				forward_count++;
			}

			cout << "... "; //ellipses divider

			for (it = prev(pset.begin(), 6); it != pset.end(); it++) { //last 5 elements

				cout << *it << " ";
			}

			cout << endl;
		}
    }
  
    partition.clear(); //clearing partition and making the first call
	find_partition(number,0);
}

void prime_partition::expand_pset(int number) { //expanding pset with additional prime numbers

    pset_max = *(pset.rbegin()); 
    int next_prime = pset_max + 1;
    
    while (pset_max <= number) {

        bool prime = true;

        for (size_t k = 2; k <= sqrt(next_prime); k++) {

             if (next_prime % k == 0) { //checking which values we need to add to pset
                   prime = false; //next is not prime
                   break;
              }
        }
    
        if (prime) {

            pset.insert(next_prime); //add to pset
			
            pset_max = *(pset.rbegin());  //updating pset max

			if (next_prime == number) { //if the current number is prime then we stop there-- do not add any more primes to pset
				break;
			}
        }
    
	    next_prime = next_prime + 1;
    }

}

bool prime_partition::is_valid(int number, int terms) {

	//series of conditions that determine the validity of the current number-terms pairing. 
	//help determine whther or not we should make a recursive call of the boolean find_partition() function

    if (number == 1) { //because 1 is not a prime number, not an option as a factor in the addition
        return false;
    }

    if (terms == num_terms && number != 0) { 
        return false;
    }

    if (terms != num_terms && number == 0) {
        return false;
    }

    if (terms == num_terms && number == 0) {
        return true;
    }
    
    if (terms < num_terms) {
        return true;
    }

    return false;
}

bool prime_partition::find_partition(int number, int terms) { //recursive function that determines the correct Goldbach's partition of given size for any number
															  //in this case, the partition size is set to 3
															  
    if (number == 0) { //base case (found the correct combination of prime numbers)

		if (!verbose) { //standard output if verbose is set to false
			for (int p = 0; p < terms-1; p++) {
				cout << partition[p] << "+"; 
			}

			cout << partition[terms-1] << endl;
		}

		return true;
    }

    set<int>::iterator k; 
    set<int>::iterator upper = pset.upper_bound(number);

    if (verbose) { //if verbose mode, print out the iterative solution (instead of just the final step)
 
       for (int p = 0; p < terms; p++) {
            cout << partition[p] << "+"; 
	   }

       cout << number << endl;
    }

	//recursive call occurs here
    for (k = pset.begin(); *k < *upper; k++) {

        partition.push_back(*k); //adding the prime number to partition because it could be potentially part of the solution

        if (is_valid(number-*k, terms+1)) { //only proceeding with recursive call if the number-terms pair is valid

            if (find_partition(number-*k, terms+1)) {

                return true;
            }

        }

        partition.pop_back(); //backtracking

    }

    return false;
}


