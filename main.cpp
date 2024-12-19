#include "code.h"

#include <iomanip>
#include <iostream>

using namespace std;


int main()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Welcome to Nissi's Tic-Tac-Toe!\n";
    cout << "You will enter your move with the format: <X or O> <Row> <Column>\n";
    cout << "Example: X 1 1 (X moves to the top-left corner of the board)\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    // Create game instance
    TicTacToe game;

    // Start the game
    game.play();

    return 0;
}
