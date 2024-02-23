//Nia Maheshwari
//Dr. Jens Gregor
//UTK COSC 302

#include "Support.h"
#include <iostream>
#include <vector>
#include <list>
#include <cstring>

using namespace std;

int main(int argc, char **argv) {

	bool rawdata_flag = false;
	string targetLocation;

	if (argc == 1 || argc > 3) { //ensuring number of arguments is appropriate
		cerr << "usage: ./Prog1 [-rawdata] datafile" << endl;
		return 0;
	}

	// part 1: read and print rawdata
    database data;
    data.init_rawdata(argv[(argc-1)]);

	if (argc == 3) { //ensuring arguments are correct 

		for (int h = 0; h < argc; h++) { //checking for rawdata input 

			if ((strcmp(argv[h], "-rawdata")) == 0) {
			
				rawdata_flag = true;
				data.print_rawdata();
			}
		}

		if (!rawdata_flag) {

			cerr << "usage: ./Prog1 [-rawdata] datafile" << endl; //error message
			return 0;
		}
	}

  //part 2: create and print summaries
	if (!rawdata_flag) { //if not asked to print rawdata

		data.init_summary();

		while (true) { //loop of prompting 

			cout << "print> ";
			cin >> targetLocation;

			if (cin.eof()) { //quit if user inputs ctrl+D or ctrl+C

				cout << endl;
				return 0;
			}

			else {

				data.print_summary(targetLocation);

			}
		}
	}

    return 0;   

}
