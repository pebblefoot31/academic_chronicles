#include <iostream>
#include <map>

using namespace std;

int main ()
{
  map<char,int> mymap;

  map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it = mymap.find('b');

  if (it != mymap.end()) {
    cout << "Found it in the map. Here it is: " << it->second << endl;
    mymap.erase (it);
  }
/*
  else {
      cout << "Found it in the map. Here it is: " << it->second << endl;
  }*/

  /* print content: 
  cout << "elements in mymap:" << '\n';
  cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';
  */

  return 0;
}
