// Nia Maheshwari
// niakmaheshwari@gmail.com
// Chapter 4
// Programming Problem - Rock, Paper, Scissors simulation
/*The purpose of this program is to stimulate a game of rock, paper, scissors
 * with the computer!*/

#include <iostream>
using namespace std;

int main() {

  char playerOne;
  char playerTwo;
  bool flag = true;

  cout << "Welcome to rock-paper-scissors. Let's start with the Player 1! "
          "Please enter 'R' for Rock, 'P' for Paper, 'S' for Scissors, or 'Q' "
          "to quit: "
       << endl;
  cin >> playerOne;
  playerOne = (toupper(playerOne));

  if (playerOne != 'Q' && playerOne != 'q') {
    cout << "Please enter 'R', 'P', or 'S', Player 2: " << endl;
    cin >> playerTwo;
    playerTwo = (toupper(playerTwo));
  } else {
    cout << "Goodbye." << endl;
    flag = false;
  }

  while (playerOne != 'Q' && playerOne != 'q') {

    while (flag && playerOne != 'Q' && playerOne != 'q') {

      if (playerOne == playerTwo) {
        cout << "Both players chose the same option: It's a tie!" << endl;

      } else if (playerOne == 'P' && playerTwo == 'R') {
        cout << "Paper covers rock: Player 1 wins!" << endl;
      } else if (playerOne == 'P' && playerTwo == 'S') {
        cout << "Scissors cut paper: Player 2 wins!" << endl;
      } else if (playerOne == 'R' && playerTwo == 'S') {
        cout << "Rock breaks scissors: Player 1 wins!" << endl;
      } else if (playerOne == 'R' && playerTwo == 'P') {
        cout << "Paper covers rock: Player 2 wins!" << endl;
      } else if (playerOne == 'S' && playerTwo == 'R') {
        cout << "Rock breaks scissors: Player 2 wins!" << endl;
      } else if (playerOne == 'S' && playerTwo == 'P') {
        cout << "Scissors cut paper: Player 1 wins!" << endl;
      }
      flag = false;
    }
    cout << endl;
    cout << "Want to play again? Hit 'Q' to quit or start a new game by "
            "entering 'R', 'P', or 'S': "
         << endl;
    cin >> playerOne;
    playerOne = (toupper(playerOne));
    if (playerOne != 'Q') {
      cout << "Player 2: " << endl;
      cin >> playerTwo;
      playerTwo = (toupper(playerTwo));
      flag = true;
    }
  }

}    
         
