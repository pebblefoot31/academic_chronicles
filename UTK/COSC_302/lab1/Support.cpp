//Nia Maheshwari
//Dr. Jens Gregor
//UTK COSC 302
#include "Support.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

//location struct functions
bool location::operator<(const location& l) const { //overloading the operator to sort first by state, and then by city 

    if (state < l.state) {
        return true;
    }

    else if (state == l.state && city < l.city) {
        return true;
    }
    return false;
}

void location::print() const {

    for (int i = 0; i < 42; i++) {
        cout << "-";
    }
    cout << endl;
    cout << city << ", " << state << " (" << geocode << ")" << endl;

    for (int i = 0; i < 42; i++) {
        cout << "-";
    }
    cout << endl;
}

//rawdata struct functions
void rawdata::print() const {

    cout << setw(5) << setfill(' ') << month << fixed << setfill(' ') << setprecision(2); 
    cout << setw(6) << precip << " " << setw(5) << temp << endl;

}

//summary member functions
summary::summary() { 

	//summary constructor-- initializes the member data values

    N = 0;
 
    precip_avg = 0.0;
    precip_max = 0.0;
    precip_min = 100.0; //making min value very large so that whatever rawdata is
						//encountered first becomes the the minimum value 
    
    temp_avg = 0.0;
    temp_max = 0.0;
    temp_min = 100.0;

}

//summary member functions
void summary::operator+=(const rawdata& r) {

    N += 1; //incrementing the number of weeks reported 
			//for a particular month

    precip_avg += r.precip; //storing the sums for avg values
    temp_avg += r.temp;

    if (r.precip >= precip_max) {//algorithm for determining the max precipitation value
		 precip_max = r.precip;
    }

    if (r.precip <= precip_min) {  //algorithm for determining the min precipitation value
		 precip_min = r.precip;
    }

    //calculating max/min temps similar to how max/min prec was determined
	if (r.temp >= temp_max) {
	    temp_max = r.temp;	
    }

	if (r.temp <= temp_min) {
	    temp_min = r.temp;	
    }
}

void summary::print() { //code for printing a summary object's data members and formatting them 

    cout << ": " << fixed << setprecision(2) << setw(5) << precip_min << " " << setw(5); 
	cout << precip_max << " " << setw(5) << precip_avg << " : " << setprecision(1) << setw(5) << temp_min << "  ";
	cout << temp_max << "  " << temp_avg << endl;

}


//write database member functions
void database::print_rawdata() {

    map<location, int>::iterator currentLoc;
    currentLoc = location_map.begin(); //start at the beginning of the location map

    while (currentLoc != location_map.end()) { //iterate through entire location map

        currentLoc->first.print();

        list<rawdata> locDataList; 
        locDataList = rawdata_cache[currentLoc->second]; //indexing into the list of rawdata for location obj

        list<rawdata>::iterator rawdataIt; //iterator for the rawdata list
        rawdataIt = locDataList.begin(); 
        
        while (rawdataIt != locDataList.end()) { //iterate list and output the rawdata for location

            rawdataIt->print(); 
            rawdataIt++;
        }

        currentLoc++;
    }
}

void database::extract_rawdata(string& line, location& l, rawdata& r) { //cleaning data, populating rawdata member variables

    stringstream dataStream;
 
    //replacing spaces with underscores and commas with spaces line by line
    for (size_t i = 0; i < line.length(); i++) {

        if (isspace(line[i])) //isspace function used to quickly identify space char
                line[i] = '_';
            if (line[i] == ',')
                line[i] = ' ';
     }

	//using a stringstream to extract the data from each incoming line (after it is cleaned) and populating data variables
     dataStream << line;
     dataStream >> r.month >> l.city >> l.state >> l.geocode >> r.precip >> r.temp;
     dataStream.str("");
}

void database::init_rawdata(const std::string &fileName) { //populating the cache of rawdata

    ifstream dataFile;

    //location and rawdata struct objects
    location dataLoc;
    rawdata dataVals;
    string line;
    int indexVal = 0;

	//error checking the file
    dataFile.open(fileName.c_str());

    if (!dataFile) { //only proceed if file opened properly
        cerr << "error: cannot open " << fileName << endl;
		cerr << "usage: ./Prog1 [-rawdata] datafile" << endl;
        exit(1);
    }

    map<location,int>::iterator locFinder;

    while (getline(dataFile, line)) { //parsing data file line by line to build location_map
 
        extract_rawdata(line, dataLoc, dataVals); //populating the rawdata and location obj variables
        
        locFinder = location_map.find(dataLoc);

        if (locFinder == location_map.end()) { //if location does not already exist in the map

			location_map.insert(pair<location, int>(dataLoc, indexVal)); //creating new element in location_map

			list<rawdata> weeklyLocationData;
            rawdata_cache.push_back(weeklyLocationData);

            rawdata_cache[indexVal].push_back(dataVals); //inserting rawdata val into the list at index in the vector corresponding with the location
            indexVal++; //updating the index value 
		 } 

		else { //location does exist

            rawdata_cache[locFinder->second].push_back(dataVals); //push dataVals at the index corresponding to the existing (matching) location obj
		}
	}
}

void database::print_summary(const string &target) {

	queue<string> locToPrint;
	bool targetStatus = true;

	unordered_map<string, set<string>>::iterator stateFinder;
	stateFinder = state_map.begin();
	set<string>::iterator setIt;

	unordered_map<string,set<string>>::iterator stateSearcher; //iterator to look for the target in state_map

	//checking if we're given a state
	stateSearcher = state_map.find(target);

	if (stateSearcher == state_map.end()) { //not found in state map

		unordered_map<string,location>::iterator geoSearcher; //iterator to look for the target in geocode_map
		geoSearcher = geocode_map.find(target);

		if (geoSearcher != geocode_map.end()) { //found in geocode_map
			
			locToPrint.push(geoSearcher->first);
		}

		else {

			targetStatus = false; //target likely does not exist in database
		}
	}

	else { //target is a state

		setIt = stateSearcher->second.begin();

		while (setIt != stateSearcher->second.end()) { //iterator through its set of geocodes

			locToPrint.push(*setIt); //adding geocode to queue
			setIt++;
		}
	}

	if (!targetStatus) { //target does not exist

		cout << "Target not found!" << endl;
	}

	//printing out queue 
	map<location,int>::iterator locFinder;
	locFinder = location_map.begin();

	//vector of months for printing purposes
	string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; 


	while (!locToPrint.empty()) { //traverse queue of goecodes until empty
		
		locFinder = location_map.begin();

		while (locFinder != location_map.end()) {
			
			if (locToPrint.front() == locFinder->first.geocode) { //finding location obj that corresponds to geocode
				
				locFinder->first.print();

				for (size_t s = 0; s < 12; s++) { //iterating through summaries at this loc's index in summary_cache from Jan-Dec

					cout << months[s]; 
					summary_cache[locFinder->second][s].print();

				}

				locToPrint.pop(); //popping that geocode from queue 
			}

			locFinder++;
		}

	}

}

void database::init_summary() {

    map<location,int>::iterator locFinder;
    locFinder = location_map.begin();

    unordered_map<string, set<string>>::iterator stateFinder;

    //building the state_map
	if (state_map.empty()) { //initializing state_map with first location
		
			set<string> geocodeSet;
            state_map.insert(make_pair(locFinder->first.state, geocodeSet));
            geocodeSet.insert(locFinder->first.geocode);

			stateFinder = state_map.begin(); //set the state_map iterator to the beginning of the map once it is initialized
	}
	
	unordered_map<string,set<string>>::iterator stateFound; //iterator to look for the state in state_map
    while (locFinder != location_map.end()) { //iterating through all the location objects to build state_map.

		stateFound = state_map.find(locFinder->first.state);

		if (stateFound == state_map.end()) { //if state does not exist in state_map 

			//create new key/value in the state_map and populate the geocode set
			set<string> geocodeSet;
			geocodeSet.insert(locFinder->first.geocode); 
			state_map.insert(make_pair(locFinder->first.state, geocodeSet));
		}

		else { //if state already exists in state_map

			//updating the existing geocode set corresponding to the state
            state_map[stateFound->first].insert(locFinder->first.geocode); 
		}

		locFinder++;
	}

	locFinder = location_map.begin();

    //building the geocode_map
    while (locFinder != location_map.end()) {

        //make new pair in the geocode_map with every location obj
        geocode_map.insert(make_pair(locFinder->first.geocode, locFinder->first));
		locFinder++;
    }

	extract_summary(); //calling extract_summary (will populate summary_cache)
}


void database::extract_summary() {

    map<location,int>::iterator locFinder;
    locFinder = location_map.begin();
    list<rawdata>::iterator rawdataIt; //iterator to traverse through the list of rawdata for a particular location
	int month = 1;

	while (locFinder != location_map.end()) { //allocating space in the first index of summary_cache 

         vector<summary> dummyVector; 
         summary_cache.push_back(dummyVector);

		locFinder++;
	}

	locFinder = location_map.begin();

    while (locFinder != location_map.end()) { //traversing location_map

		while (month < 13) { //extracting weekly data by month starting at January

			rawdataIt = rawdata_cache[locFinder->second].begin(); //traversing the weekly data for every obj in the location_map

			summary monthSum; //creating an instance of summary for each month

			while (rawdataIt != rawdata_cache[locFinder->second].end()) {

				if (rawdataIt->month == month) {

					monthSum += *rawdataIt; //updating the summary for a month
				}

				rawdataIt++;
			}
		
			//computing average values
            monthSum.precip_avg = monthSum.precip_avg/monthSum.N; 
            monthSum.temp_avg = monthSum.temp_avg/monthSum.N;
		
            summary_cache[locFinder->second].push_back(monthSum); //pushing back the summary for each month of this location to the corresponding index 
			month++;
		}

		locFinder++;

		month = 1;

	}

}
