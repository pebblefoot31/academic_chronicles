//Nia Maheshwari
//niakmaheshwari@gmail.com
//phone number: (865)-232-7482
//Linux OS
//Terminal 
//Chapter 12 - Exercise 6
//***************************************************************************************************
//Summary + Logic
//The purpose of this program is to create a Time class with a default time constructor and 
//several methods which can work on one (or more) Time objects. This was the most challenging yet 
//equally rewarding assignment so far. Although I did quite a bit of research on creating both classes
//and  class methods (perfecting syntax was quite painful), I was able to debug smoothly near the end,
//which means I learned through the process! Another significant struggle aside from syntax was 
//creating the method which would calculate the difference between two Time objects; at one point, my
//program refused to compile. Thus, I decided to just present the difference in seconds (although a 
//combo of minutes:seconds would be more applicable). That's all! It was a fun class :)
//***************************************************************************************************


#include <iomanip>
#include <iostream>
using namespace std;

class Time // creating the Time class
{
private: // establishing essential private variables which will be used
         // throughout this class
  int minutes;
  int seconds;

public:
  Time(int m = 0, int s = 0); // default constructore
  void setTime(
      int min,
      int sec); // function to set the time to something besides default 00:00
  void observeTime();  // function to print a time object
  void TotalSeconds(); // function to calculate and output the total seconds in
                       // a time object
  void equalTo(
      Time); // function to compare and output the result for two time objects
  void greaterThan(
      Time); // function to compare and output the result for two time objects
  void lessThan(
      Time); // function to compare two and output the result for time objects
  void
  addTime(Time time1,
          Time time2); // function to add two time objects and output the result
  void subtractTime(Time time1, Time time2); // function to subtract two time
                                             // objects and output the result
};

//***********************************Class Methods*********************************//



Time::Time(int m, int s) // defining the Time setting function
{
  minutes = m;
  seconds = s;

  while (seconds >= 60) {
    minutes += (seconds / 60);
    seconds -= 60;
  }
}




void Time::TotalSeconds() // defining a function which calculates + prints the total number of seconds in the set time
{
  cout << "The total seconds are " << ((60 * minutes) + seconds) << " seconds."
       << endl;
}




void Time::observeTime() // defining a function which prints out the time in minutes and seconds
{
  while (seconds >= 60) {
    minutes += (seconds / 60);
    seconds -= 60;
  }

  cout << "The time is " << setw(2) << setfill('0') << minutes << ":" << setw(2)
       << setfill('0') << seconds << "\n";
}




void Time::equalTo(Time otherTime) // defining a function which checks if one time object is equal to another time object
{
  if (minutes == otherTime.minutes && seconds == otherTime.seconds)
    cout << "The times are equal!" << endl;
  else
    cout << "The times are not equal!" << endl;
}




void Time::lessThan(Time otherTime) // defining a function which checks whether one time object is less than another
{
  if (minutes < otherTime.minutes)
    cout << "The time is less!" << endl;
  else
    cout << "The time is not less." << endl;
}



void Time::greaterThan(
    Time otherTime) // defining a function which checks whether one time object is greater than another
{
  if (minutes > otherTime.minutes)
    cout << "The time is greater!" << endl;
  else
    cout << "The time is not greater." << endl;
}




void Time::addTime(
    Time time1, Time time2) //defining a function which adds two time objects
{
  int totalMin;
  int totalSec = time1.seconds + time2.seconds;

  if (totalSec >= 60)
    totalMin = time1.minutes + time2.minutes + (totalSec / 60);
  else
    totalMin = time1.minutes + time2.minutes;

  while (totalSec >= 60)
    totalSec -= 60;

  cout << "The total time is " << totalMin << " minutes and " << totalSec
       << " seconds." << endl;
}




//function to calculat the difference between two time objects in seconds
void Time::subtractTime(Time time1, Time time2) {

  //establishing variables to be used in the method
  int totalDiffInSec; //represents the difference in the time objects but converted to seconds
  int totalSec1; //the total seconds of time1
  int totalSec2; //the total seconds of time 2

  totalSec1 = (time1.minutes) * 60 + time1.seconds; //computing total seconds of time1
  totalSec2 = (time2.minutes) * 60 + time2.seconds; //computing the total seconds of time2

  if (totalSec1 >= totalSec2) {
    totalDiffInSec = (totalSec1 - totalSec2); //the diff.
    cout << "The time difference is " << totalDiffInSec << " seconds." << endl; //printing result
  }

  //repeat of above calculations but with a reversed conditional statment to account for a situation which would otherwise yield a negative number
  else if (totalSec2 > totalSec1) {
    totalDiffInSec = (totalSec2 - totalSec1);
    cout << "The time difference is " << totalDiffInSec << " seconds." << endl;
    }
}



//***************************Main Function**********************************//

int main() {
  //establishing the time
  Time time; //time(9, 120);
  Time otherTime(10, 2);

  //finally testing out all of the class methods!!!!
  time.observeTime();
  time.TotalSeconds();
  otherTime.observeTime();
  otherTime.TotalSeconds();
  time.greaterThan(otherTime);
  time.equalTo(otherTime);
  time.lessThan(otherTime);
  time.addTime(otherTime, time);
  time.subtractTime(otherTime, time);

  return 0;
}