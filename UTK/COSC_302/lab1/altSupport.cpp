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
 11 
 12 using namespace std;
 13 
 14 //write location member functions
 15 bool location::operator<(const location& l) const { //overloading the operator to sort first by state, and then by city name
 16 
 17     if (state < l.state) {
 18         return true;
 19     }
 20 
 21     else if (state == l.state && city < l.city) {
 22         return true;
 23     }
 24 
 25     return false;
 26 
 27 }
 28 
 29 void location::print() {
 30 
 31     for (int i = 0; i < 42; i++) {
 32         cout << "-";
 33     }
 34     cout << endl;
 35 
 36     cout << city << ", " << state << " (" << geocode << ")" << endl;
 37 
 38     for (int i = 0; i < 42; i++) {
 39         cout << "-";
 40     }
 41 
 42     cout << endl;
 43 }
 44 
 45 //write rawdata member functions
 46 void database::print_rawdata() {
 47 
 48     map<location, int>::iterator locPrinter;
 49     locPrinter = location_map.begin(); //start at the beginning
 50 
 51     while (locPrinter != location_map.end()) {

 53        cout << locPrinter->first.state << endl;
 54 
 55         locPrinter++;
 56     }
 57 }
 58 
 59 //write summary member functions
 60 /*
 61 summary::summary() {
 62 }
 63 
 64 void summary::operator+() {
 65 }
 66 
 67 void summary::print() {
 68 }
 69 */
 70 
 71 //write database member functions
 72 void database::extract_rawdata(const string &fileName) {
 73 
 74     ifstream dataFile;
 75     stringstream myStream;
 76     string text;
 77 
 78     dataFile.open(fileName.c_str());
 79 
 80     if (!dataFile) { //only proceed if the file opened properly
 81         cerr << "error opening file." << endl;
 82         exit(1);
 83     }
 84 
 85     while (getline(dataFile, text)) {
 86 
 87         //replacing spaces with underscores and commas with spaces line by line
 88         for (int i = 0; i < text.length(); i++) {
 89 
 90             if (isspace(text[i])) //isspace function used to quickly identify space char
 91                 text[i] = '_';
 92             if (text[i] == ',')
 93                 text[i] = ' ';
 94         }
 95 
 96     }

 98     dataFile.close();
 99 }
100 
101 
102 void database::init_rawdata(const std::string &fileName) {
103 
104     ifstream dataFile;
105 
106     //location and rawdata struct objects
107     location dataLoc;
108     rawdata dataVals;
109 
110     bool cityExists = false;
111 
112     string text;
113     int monthData;
114     string currentCity;
115     string nextCityData;
116     string stateData;
117     string geocodeData;
118     float precipData;
119     int tempData;
120     int indexVal = 0;
121     stringstream dataStream;
122 
123     dataFile.open(fileName.c_str());
124 
125     if (!dataFile) { //only proceed if the file opened properly
126         cerr << "error opening file." << endl;
127         exit(1);
128     }
129 
130     while (getline(dataFile, text)) {
131 
132         extract_rawdata(dataFile);
133 
134         dataStream << text;
135         dataStream >> monthData >> currentCity >> stateData >> geocodeData >> precipData >> tempData;
136 
137         dataLoc.state = stateData;
138         dataLoc.city = currentCity;
139         dataLoc.geocode = geocodeData;
140 
141         dataVals.month = monthData;
142         dataVals.precip = precipData;
143         dataVals.temp = tempData;
144 
145 
146         map<location,int>::iterator locFinder;
147         locFinder = location_map.find(dataLoc);
148 
149         if (locFinder != location_map.end()) { //if the location does not already exist, we will create a new element in the binary tree
150 
151             location_map.emplace(dataLoc, indexVal);
152             indexVal++; //update index value //put the rawdata thing into the matching index in the vector???
153 
154             rawdata_cache[indexVal].push_back(dataVals);
155 
156         }
157 
158         else {
159 
160             rawdata_cache[locFinder->second].push_back(dataVals); //insert the dataVals at the index that the iterator returns 
161         }
162 
163     }
164 
165         //something with location_map and geocode_map;
166       /*  for (int i = 0; i < rawdata_cache.size(); i++) {
167 
168             if (rawdata_cache[i] == currentCity) {
169                 cityExists = true;
170                 rawdata_cache[i].push_back(dataVals);
171             }
172 
173         }
174 
175         if (!cityExists) {
176             
177             for (int i = 0; i < rawdata_cache.size(); i++) {
178 
179                 if (currentCity < rawdata_cache[i]) {
180                     rawdata_cache.push_back(currentCity);
181                     rawdata_cache[i].push_back(dataVals);
182                     break;
183                 }
184 
185             }
186         }
187 
188     }*/
189 }
190 
191 /*
192 void print_summary(target)
193 void init_summary()
194 void extract_summary();
195 */
