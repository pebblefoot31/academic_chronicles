#pragma once
#include <vector>
using std::vector;

class isprime {
  bool verbose;
  vector <int> known_primes;

  void expand_known_primes(int);

  public:
  isprime(bool verbose=false);
  bool operator()(int);
};
