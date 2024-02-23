//Nia Maheshwari
//Dr. Jens Gregor
//COSC 302
//Note: received help from Shivam

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include "Support.h"

using namespace std;

//adding omega() function from class05_sorting_4_handout.pdf
float omega() {

    return (float)std::clock()/(float)CLOCKS_PER_SEC;
}

//copied from Lab 2
class Data {

    friend istream & operator>>(istream &, Data &);
    friend ostream & operator<<(ostream &, const Data &);
    
    public:
        bool operator<(const Data &) const;
    
	//adding private ID integer variable
    private:
        string firstname;
        string lastname;
        string phonenum;
        int ID;
};

//copied from Lab 2
bool Data::operator<(const Data &rhs) const {

    //remove phone number tiebreaker
    if (lastname != rhs.lastname) { //comparing by lastname

        if (lastname < rhs.lastname) {
               return true;
        }
     }
    
    else { 

        if (firstname < rhs.firstname) {
               return true;
         }
     }
    
    return false;
} 

//copied from Lab 2
istream & operator>>(istream &in, Data &r) {

	static int ID = 2;
    //increment and assign value to r.ID
    in >> r.firstname >> r.lastname >> r.phonenum;
	r.ID = ID++;

    return in;
}

//copied from Lab 2
ostream & operator<<(ostream &out, const Data &r) {
  // add r.ID output (setw(8), right justified)

    string firstLast;
    firstLast = r.lastname + "," + r.firstname;
    
    out << setw(23) << left << setfill('.') << firstLast << left;
    out << right << " " << r.phonenum << setw(9) << right << setfill(' ') << r.ID;
    
    return out;
}

//copied from Lab 2
template <typename T>
void printData(T p1, T p2, string &fname) { //writes sorted list data to file

    ofstream fout(fname.c_str(), fstream::trunc);
    
     while (p1 != p2) {

        fout << *p1 << "\n";
        ++p1;
     }
    
     fout.close();
}

// compare lastname, firstname, phone number
int main(int argc, char *argv[]) {

    //error checking command line arguments
    if (argc != 3) { //ensuring that the num of cmdline arguments is valid
    
          cerr << "usage: ./Prog3 -insertion|mergesort|stdsort|quicksort file.txt" << endl; 
          return 1;
    }

    bool stdsort = false;
    bool insort = false;
    bool mergesort = false;

    //cmdline arg checking: CS302: Prog3 -insertion|mergesort|stdsort file.txt
    while (true) {

        if ((strcmp(argv[1], "-stdsort")) == 0) {
           stdsort = true;
           break;
        }
        
        else if ((strcmp(argv[1], "-insertion")) == 0) {
           insort = true;
           break;
        }
        
        else if ((strcmp(argv[1], "-mergesort")) == 0) {
           mergesort = true;
           break;
        }

        else { //in the case that the wrong args are inputted
            cerr << "usage: ./Prog3 -insertion|mergesort|stdsort|quicksort file.txt" << endl; 
            return 1;
        }
    } 
    
    ifstream fin(argv[(argc-1)]);
     
    if (!fin) { //ensuring file opens correctly
        cerr << "error opening file." << endl;
        return 1;
    }

    string writeFileName;
    string inputName = argv[argc-1]; //input file name
    ofstream writeFile;

    dlist<Data> A;
    Data din;

    while (fin >> din) { //creating vector of Data
       A.push_back(din);
    }
    
    fin.close();

    float T0 = omega(); //time initial

	//performing sort based on cmdline args
    if (insort) {
  
      writeFileName = "insertion_" + inputName;
      A.insertion_sort();
      
    } 
  
    else if (mergesort) {
  
      writeFileName = "mergesort_" + inputName;
      A.mergesort();
  
    } 
  
    else if (stdsort) {
  
      writeFileName = "stdsort_" + inputName;
      A.quicksort(1);
  
    } 
  
    float T1 = omega(); //time after sorting
    float timeDiff = 1000.0*(T1-T0); //computing the time elapsed in ms

    // print T1-T0 in ms
    cout << setprecision(1) << fixed << timeDiff << " ms\n"; 
  
	//writing to the output file
    writeFile.open(writeFileName);
    printData(A.begin(), A.end(), writeFileName);

    return 0;
}
