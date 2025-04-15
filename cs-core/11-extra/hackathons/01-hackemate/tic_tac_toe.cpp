#include <iostream>
#include <vector>
using namespace std;

vector<char> board(9, ' ');

void printBoard() {
    for (int i = 0; i < 9; i += 3) {
        cout << " " << board[i] << " | " << board[i+1] << " | " << board[i+2] << "\n";
        if (i < 6) cout << "---+---+---\n";
    }
}

bool checkWinner(char player) {
    int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };
    for (auto &condition : winConditions) {
        if (board[condition[0]] == player && 
            board[condition[1]] == player && 
            board[condition[2]] == player) {
            return true;
        }
    }
    return false;
}

bool isFull() {
    for (char cell : board) {
        if (cell == ' ') return false;
    }
    return true;
}

void playMove(char player) {
    int move;
    while (true) {
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> move;
        move -= 1;  
        if (move >= 0 && move < 9 && board[move] == ' ') {
            board[move] = player;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

void playGame() {
    char currentPlayer = 'X';
    while (true) {
        printBoard();
        playMove(currentPlayer);
        
        if (checkWinner(currentPlayer)) {
            printBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }
        
        if (isFull()) {
            printBoard();
            cout << "It's a tie!\n";
            break;
        }
        
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    playGame();
    return 0;
}

