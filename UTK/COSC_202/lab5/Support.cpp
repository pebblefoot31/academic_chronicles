#include <iostream> 
#include <fstream>
#include <cstring> 
#include <string> 
#include <algorithm>
#include <cmath>
#include "Support.h" 

using namespace std;

ppm::ppm() {
	
	//initializing the ppm object variables to what is expected
    magicid = "P6";
    maxvalue = 255;
    Nrow = 0;
    Ncol = 0;
    block_size = 512;
    img = NULL;
}

RGB* ppm::operator[](int i) {

    return &img[i*Ncol]; //useful in navigating the image like it is a 2D array
}

ppm::ppm(const ppm &imgToCopy) {

	//copying source image's header info 
    magicid = imgToCopy.magicid;
    Nrow = imgToCopy.Nrow;
    Ncol = imgToCopy.Ncol;
    maxvalue = imgToCopy.maxvalue;

    //copying each pixel from the original image into the copy 
    img = new RGB[Ncol * Nrow];
    for (int i = 0; i < (Ncol*Nrow); i++) {
        img[i] = imgToCopy.img[i];
    }
}

ppm::~ppm() {
    if (img != NULL) //free up allocated mem
        delete[] img;
}

void ppm::set_bs(int num) {

    block_size = num;
}

void ppm::read(const std::string &fileName) {

    ifstream imageFile;
   
    int numRows;
    int numColumns;
    int inputMaxValue;
    int numBytesRead = 0;
    int totBytes = 0;
    string inputMagicID;

    imageFile.open(fileName.c_str());

    if (!imageFile) { //only proceed if the file opened properly
        cerr << "ppm::read: cannot open " << fileName << endl;
        exit(1);
    }

    //reading the header
    imageFile >> inputMagicID >> numColumns >> numRows >> inputMaxValue; //gotta make sure that I'm reading in the num of rows and columns in the right order from the header of the ppm file

    while (imageFile.get() != '\n'); //reading until the end of the header

    //error checking
    if (inputMagicID != magicid) {
        cerr << "ppm::read: magicid " << inputMagicID <<  " not supported" << endl;
        exit(1);
    }

    if (inputMaxValue != maxvalue) {
        cerr << "ppm::read: maxvalue " << inputMaxValue << " not supported" << endl;
        exit(1);
    }

    Ncol = numColumns;
    Nrow = numRows;

    totBytes = (Ncol*Nrow)*sizeof(RGB);
    img = new RGB[Ncol * Nrow];
    int i = 0;

    while (true) {

        imageFile.read((char *)img + i, block_size); //reading image in the block_size chunks
        i += block_size;
        numBytesRead += imageFile.gcount(); //keeping track of the bytes read for error checking later on

        if (imageFile.eof() || imageFile.gcount() == 0) { //exit if the file is either corrupted or if we have reached the end
            break;
        }
    }

	//error checking to make sure that we have read the right number of bytes
    if (totBytes != numBytesRead) {
        cerr << "ppm::read: expected " << totBytes << " but read " << numBytesRead << " bytes" << endl;
        exit(1);
    }
    
    imageFile.close(); 
}

void ppm::write(const std::string &fileName) {

    string newFileName = fileName;

    int totBytes = (Ncol*Nrow)*sizeof(RGB);
    int bytesWritten = 0;

	//creating a copy file that will have the modified data
    size_t suffixIndex = newFileName.rfind(".ppm");
    newFileName.insert((suffixIndex), "_mod");

    ofstream modImageFile; 
    modImageFile.open(newFileName.c_str());

    if (!modImageFile) { //only proceed if the file opened properly
        cerr << "write: error in opening file." << endl;
        exit(1);
    }
  
   //write header
    modImageFile << magicid << endl;
    modImageFile << Ncol << " "<< Nrow << endl;
    modImageFile << maxvalue << endl;

   //write image (block size) 
    int j = 0;
    while (true) {

        if ((totBytes - bytesWritten) < block_size) {
            modImageFile.write((char *)img + j, totBytes-bytesWritten);
            break;
        }

        modImageFile.write((char *)img + j, block_size);
        j += block_size;
        bytesWritten += block_size; 
    }
    
    modImageFile.close();
}

void gray(ppm &img) {

    int nRow = img.get_Nrow(); 
    int nCol = img.get_Ncol(); 

    float R = 0.0;
    float G = 0.0;
    float B = 0.0;

	//grayscaling pixel by pixel
    for (int r = 0; r < nRow; r++) { //this nested for loop demonstrates iterating through a 2D array row by row 
        for (int c = 0; c < nCol; c++) {

            R = img[r][c].R;
            G = img[r][c].G;
            B = img[r][c].B;

            float Y = (R + G + B)/3;
			
            img[r][c].R = (uint8_t)Y;
            img[r][c].G = (uint8_t)Y;
            img[r][c].B = (uint8_t)Y;
        }
    }

}

void flip(ppm &img) {

    int totCols = img.get_Ncol();
    for (int r = 0; r < img.get_Nrow(); r++) {
        for (int c = 0; c < (totCols/2); c++) {
            swap(img[r][c], img[r][totCols-1-c]); //swapping pixels row by row to flip the image across a vertical axis
        }
    }
}

void lens(ppm &img, float rho) {

    float row = img.get_Nrow(); 
    float col = img.get_Ncol();

    float centerRow = row/2.0;
    float centerCol = col/2.0;

    float rmax = min(centerRow, centerCol);

    ppm img_copy = img;
	
	//applying the necessary mathematical procedures for the lens function
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {

			float r1 = r-centerRow;
			float c1 = c-centerCol;
			float rad = sqrt((r1*r1)+(c1*c1));

			if (rad < rmax) {
              
				float z = sqrt((rmax*rmax) - (rad*rad));

				float r2 = (r1/sqrt((r1*r1)+(z*z)));
				float c2 = (c1/sqrt((c1*c1)+(z*z)));

				float r3 = (1.0-1.0/rho)*(asin(r2)); //value of rho adjusts the effect of -lens
				float c3 = (1.0-1.0/rho)*(asin(c2)); 

				int r4 = ((int)(r-z*tan(r3)+0.5));
				int c4 = ((int)(c-z*tan(c3)+0.5));

				img[r][c] = img_copy[r4][c4];

			} 
		} 
	} 
}



