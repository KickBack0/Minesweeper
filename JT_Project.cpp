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
    for (int c = 0; c < SIZE; c++) cout << c << ' ';
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
                cout << " . ";
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

        // Where is the Fail Function?
		if (cin.fail() || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
			cin.clear(); // clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
			mark(row, col); // toggle mark
			continue;
		}

        // Wo
        if (board[row][col].isMine) {
            std::cout << "BOOM! You hit a mine.\n";
            printBoard(true);
            break;
        }

        reveal(row, col);

        if (checkWin()) {
            cout << "You won!\n";
            printBoard(true);
            break;
        }
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
