
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
    bool mark = false;
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
	board[r][c].mark = !board[r][c].mark; // Toggle mark
}

void printBoard(bool revealAll = false) {
	if(SIZE>10){
		cout << "    ";
   		for (int c = 0; c < SIZE; c++) {
			if(c>=10){
				cout << c << ' ';
			}
			else{cout << c << "  ";}
    	}
		std::cout <<"\n   ";
		for(int i=0;i<SIZE-1;i++){
    			std::cout << "_-";
		}
		std::cout << "_"
    		cout << endl;
    		for (int r = 0; r < SIZE; r++) {
			if(r>=10){cout << r << " |";}
			else{cout << r << "  |";}
        		for (int c = 0; c < SIZE; c++) {
            			if (revealAll || board[r][c].revealed) {
               				if (board[r][c].isMine)
                    				cout << "*  ";
                			else{
                    				cout << board[r][c].adjacentMines << "  ";
					}
					if (board[r][c].mark) {
						cout << "F  ";
					}
            				else {
                				cout << ".  ";
            				}
        			}
        		cout << endl;
    			}
		}
	return;
	}
    cout << "   ";
    for (int c = 0; c < SIZE; c++) {
        cout << c << ' ';
    }
    std::cout << "\n   ";
    for (int r = 0; r < SIZE-1; r++) {
        std::cout << "_-";
    }
    std::cout << "_";
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
			else if (board[r][c].mark) {
				cout << "F ";
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
//int inRange() {
//    int inRange = 0;
//    for (int a = -1; a >= 1; a++) {
//        for (int j = -1; j >= 1; j++) {
//            if (board[a][j].fail()) { continue; }
//            else {
//                if (board[a][j].isMine) {
//                    inRange++;
//                }
//            }
//        }
//    }
//	return inRange;
//}

int main() {
    srand(time(0));
    placeMines();
    calculateAdjacents();
	int row, col;
        string flag;
	//start makes sure 0 to start and can't be a mine
	printBoard();
	 cin >> row;
        // Check if the user entered a flag command
        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin >> flag >> row >> col; // attempt to read the "mark" command
            if (flag == "mark"||flag=="f"||flag=="m" || flag == "flag" && row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
                mark(row, col); // toggle mark
                
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please try again.\n";
                
            }
        }
        cin >> col;
		// Validate row and column input
		if (cin.fail() || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter valid row and column numbers.\n";
            
        }
	        // Check actions and values


		
        while(true){
            int removed = 0;
            for(int a=-1;a>=1;a++){
                for(int j=-1;j>=1;j++){
                    // Remove mines in a 3x3 area around (row, col)
                    for (int a = -1; a <= 1; a++) {
                        for (int j = -1; j <= 1; j++) {
                            int nr = row + a;
                            int nc = col + j;
                            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE) {
                                if (board[nr][nc].isMine) {
                                    board[nr][nc].isMine = false;
                                    removed++;
                                }
                            }
                        }
                    }
                    // Re-place the removed mines elsewhere
                    for (int i = 0; i < removed; i++) {
                        placeMines();
                    }
                }
            }
            if (removed == 0) { break; }
        }

		if (!board[row][col].mark) {
            reveal(row, col);
		}

    while (true) {
        system("cls");
        printBoard();
        cout << "Enter row and column to reveal (or 'mark <row> <col>'): ";
        cin >> row;


        // Check if the user entered a flag command
        if (cin.fail()) {
            cin.clear(); // clear the error flag
            cin >> flag >> row >> col; // attempt to read the "mark" command
            if (flag == "mark"||flag=="f"||flag=="m" || flag == "flag" && row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
                mark(row, col); // toggle mark
                continue;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please try again.\n";
                continue;
            }
        }

        cin >> col;

        // Validate row and column input
        if (cin.fail() || row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter valid row and column numbers.\n";
            continue;
        }
		
        // Check actions and values
        if (board[row][col].isMine) {
            printBoard(true);
            std::cout << "BOOM! You hit a mine.\n";
            break;
        }
		if (!board[row][col].mark) {
            reveal(row, col);
			continue;
		}
        

        // Win Condition
        if (checkWin()) {
            printBoard(true);
            cout << "You won!\n";
            break;
        }
    }

    return 0;
}
