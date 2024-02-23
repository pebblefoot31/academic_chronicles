//Nia Maheshwari
//Dr. Jens Gregor
//COSC_302
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include "Support.h"
using namespace std;

class data {
  friend istream & operator>>(istream &, data &);
  friend ostream & operator<<(ostream &, const data &);

  public:
	bool operator<(const data &) const;

  private:
    string firstname;
    string lastname;
    string phonenum;
};

bool data::operator<(const data &rhs) const { //overloading the < operator to compare instances of data

  //compare in following order: lastname, firstname, phone number

    if (lastname != rhs.lastname) {
        if (lastname < rhs.lastname) {
            return true;
        }
    }

    else if (firstname != rhs.firstname) {
        if (firstname < rhs.firstname) {
            return true;
        }
    }

    else {
        if (phonenum < rhs.phonenum) {
            return true;
        }
    }

    return false;
}

istream & operator>>(istream &in, data &r) { 

	//overloading to read in each line and populate an instance of data struct 
    in >> r.firstname >> r.lastname >> r.phonenum;

    return in;
}

ostream & operator<<(ostream &out, const data &r) {

	//overloading this operator to print out each data obj. in 
	//a pre-formatated way
	
    string firstLast;
    firstLast = r.lastname + "," + r.firstname;

    out << setw(23) << left << setfill('.') << firstLast << left; 
    out << right << " " << r.phonenum/* << endl*/;

    return out;  
}

template <typename T>
void printdata(T p1, T p2, string &fname) {
  ofstream fout(fname.c_str(), fstream::trunc);

  while (p1 != p2) {
    fout << *p1 << "\n";
    ++p1;
  }

  fout.close();
}

int main(int argc, char *argv[]) {

    srand(302); //seeding random value generator

    if (argc < 1 || argc > 5) { //ensuring that the num of cmdline arguments is valid

        cerr << "usage: ./Prog2 -stdsort | -qsort [k0 k1] file.txt" << endl;
        return 1;
    }

    bool stdsort = false;
    bool qsort = false;
    bool qsortK = false;
    int k0; 
    int k1; 

    for (int i = 0; i < argc; i++) { //checking for qsort or stdsort commandline argument

        if ((strcmp(argv[i], "-stdsort")) == 0) {
           stdsort = true;
        }

        if ((strcmp(argv[i], "-qsort")) == 0) {

            qsort = true;

            if (argc == 4) {
                
                cerr << "wrong args. " << endl;
                return 1;
            }

            if (argc == 5) { //condition to quickselect

                qsortK = true;
                k0 = atoi(argv[i+1]); //initializing k0
                k1 = atoi(argv[i+2]); //initializing k1
                
                if (k0 < 0) {  //validating k0 range
                    k0 = 0;
                }


            }

        }

    }

    if (!qsort && !stdsort) { //error checking cmd line arguments

        cerr << "usage: ./Prog2 -stdsort | -qsort [k0 k1] file.txt" << endl;
        return 1;
    }

    ifstream fin(argv[(argc-1)]);

    if (!fin) { //ensuring file opens correctly

        cerr << "error opening file." << endl;
        return 1;
    }

    vector<data> A; //vector that will hold all of the data objects
    data din; //creating a data obj

    while (fin >> din) { //initializing the array of data

        A.push_back(din);
    }

    int N = (int)A.size();

    if (qsortK && k1 >= N) { //validating k1 range
          k1 = N-1;
    }

    string writeFileName;
    string suffixName = argv[argc-1];
    ofstream writeFile; 

    fin.close();
  
    if (stdsort) {

        sort(A.begin(), A.end()); //performing std::sort on array
        writeFileName = "stdsort_" + suffixName;

    }

    if (qsort) {

        if (qsortK) {

			//performing quickselect and then quicksort on 
			//the array within the desired range
		
            quickselect(A,0,k0,N-1); 
            quickselect(A,k0,k1,N-1);
            quicksort(A, k0, k1);

        }

        writeFileName = "qsort_" + suffixName;

        k0 = 0;
        k1 = N-1;

		//applying quicksort to array
        quicksort(A, k0, k1);

    } 

	if (qsortK) { //filename if performing qselect on data

		writeFileName = "qselect_" + suffixName;
	}

	printdata(A.begin(), A.end(), writeFileName); //writing to appropriate file

  return 0;
}
