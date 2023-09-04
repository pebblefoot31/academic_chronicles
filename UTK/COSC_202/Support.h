//Nia Maheshwari
//UTK COSC 202
//Professor Adam W. Disney

#include <vector>
#include <string>

struct location {
	std::string geocode;
	std::string cityName;
	std::string stateName;

	bool empty();
	void set_geocode(const char *);
	bool operator==(const location&);
};

//establishing a data struct for the variables which hold numerical values.
//This distinguishes them from the string variables (as found in the location struct)
struct data {
	int month;
	int temperature;
	float precipitation;
};


class summary {

//the purpose of this section of the summary class is to provide a blueprint-like 
//format for the arrays of values that need to be calculated for each station
private:
	location station;
	std::vector<float> tot_prec;
	std::vector<float> max_prec;
	std::vector<float> min_prec;
	std::vector<int> max_temp;
	std::vector<int> min_temp;
	std::vector<int> sum_temp;
	std::vector<int> num_reports; //vector array for weekly weather reports	

//the purpose of this section of the summary class is to create the 
//appropriate signatures for the necessary member functions
public:
	summary();
	summary(location &);
	location& get_station();
	void incorporate_data(const data &);
	void print_station();
	void print_data();
};

