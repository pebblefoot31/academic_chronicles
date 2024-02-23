//Nia Maheshwari
//Dr. Jens Gregor
//UTK COSC 302
#pragma once
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

struct location {
  string city;
  string state;
  string geocode;

  bool operator<(const location&) const;
  void print() const; 
};

struct rawdata {
  int month;
  float precip;
  int temp;

  void print() const;
};

struct summary {

  int N;

  float precip_avg;
  float precip_max;
  float precip_min;

  float temp_avg;
  float temp_max;
  float temp_min;

  summary();
  void operator+=(const rawdata&);
  void print();

};

class database {

  public:
    void init_rawdata(const string &fileName);
    void print_rawdata();

    void init_summary();
    void print_summary(const string &target);

  private:
    void extract_rawdata(string&, location&, rawdata&);
    void extract_summary();

    //pt 1
    map<location, int> location_map;
    vector<list<rawdata>> rawdata_cache; 

    //pt 2
    unordered_map<string, set<string>> state_map;
    unordered_map<string,location> geocode_map;
    vector<vector<summary>> summary_cache;
};
