//Nia Maheshwari
//UTK COSC 202
//Professor Adam W. Disney

#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include "Support.h"
	

bool location::empty() {

	return geocode.empty();
}


void location::set_geocode(const char *g) {

	geocode = g; 
}


//overloading the == operator to compare geocodes
bool location::operator==(const location& l) {

	if (geocode == l.geocode)
		return true;
	else
		return false;
}


//default constructor
summary::summary() {

	//establishing the values we want to include in each city's summary
	for(int i=0;i<12;i++){
		tot_prec.push_back(0.0);
		max_prec.push_back(0.0);
		min_prec.push_back(100.0);
		max_temp.push_back(0);
		min_temp.push_back(100);
		sum_temp.push_back(0);
		num_reports.push_back(0);
	}
}


//constructor that accepts location as an argument
summary::summary(location &l) {

	station.cityName = l.cityName;
	station.stateName = l.stateName;
	station.geocode = l.geocode;

	for(int i=0;i<12;i++){
		tot_prec.push_back(0.0);
		max_prec.push_back(0.0);
		min_prec.push_back(100.0);
		max_temp.push_back(0);
		min_temp.push_back(100);
		sum_temp.push_back(0);
		num_reports.push_back(0);
	}
}

location& summary::get_station() {
	return station; 
}	


void summary::incorporate_data(const data &d) {
	tot_prec[d.month-1] += d.precipitation;
	if (d.precipitation >= max_prec[d.month-1]) //simple algorithm for determining the max precipitation value
		max_prec[d.month-1] = d.precipitation;
	if (d.precipitation <= min_prec[d.month-1]) //simple alg. for determining the min precipitation value
		min_prec[d.month-1] = d.precipitation;

	//calculating max/min temps similar to how I calculated max/min prec
	if (d.temperature >= max_temp[d.month-1]) 
		max_temp[d.month-1] = d.temperature;
	if (d.temperature <= min_temp[d.month-1])
		min_temp[d.month-1] = d.temperature;

	//calculating the sum of all temperature readings taken during a month at 
	//one location (necessary for correctly calculating avg. temp in the print_data() function)
	sum_temp[d.month-1] += d.temperature;
	num_reports[d.month-1]++;
}


//displaying a heading that provides information with the city name and dashes as a divider
void summary::print_station() {
	for (int i =0; i <42; i++) 
		std::cout << "-";
	std::cout << std::endl;
	std::cout << station.cityName << ", " << station.stateName << " (" << station.geocode << ")" << std::endl;
	for (int i =0; i <42; i++) 
		std::cout << "-";
	std::cout << std::endl;
}


//formatting the output (setting decimal place precision for floats, the number of spaces bw values,
//printing the correct month for each line, and finally outputting the values themselves) 
void summary::print_data() {
	std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	for (int i =0; i <12; i++)
		std::cout << months[i] << ": " << std::fixed << std::setprecision(2) << std::setw(5) << tot_prec[i] << " " << std::setw(5) << tot_prec[i]/num_reports[i] << " " << std::setw(5) << max_prec[i] << " " << std::setw(5) << min_prec[i] << " :  " << sum_temp[i]/num_reports[i] << "  " << max_temp[i] << "  " << min_temp[i] << std::endl; 
}
