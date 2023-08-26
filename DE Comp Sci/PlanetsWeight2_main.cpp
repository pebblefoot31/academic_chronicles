#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


enum Planet {Mercury,Venus, 
Earth, 
Moon, 
Mars, 
Jupiter, 
Saturn, 
Uranus, 
Neptune, 
Pluto};

int main() {

    float weightOnPlanet;
    float weight;
    string planet;

  cout << "Please enter your weight: " << endl;
  cin >> weight;
  
    cout << "Please indicate your planet by name. The moon is also a viable option in this case: " << endl;
    cin >> planet;
    
  if (planet >= Mercury && planet <= Pluto)
  {
    switch (planet-1)
      {
      case Mercury:
         // weightOnPlanet = weight*0.4155;
          cout << "Your planet is Mercury" << endl;
          break;
      case Venus:
         // weightOnPlanet = weight*0.8975;
          cout << "Your planet is Venus, and your weight on Venus is " << (weight*0.8975) << " lbs."<< endl;
          break;
      case Earth:
          ///weightOnPlanet = weight*1.0;
          cout << "Your planet is Earth" << endl;
          break;
      case Moon:
          //weightOnPlanet = weight*0.166;
          cout << "Your location is the Moon " << endl;
          break;
      case Mars:
          //weightOnPlanet = weight*0.3507;
          cout << "Your planet is Mars" << endl;
          break;
      case Jupiter:
          //weightOnPlanet = weight*2.5374;
          cout << "Your planet is Jupiter" << endl;
          break;
      case Saturn:
          //weightOnPlanet = weight*1.0677;
          cout << "Your planet is Saturn" << endl;
          break;
      case Uranus: 
         // weightOnPlanet = weight*0.8947;
          cout << "Your planet is Uranus."<< endl;
      case Neptune:
          //weightOnPlanet = weight*1.1794;
          cout << "Your planet is Neptune " << endl;
          break;
      case Pluto:
          //weightOnPlanet = weight*0.0899;
          cout << "Your planet is Pluto" << endl;
          //cout << "Your weight on Pluto is: " << weightOnPlanet;
          break;
        }
    }

}
    
     
  // Creating Gender type variable
  //cout << "Please enter the full name of the planet you are on: " << endl;
  //cin >> planet;
  //cout << "Please enter your weight: " << endl;
  //cin >> weight;
  //cout << "Your weight on " << planet << " is " << weightOnPlanet << endl;
