#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {

  //establishing input variables such as price of vehicle, the vehicle's down payment, the trade in value, loan amount, and the annual interest rate
  float price;
  float downPayment;
  float tradeIn;
  float loanAmt;
  float annualIntRate;
  float annualIntPercent;
  float monIntRate;
  float monPayment;
  int noMonths = 12;  //starting value for the number of months
  int multiple = 2;  //value used to calculate the number of months for increasing number of years


  
  //obtaining the price of the vehicle
  cout << "Please enter the price of the vehicle: " << endl;
    cin >> price;
  //loop to ensure that price meets criteria
  while (price < 50.00 && price > 50000.00) {
    cout << "Please enter the price of the vehicle in dollars and cents: "
         << endl;
    cin >> price;
  }

  
  //obtaining the trade in valeu
  cout << "Please enter the trade-in value of the vehicle in dollars and cents.: "
       << endl;
  cin >> tradeIn;
  //loop to ensure that trade in value is a number greater than 0 and less than the price
  while (tradeIn < 0 && tradeIn > price) {
    cout << "Please enter the trade-in of the vehicle in dollars and cents: "
         << endl;
    cin >> tradeIn;
  }

  
  //obtaining the down payment of the vehicle
  cout << "Please enter the down payment of the vehicle: " << endl;
  cin >> downPayment;
  //the downpayment must meet the following criteria to escape the loop
  while (downPayment < 0 && downPayment > (price - tradeIn)) {
    cout << "Please enter the trade-in of the vehicle in dollars and cents: "
         << endl;
    cin >> tradeIn;
  }


  //obtaining interest rate of the vehicle
  cout << "Please enter the annual interest rate of the vehicle as a percentage converted to a decimal. For instance, an interest rate of 7% would translate to a decimal entry of 0.07: " << endl;
  cin >> annualIntRate;
  //loop to ensure that value entered is a percentage converted to a decimal
  while (annualIntRate > 1) {
    cout << "Please enter a percentage converted to a decimal: " << endl;
    cin >> annualIntRate;
  }


    
  //calculating the monthly interest rate
  monIntRate = annualIntRate / 12.0;


  //calculating the annual interest rate
  annualIntPercent = annualIntRate * 100.0;

  //calculating the loan amount
  loanAmt = price - downPayment - tradeIn;


  //outputting calculations and such values as a form of confirmation
  cout << "\n" << "Honest Dave's Used Cars"  << "\n" << endl;
  cout << "Vehicle Price " << fixed << setprecision(2) << setw(25) << price << endl;
  cout << "Trade in value " << fixed << setprecision(2) << setw(24) << tradeIn << endl;
  cout << fixed << setw(39) << "--------" << endl;
  cout << "Down Payment " << fixed << setprecision(2) << setw(26) << downPayment << "\n" << endl;
  cout << "Loan Amount " << fixed << setprecision(2) << setw(27) << loanAmt << "\n" << endl;
  cout << "Annual Interest Rate " << fixed << setprecision(2) << setw(18) << annualIntPercent << "%" << "\n" << endl;


  //header to the monthly payment options
  cout << "Monthly payment options: " << endl;

  //loop that will print out the monthly payment options by computing them using the following formula and spacing them out evenly. Number of months will be displayed to the left of the actual payment amount
  for (int count = 0; count < 5; count++) {
    monPayment = (loanAmt * monIntRate) / (1.0 - pow((1.0 + monIntRate), -noMonths));
    cout << noMonths << " months " << fixed << setprecision(2) << setw(30) << monPayment << endl;
    noMonths = 12*multiple;
    multiple ++;
  }
}