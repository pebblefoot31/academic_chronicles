//Nia Maheshwari
//UTK COSC 202
//Professor Adam W. Disney

#include <iostream>
#include <sstream>
#include <ctype.h>
#include <vector>
#include "Support.h"


void extract_values(std::string& line, location& l, data& d) {

	std::stringstream myStream;
	myStream << line;
        myStream >> d.month >> l.cityName >> l.stateName >> l.geocode >> d.precipitation >> d.temperature;   
	myStream.str("");
}


int main(int argc, char* argv[]) { //this line will allow for the station geocode (or lack thereof) to be determined via the terminal

	std::vector<summary> summaries;
	location loc;
	data dat;
	std::string line;	
	bool found; //a flag created to help determine (in a later loop) whether or not the summary object for 
				//a certain station containing weather data has already been added to the summaries vector  


	if (argc > 2) {
		std::cerr << "usage: "<< argv[0] <<" [geocode] < datafile" << std::endl; //error message if multiple geocodes (or too many argumentS) are inputted
		return 1;
	}

	//read stdin from terminal
	while (getline(std::cin, line)) {


		//parse the weather file line by line and perform appropriate substitutions
		for (size_t i = 0; i < line.length(); i++) {
		

			if (isspace(line[i])) //isspace function used to quickly identify space char
				line[i] = '_';
			if (line[i] == ',')
				line[i] = ' ';
		}


		extract_values(line, loc, dat);	

		if (summaries.size() == 0) { //add an element if the summary vector is empty
			summary s(loc);
			s.incorporate_data(dat);
			summaries.push_back(s);
		} 
		else {
			found = false;

			for (size_t i = 0; i < summaries.size(); i++) {
				
				//if the geocode being passed is already present as an element in the vector, 
				//append the data to the existing summary object with the matching geocode 
				//rather than creating a new summary object in the summaries vector
				if (summaries[i].get_station() == loc) { 
					summaries[i].incorporate_data(dat);
					found = true;
				}
			}

			if (found == false) {
				summary s(loc);
				s.incorporate_data(dat);
				summaries.push_back(s);
			}
		}
		
	}
	
	if (argc == 2) { //displaying weather data for the requested station (via inputted geocode)

		for (size_t i = 0; i < summaries.size(); i++) {
			if (summaries[i].get_station().geocode == argv[1]) {
				
				summaries[i].print_station();
				summaries[i].print_data();
			}
		}
	} 
	else { //display weather data for ALL stations if no geocode is provided
		for (size_t i = 0; i < summaries.size(); i++) {
			summaries[i].print_station();
			summaries[i].print_data();
		}

	}

	return 0;
}

