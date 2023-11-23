//Nia Maheshwari
//Professor Adam Disney
//UTK COSC 202

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

bool success = false;
bool findall = false;
bool verbose = false;

void show_solution(vector <int> &numbers, vector <int> &operations) {

    char sign;
    vector <char> operators; 

	//creating a vector that will store the operators in the solution order
    for (size_t i = 0; i < (numbers.size()-1); i++) {

            if (operations[i] == 1) {
                sign = '+';
            }
    
            if (operations[i] == 2) {
                sign = '-';
            }
            
            if (operations[i] == 3) {
                sign = '*';
            }
    
            if (operations[i] == 4) {
                sign = '/';
            }

        operators.push_back(sign);

		//only if verbose print equation (alternating number and sign)
        if (verbose) {
            cout << numbers[i];
            if (i < numbers.size()-2) {
                cout << sign; 
            }
        }
    }

	//printing equation cont'd
    if (verbose) {

        cout << "=" << numbers[numbers.size()-1];
        cout << " ";
    }

	//printing out the signs only
    for (size_t o = 0; o < operators.size()-1; o++) {
        cout << operators[o];
    }

    cout << endl;
}



bool find_solution(vector <int> &numbers, vector <int> &operations, int k=0, int fvalue=0) {

    int n = numbers.size()-1;

    //recursive/starter case
    if (k == 0) {
        operations.clear(); 
        if (find_solution(numbers, operations, k+1, numbers[0])) { //recursing
            return true;
        }
        return false;
    }

    //base case
    if (k == n) {

        //we found our solution, stop recursing.
        if (numbers[n] == fvalue) {
            show_solution(numbers, operations);
            success = true; //indicating that we actually found a solution
            return true;
        }
        return false;
    }
    

    for (int i = 1; i < 5; i++) {

        int new_fValue = fvalue;

        switch (i) {

            //add
            case 1:
                new_fValue = new_fValue + numbers[k];
                break;
                
            //subtract
            case 2:
                new_fValue = new_fValue - numbers[k];
                break;
                
            //multiply
            case 3: 
                new_fValue = new_fValue * numbers[k];
                break;

            //divide
            case 4:
                new_fValue = new_fValue / numbers[k];
                break;
        }

        operations.push_back(i); //updating the operations vector to hold the latest val
 
        if (find_solution(numbers, operations, k+1, new_fValue)) { //exiting the recursion if we only want one solution and it was found
            if (!findall) {
                return true;
            }
        } 
        
        operations.pop_back(); //popping back the latest operation if we did not find a solution
        
     }

    return false;
}


int main(int argc, char **argv) {

    vector <int> numbers;
    vector <int> ops;
    int num;
    bool explorePermutations = false;

    //reading all generated numbers into the numbers vector
    while (cin >> num) {
        numbers.push_back(num);
    }


    //commandline parsing: making sure that num of args is within acceptable range
    if (argc < 3 || argc > 4) {
		cerr << "usage: ./Prog6 -inorder|anyorder -1|2 [-verbose] < numbers.txt" << endl;
        return 1;
    }


    //commandline parsing: checking whether or not to pursue permutations 
    if ((strcmp(argv[1], "-inorder")) == 0 || (strcmp(argv[1], "-anyorder")) == 0) {
            
         if ((strcmp(argv[1], "-anyorder")) == 0) {
                explorePermutations = true;
         }
    }

    else {
		cerr << "usage: ./Prog6 -inorder|anyorder -1|2 [-verbose] < numbers.txt" << endl;
        return 1;
    }


    //commandline parsing: checking whether or not to pursue multiple solutions
    if ((strcmp(argv[2], "-1")) == 0 || (strcmp(argv[2], "-2")) == 0) {

        if ((strcmp(argv[2], "-2")) == 0) {
            findall = true;
        }
    }

	else {
		cerr << "usage: ./Prog6 -inorder|anyorder -1|2 [-verbose] < numbers.txt" << endl;
        return 1;
	}


    //commandline parsing: checking for verbose option
    if (argc == 4) {
        if ((strcmp(argv[3], "-verbose")) == 0) {
        verbose = true;

        }

        else {
            cerr << "error message." << endl;
            return 1;
        }
    }


    //commandline parsing: going through all of the permutations
    if (explorePermutations) {

		sort(numbers.begin(), numbers.end()-1); //sorting the vector (all but the target number) before exploring permutations
		do {
			find_solution(numbers, ops, 0, numbers[0]); //finding a sol for the numbers in their current order
		} while (next_permutation(numbers.begin(), numbers.end()-1)); //trying the next permutation of the nums (changing up order)
	}

	else {
		find_solution(numbers, ops, 0, numbers[0]); //calling find_sol with the given order of numbers vector
	}


	if (!success) {
		return 1;
	}

    return 0;
}


