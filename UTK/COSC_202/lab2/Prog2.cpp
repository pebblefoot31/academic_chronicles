#include <iostream>
#include <sstream>
#include <string>
#include "Support.h"

//void extract_values(string &text, location &n_station, data &n_data) {
void extract_values(std::string& line, location& l, data& d) {
    std::stringstream myStream;
    myStream << line;
    myStream >> d.month >> l.city >> l.state >> l.geocode >> d.precip >> d.temp;
    myStream.str("");
}


int main(int argc, char *argv[])
{
  if (argc != 1 && argc != 2) {
      std::cerr << "usage: " << argv[0] << " [location] < datafile\n";
    return 1;
  }

  char *target_location = NULL;
  if (argc == 2)
    target_location = argv[1];

  list city_list; // this will invoke appropriate chain of constructors

  std::string n_text;
  location n_station;
  data n_data;

  while (getline(std::cin, n_text)) {
    
      for (int i = 0; i < n_text.length(); i++) {
        if (isspace(n_text[i])) //isspace function used to quickly identify space char
            n_text[i] = '_';
        if (n_text[i] == ',')
            n_text[i] = ' ';
    }
    extract_values(n_text, n_station, n_data);
    city_list.insert(n_station, n_data);
  }

  city_list.print(target_location);

  return 0;

}
