//Nia Maheshwari
//Professor Adam Disney
//COSC 202
#include "Support.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char *argv[]) {

    ppm image;
    int block_size = 512;
    float rho = 1.0;
    char* file;
    string fileName;
    bool makeGray = false;
    bool makeFlip = false;
    bool makeLens = false;
	bool proceed = false;
	bool fileGiven = false;
	bool bsGiven = false;


    file = argv[(argc-1)];
    fileName = file; //converting char* file name into string

	//ensuring that min required number of arguments are present

	//error checking for whether or not we were given enough arguments
	if (fileName == " ") {
        cerr << "usage: ./Prog5 [-gray] [-flip] [-lens z] [-bs nbytes] image.ppm" << endl;
		return(1);
	}

    if (argc <= 1) {
        cerr << "usage: ./Prog5 [-gray] [-flip] [-lens z] [-bs nbytes] image.ppm" << endl;
        return(1);
    }

	if (argc > 2) {
		proceed = true;
	}

	//ensuring that final argument is a filename 
	if (fileName.find("ppm")) {
		fileGiven = true;
	}

    for (int h = 0; h < argc; h++) { //commandline arg parsing loop

        if ((strcmp(argv[h], "-bs")) == 0) { //setting blocksize if requested 

            block_size = atoi(argv[h+1]);
			bsGiven = true;
            h++;
        
        }
        
        if ((strcmp(argv[h], "-gray")) == 0) {
            makeGray = true;
        }
        
        if ((strcmp(argv[h], "-flip")) == 0) {
            makeFlip = true;
        }
        
        if ((strcmp(argv[h], "-lens")) == 0) {
        
            rho = atof(argv[h+1]); //converting rho to float when given '-lens' 
            
            if (1.0 < rho && rho <= 2.0) { //ensuring that rho is within correct range
                makeLens = true;
            }
        
            else {
				cerr << "usage: ./Prog5 [-gray] [-flip] [-lens z] [-bs nbytes] image.ppm" << endl; //error message if rho is out of bounds
                return(1);
            }
        }
    }
    
    image.set_bs(block_size); //setting the block size

	if (proceed && fileGiven) { //error checking for invalid mode option even when given a filename
		if (bsGiven == false && makeGray == false && makeFlip == false && makeLens == false) { //if no modifications were inputted, exiting program
			cerr << "usage: ./Prog5 [-gray] [-flip] [-lens z] [-bs nbytes] image.ppm" << endl;
			return(1);
		}
	}
    
    image.read(fileName); 
    
	//applying the appropriate modifications
    if (makeGray) {
           gray(image);
    }
    if (makeFlip) {
           flip(image);
    }
    if (makeLens) {
           lens(image, rho);
    }
    
    image.write(fileName);

    return 0;
}
