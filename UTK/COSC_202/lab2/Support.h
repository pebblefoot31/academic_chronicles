#include <string> 

struct location {
  std::string city;
  std::string state;
  std::string geocode;

  bool operator<(const location &) const;
  bool operator==(const location &) const;
  bool operator==(const std::string &) const;
};


struct data {
  int month;
  float precip;
  int temp;
};


class list {
  struct node {
    node(const location &n_station = location());
    ~node();

    void print_station();
    void print_data();

    location station;

    int *N;

    float *total_precip;
    float *max_precip;
    float *min_precip;

    int *total_temp;
    int *max_temp;
    int *min_temp;

    node *next;
  };

  public:
    list();
    ~list();

    void insert(const location &, const data &);
    void print(const char *); // if user enters city name, figure out that city's geocode and invoke node's print functions

  private:
    node *head;
};
