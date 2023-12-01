#pragma once
#include <set>
#include <vector>
using namespace std;

class prime_partition {

  public:
	prime_partition();              //constructor
	void set_verbose();             //set verbose function
	void find_partition(int);       //prints partition if found (public wrapper)

  private:
	void expand_pset(int);          //similar to lab three where we add primes to pset
	bool is_valid(int, int);        //check return condition of a partition for number and terms
	bool find_partition(int, int);  //finds partition recursively (private helper)

	bool verbose;                   //whether to print verbose output
	int num_terms;                  //the number of terms to look for (in this case always 3)
	int pset_min;                   //always 2
	int pset_max;                   //the current largest prime in pset

	set<int> pset;                  //the set of primes
	vector<int> partition;          //the vector keeping track of the partition of numbers

};

