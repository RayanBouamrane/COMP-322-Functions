//Name: Rayan Bouamrane
//ID: 260788250
//run using: g++ main.cpp

#include <iostream>
#include "functions.cpp"

using namespace std;

int main() {

    greetAndInstruct();

    while (cin && !checkWinner(theBoard)) {
        cout << "Make a move!\n\n";
        string str;
        int cell = 0;
        getline(cin, str);
        try { cell = stoi(str); }
        catch (invalid_argument const &e) {
            cout << "Not a number\n";
            continue;
        }
        catch (out_of_range const &f) {
            cout << "Out of integer range\n";
            continue;
        }
        if (checkIfLegal(cell, theBoard)) {

            theBoard[cell - 1] = 'X';
            cout << "\n";
            displayBoard(theBoard);

            if (checkWinner(theBoard)) { break; }

            computerMove(theBoard);
            if (checkWinner(theBoard)) { break; }

            if (checkTie(theBoard)) {
                cout << "it's a tie";
                break;
            }
        }
    }
    return 0;
}