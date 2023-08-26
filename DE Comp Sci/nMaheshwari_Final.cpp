#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Nia Maheshwari
//niakmaheshwari@gmail.com
//phone number: (865)-232-7482
//Linux OS
//Terminal 
//Semester Final
//***************************************************************************************************
//Summary + Logic
//The purpose of this program is to create a program to calculate the monthly payment of a certain 
//car based on the given price, loan, interest rate, and down payment values, This is just like the
//midterm prograrm but instead of a large, complicated main function, this program operates based on 
//a module of several individual functions working cohesively when called one after the other in the
//main function. Truly, this was quite challenging-- especially when it came to dealing with various
//data types and outputs regarding the many function definitions. I overcame a calculation-based challenge 
//by using a simple print statement to isolate and identify the problem.  
//***************************************************************************************************



//*******************Various Computational Functions***********************

//function to get price of the car
float getPrice() {
  //obtaining the price of the vehicle
  float vehiclePrice;  
  cout << "Please enter the price of the vehicle: " << endl;
      cin >> vehiclePrice;
  //loop to ensure that price meets criteria
    while (vehiclePrice > 48500.00 && vehiclePrice < 75.00) {
      cout << "Please enter the price of the vehicle in dollars and cents: " << endl;
      cin >> vehiclePrice;
       }
  return vehiclePrice;
  }



//--------------------------------------------------------------------//

//function to get trade in value
float getTradeIn(float price) {
  float tradeInVal;
  //obtaining the trade in value
    cout << "Please enter the trade-in value of the vehicle in dollars and cents.: "
         << endl;
    cin >> tradeInVal;
  //loop to ensure that trade in value is a number greater than 0 and less than the price
    while (tradeInVal < 0 && tradeInVal > price) {
      cout << "Please enter the trade-in of the vehicle in dollars and cents: "
           << endl;
      cin >> tradeInVal;
    }
  return tradeInVal;  
}



//------------------------------------------------------------------------//

float getDownPayment(float price, float trade) {
  float downPaymentVal;
  
//obtaining the down payment of the vehicle
  cout << "Please enter the down payment of the vehicle: " << endl;
  cin >> downPaymentVal;
  //the downpayment must meet the following criteria to escape the loop
  while (downPaymentVal < 0 && downPaymentVal > (price - trade)) {
    cout << "Please enter the trade-in of the vehicle in dollars and cents: " << endl;
    cin >> trade;
   }
  return downPaymentVal;
  return trade;
}

//-----------------------------------------------------------------//

//function to obtain the interest rate
float getInterestRate() {
  float annualInterestDecimal;
  //obtaining interest rate of the vehicle
    cout << "Please enter the annual interest rate of the vehicle as a percentage converted to a decimal. For instance, an interest rate of 7% would translate to a decimal entry of 0.07: " << endl;
    cin >> annualInterestDecimal;
  //loop to ensure that value entered is a percentage converted to a decimal
    while (annualInterestDecimal > 1) {
      cout << "Please enter a percentage converted to a decimal: " << endl;
      cin >> annualInterestDecimal;
    }
  return annualInterestDecimal;
}

//--------------------------------------------------------------//


//function to calculate the loan amount
float loanAmount(float downPayment, float tradeIn, float price) { 
  return (price - downPayment - tradeIn);  
}

//--------------------------------------------------------------//

//calculating the annual interest rate
float annualInterestRate(float annualIntDecimal) {
  return (annualIntDecimal * 100.0);
}

//--------------------------------------------------------------//

//function to calculate the monthely interest rate
float monthlyInterestRate(float annualIntRate) {
  return (annualIntRate / 12.0);
}

//--------------------------------------------------------------//

//loop that will print out the monthly payment options by computing them using the following formula and spacing them out evenly. Number of months will be displayed to the left of the actual payment amount
float *calcMonPayment(float loanAmt, float monIntRate) {
   static float monthPayments[5];
   int months = 12;
   int multiple = 2;
   for (int count = 0; count < 5; count++) {
      monthPayments[count] = ((loanAmt*monIntRate)/ (1.0 - (pow((1.0 + monIntRate), -(months)))));
      months = 12*multiple;
      multiple++;
   }
    return monthPayments;
  }


//--------------------------------------------------------------//


//an extra function meant to printout the extra information right before monthly payments
void displayAdditionalInfo(float carPrice, float tradeIn, float downPay, float loan, float annualIntRate) {
  cout << "\n" << "Honest Dave's Used Cars"  << "\n" << endl;
    cout << "Vehicle Price " << fixed << setprecision(2) << setw(25) << carPrice << endl;
    cout << "Trade in value " << fixed << setprecision(2) << setw(24) << tradeIn << endl;
    cout << fixed << setw(39) << "--------" << endl;
    cout << "Down Payment " << fixed << setprecision(2) << setw(26) << downPay << "\n" << endl;
    cout << "Loan Amount " << fixed << setprecision(2) << setw(27) << loan << "\n" << endl;
    cout << "Annual Interest Rate " << fixed << setprecision(2) << setw(18) << annualIntRate << "%" << "\n" << endl;
    cout << "Monthly payment options: " << endl;
  
}

//--------------------------------------------------------------//

//display the monthly payments
void displayLoanSchedule(float payments[5]) {
  int months = 12;
  float multiple = 2.0;
  for (int count = 0; count < 5; count++) {
      cout << months << " months " << fixed << setprecision(2) << setw(30) << payments[count] << endl;
      months = 12*multiple;
      multiple ++;
    }
}

//***********************************Main Function*************************************

int main() {
  
  //calling the various functions in correct execution order
  //this part necessitated a few global vars for parameter purposes in later functions
  float carPrice = getPrice();
  float tradeIn = getTradeIn(carPrice);
  float downPay = getDownPayment(carPrice, downPay);
  float intRate = getInterestRate();
  float monthlyIntRate = monthlyInterestRate(intRate);
  float annualIntRate = annualInterestRate(intRate);
  float loan = loanAmount(downPay, tradeIn, carPrice);

  displayAdditionalInfo(carPrice, tradeIn, downPay, loan, annualIntRate);
  
  float* monPay;
  monPay = calcMonPayment(loan, monthlyIntRate);
  displayLoanSchedule(monPay);

   
}