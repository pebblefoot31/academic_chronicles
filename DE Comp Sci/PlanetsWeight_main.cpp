#include <iostream>
#include <string>
using namespace std;


//creating an Enum type
enum Planet {Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto};

int main() {

  //establishing variables to retain siginificant values throughout the program
  float weight;
  int planet;
  bool flag;


  //obtaining user's weight on Earth through simple cin + cout statements
  cout << "Please enter your weight in lbs. You may use one or two decimal places: " << endl;
  cin >> weight;
  
  //determining the planet that the user wants to travel to, with 1 indicating Mercury and 10 indication Pluto
  cout << "Please indicate a planet by number (range 1-10, including the moon) in relation to distance from the sun. For instance, if you choose to be on Mercury, you would enter '1' as it is the closest to the sun. Venus would be '2', and so on. The Moon is also a viable option: please enter 4' for the moon. Enter the corresponding number for the planet you want to know your weight on: " << endl;
    cin >> planet;

  
  //ensuring that the chosen planet is within the range of numbers that can correspond to planets within our solar system (1-10)
  while (planet < (Mercury+1) || planet > (Pluto+1)) {
    flag = false;
    cout << "Please try again and make sure to enter a number within the range of the planets in our solar system: " << endl;
        cin >> planet;
        if (planet >= Mercury && planet <= Pluto)
          flag = true;
        }

  if (flag)   //conditional statement to enter the 'switch' code which computes and outputs the user's weight based on their chosen planet
    {
      switch (planet-1)
        {
        case Mercury:
          cout <<"Your location: Mercury \t \t Your weight: " << (weight*0.4155) << " lbs."<< endl;  //purpose of the tabs is to have a cleaner output
          break;
        case Venus:
          cout << "Your location: Venus \t \t Your weight: " << (weight*0.8975) << " lbs."<< endl;
          break;
        case Earth:
          cout << "Your location: Earth \t \t Your weight: " << (weight*1.0) << " lbs."<< endl;
          break;
        case Moon:
          cout << "Your location: the Moon \t \t Your weight: " << (weight*0.166) << " lbs."<< endl;
          break;
        case Mars:
          cout << "Your location: Mars \t \t Your weight: " << (weight*0.3507) << " lbs."<< endl;
          break;
        case Jupiter:
          cout << "Your location: Jupiter \t \t Your weight: " << (weight*2.5374) << " lbs."<< endl;
          break;
        case Saturn:
          cout << "Your location: Saturn \t \t Your weight: " << (weight*1.0677) << " lbs."<< endl;
          break;
        case Uranus: 
          cout << "Your location: Uranus \t \t Your weight: " << (weight*0.8947) << " lbs."<< endl;
          break;
        case Neptune:
          cout << "Your location: Neptune \t \t Your weight: " << (weight*1.1794) << " lbs."<< endl;
          break;
        case Pluto:
          cout << "Your location: Pluto \t \t Your weight: " << (weight*0.0899) << " lbs."<< endl;
          break;
        }
    }
 
}