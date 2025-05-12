// JT_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10;
const int MINES = 10;

struct Cell {
    bool isMine = false;
    bool revealed = false;
    int adjacentMines = 0;
};

vector<vector<Cell>> board(SIZE, vector<Cell>(SIZE));

void placeMines() {
    int placed = 0;
    while (placed < MINES) {
        int r = rand() % SIZE;
        int c = rand() % SIZE;
        if (!board[r][c].isMine) {
            board[r][c].isMine = true;
            placed++;
        }
    }
}

void calculateAdjacents() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c].isMine) continue;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && board[nr][nc].isMine) {
                        board[r][c].adjacentMines++;
                    }
                }
            }
        }
    }
}

void reveal(int r, int c) {
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || board[r][c].revealed) return;
    board[r][c].revealed = true;
    if (board[r][c].adjacentMines == 0 && !board[r][c].isMine) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr != 0 || dc != 0) reveal(r + dr, c + dc);
            }
        }
    }
}

void mark(int r, int c) {
	if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) return;
	if (board[r][c].revealed) return; // Can't mark a revealed cell
	board[r][c].revealed = !board[r][c].revealed; // Toggle mark
}

void printBoard(bool revealAll = false) {
    cout << "   ";
    for (int c = 0; c < SIZE; c++) {
        cout << c << ' ';
    }
    std::cout << "\n   _-_-_-_-_-_-_-_-_-_";
    /*for (int c = 0; c < SIZE; c++) {
        cout << "_";
    }*/
    cout << endl;
    for (int r = 0; r < SIZE; r++) {
        cout << r << " |";
        for (int c = 0; c < SIZE; c++) {
            if (revealAll || board[r][c].revealed) {
                if (board[r][c].isMine)
                    cout << "* ";
                else
                    cout << board[r][c].adjacentMines << ' ';
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}


bool checkWin() {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (!board[r][c].isMine && !board[r][c].revealed)
                return false;
    return true;
}


int main() {
    srand(time(0));
    placeMines();
    calculateAdjacents();

    while (true) {
        printBoard();
        int row, col;
        cout << "Enter row and column to reveal: ";
            cin >> row >> col;


		if (cin.fail() || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
			cin.clear(); // clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
			mark(row, col); // toggle mark
			continue;
		}

        // reveal(row, col);

        // Fail condition
        if (board[row][col].isMine) {
            printBoard(true);
            std::cout << "BOOM! You hit a mine.\n";
            break;
        }

        reveal(row, col);

        // Win Condition
        if (checkWin()) {
            printBoard(true);
            cout << "You won!\n";
            break;
        }
    }

    return 0;
}