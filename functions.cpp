//Name: Rayan Bouamrane
//ID: 260788250

#include <iostream>
#include <cstring>
#include <random>

using namespace std;

void initializeBoards();
void setupDisplayBoard(char board[]);
void greetAndInstruct();
void displayBoard(char board[]);
bool checkIfLegal(int cellNbre, char board[]);
bool checkIfCompLegal(int c, char board[]);
bool looper(char board[], char player, int start, int end, int inc);
bool checkWinnerHelper(char board[], char player);
bool checkWinner(char board[]);
void computerMove(char board[]);
bool checkTie(char board[]);

char theBoard[27];              //global variable storing board composed of chars
string display[27];             //similar to theBoard, stores corresponding formatted strings

void initializeBoards() {
    for (char &i : theBoard)
        i = ' ';
    for (auto &i : display)
        i = " ";
}

void setupDisplayBoard(char board[]) {
    for (int i = 0; i < 27; i++) {
        if (board[i] == ' ') {
            display[i] = to_string(i + 1);
            if (i < 9) {
                display[i] += " ";
            }
        } else {
            display[i] = string(1, board[i]) + " ";
        }
    }
}

void greetAndInstruct() {
    initializeBoards();
    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.\n"
            "The board is numbered from 1 to 27 as per the following:\n\n";
    displayBoard(theBoard);
    cout << "Player starts first. Simply input the number of the cell you want to occupy.\n"
            "Player’s move is marked with X. Computer’s move is marked with O.\n\n"
            "Start? (y/n): \n";

    while (cin) {
        string str;
        getline(cin, str);
        if (str == "n" || str == "N") {
            cout << "Good Bye!\n";
            exit(0);
        } else if (str == "y" || str == "Y") {
            cout << "\n";
            break;
        } else
            cout << "Try Again.\n";
    }
    displayBoard(theBoard);
}

void displayBoard(char board[]) {

    setupDisplayBoard(board);

    for (int j = 0; j < 3; j++) {
        cout << " ";
        for (int i = 3 * j; i < 27; i++) {
            cout << display[i];
            if (i % 3 != 2) {
                cout << " | ";
            } else {
                i += 6;
                cout << "       ";
            }
        }
        cout << "\n";
        if (j < 2) { cout << "-------------      --------------     --------------\n"; }
    }
    cout << "\n";
}

bool checkIfLegal(int cellNbre, char board[]) {

    if (cellNbre < 1 || cellNbre > 27) {
        cout << "Not in range\n";
    } else if (board[cellNbre - 1] != ' ') {
        cout << "Cell occupied\n";
    } else {
        return true;
    }
    return false;
}

bool checkIfCompLegal(int c, char board[]) {
    return (c >= 0 && c < 27 && board[c] == ' '); //same logic but without the print statements
}


bool looper(char board[], char player, int start, int end, int inc) {       //helper function, checks if given
    int counter = 0;                                                        //3 cells have all X's or all O's
    for (int i = start; i <= end; i += inc) {
        if (board[i] == player)
            counter++;
    }
    return counter > 2;
}

bool checkWinnerHelper(char board[], char player) {

    if (looper(board, player, 0, 26, 13)) return true;      //checks 3D diagonals eg. 1,14,27
    if (looper(board, player, 2, 24, 11)) return true;
    if (looper(board, player, 6, 20, 7)) return true;
    if (looper(board, player, 8, 18, 5)) return true;

    for (int i = 0; i < 9; i++)                                          //checks horizontal eg. 1,2,3
        if (looper(board, player, 3 * i, 3 * i + 2, 1)) return true;

    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)                                       //checks vertical eg. 1,4,7
            if (looper(board, player, i + 9 * j, i + 6 + 9 * j, 3)) return true;

    for (int i = 0; i < 9; i++)
        if (looper(board, player, i, i + 18, 9)) return true;   //checks depth/horizontal eg. 1, 10, 19

    for (int i = 0; i < 3; i++)
        if (looper(board, player, 9 * i, 9 * i + 8, 4)) return true; //diagonal eg. 1,5,9

    for (int i = 0; i < 3; i++)                                        //other direction diagonal eg. 3,5,7
        if (looper(board, player, 9 * i + 2, 9 * i + 6, 2)) return true;

    for (int i = 0; i < 3; i++)                                     //diagonal eg. 1,11,21
        if (looper(board, player, 9 * i, 9 * i + 20, 10)) return true;

    for (int i = 0; i < 3; i++)                                     //diagonal eg. 3,11,19
        if (looper(board, player, 9 * i + 2, 9 * i + 18, 8)) return true;

    return false;
}

bool checkWinner(char board[]) {

    if (checkWinnerHelper(board, 'X')) {
        cout << "Player Wins!\n";
        return true;
    }

    if (checkWinnerHelper(board, 'O')) {
        cout << "Computer Wins.\n";
        return true;
    }
    return false;
}

void computerMove(char board[]) {

    for (int i = 0; i < 27; i++) {
        char temp[27];
        strcpy(temp, board);
        temp[i] = 'O';                       //create temporary board where a given move has been played

        if (checkIfCompLegal(i, theBoard) && (checkWinnerHelper(temp, 'O'))) {
            theBoard[i] = 'O';                  //if the move is legal, and the computer is a winner by playing it,
            board[i] = 'O';                     //computer plays it
            cout << "Computer's move: " << i + 1 << "\n";
            displayBoard(board);
            return;
        }                  //this is tested first and separately to guard against case where a move prevents a loss
    }                      //but doesnt win, yet a winning move could have been found after

    for (int i = 0; i < 27; i++) {
        char temp[27];
        strcpy(temp, board);
        temp[i] = 'X';                  //temp board stores hypothetical player move

        if (checkIfCompLegal(i, theBoard) && (checkWinnerHelper(temp, 'X'))) {
            theBoard[i] = 'O';          //if that move would have made the player a winner,
            board[i] = 'O';             //computer plays it itself
            cout << "Computer's move: " << i + 1 << "\n";
            displayBoard(board);
            return;
        }
    }

    while (true) {
        random_device rd;                   //else play randomly
        mt19937 mt(rd());
        uniform_real_distribution<double> d(0, 27);
        int i = (int) d(mt);
        if (checkIfCompLegal(i, theBoard)) {
            theBoard[i] = 'O';
            board[i] = 'O';
            cout << "Computer's move: " << i + 1 << "\n";
            displayBoard(board);
            return;
        }
    }
}

bool checkTie(char board[]) {
    for (int i = 0; i < 27; i++)
        if (board[i] == ' ') return false;
    return true;
}
