#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// initializing the tic-tac-toe board
char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

string player;
// contains row and col of a position in the tic-tac-toe board
struct Position {
	int row, col;
};

// function declaraions3
void makeMove(string player);
void userMove();
void computerMove();
bool isDraw();
bool isWin();
Position optimalMove();
int evaluateFunc(string player);
int minmax(bool maximizer);
void displayBoard();

int main() {
	int score;
  // loop until the player inputs user or computer
  /*
  do{
      cout << "Who wants to make the first move? \n";
    	cin >> player;
  } while (player != "user" || player != "computer");
  */
  cout << "Who wants to make the first move? \n";
  cin >> player;
  
  // loop until the game is not over
 	while ((isDraw() == false) && (isWin() == false)) {
 	      cout << "The game isn't over yet.\n";
    		makeMove(player);
    		if (player == "user")
    		  player = "computer";
    		else
    		  player = "user";
    		displayBoard();
    		cout << "************************************ \n";
  	}
  	cout << "The game is over.\n";
  	return 0;
}

// prints the board 
void displayBoard() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << board[i][j];
      cout << " | ";
    }
    cout << board[i][3] << endl;
    cout << "_________\n";
  }
  for (int j = 0; j < 2; j++) {
    cout << board[2][j];
    cout << " | ";
  }
  cout << board[2][3] << endl;
}
// calls userMove() and computerMove()
void makeMove(string player) {
  	// cout << "Entered makeMove\n";
  	if (player == "user") {
    		cout << "User turn ...\n";
    		userMove();
  	}
  	else {
  	    cout << "Computer turn ...\n";
    		computerMove();
  	}
}

// prompts the user for his move
void userMove() {
  	int row, col;
  	cout << "Row: ";
  	cin >> row;
  	cout << "Column: ";
  	cin >> col;
  	if (board[row-1][col-1] == ' ')
    		board[row-1][col-1] = 'X';
  	else {
    		cout << "Someone already used it.\n";
    		cout << "Please insert the row and column again\n";
    		userMove();
	  }
}

// computers move
void computerMove() {
  Position bestMove = optimalMove();
  cout << bestMove.row << bestMove.col << endl;
	board[bestMove.row][bestMove.col] = 'O';
}

// returns true if the someone won the game, else returns false
bool isWin() {
	if (board[0][0] != ' ') {
    		if (board[0][0] == board[0][1])
      			if (board[0][0] == board[0][2]) {
        			return true;
      			}
    		if (board[1][0] == board[0][0])
      			if (board[2][0] == board[0][0]) {
        			return true;
      			}
    		if (board[0][0] == board[1][1])
      			if (board[0][0] == board[2][2]) {
        			return true;
      			}
  else
    		if (board[0][1] != ' ')
      			if (board[0][1] == board[1][1])
        			if (board[0][1] == board[2][1]) {
          				return true;
        			}
  else
    		if (board[1][0] != ' ')
      			if (board[1][0] == board[1][1])
        			if (board[1][0] == board[1][2]) {
          				return true;
        			}
  else
    		if (board[2][0] != ' ')
      			if (board[2][0] == board[2][1])
        			if (board[2][0] == board[2][2]) {
          				return true;
        			}
  else
    		if (board[0][2] != ' ')
      			if (board[0][2] == board[1][2])
        			if (board[0][2] == board[2][2]) {
          				return true;
        			}
  	}
  	return false;
}

// returns true if the game is draw else false
bool isDraw() {
	for (int i = 0; i < 3; i++) {
    		for (int j = 0; j < 3; j++) {
      			if (board[i][j] == ' ')
        			return false;
    		}
  	}
	return true;
}

// evaluates the score if the game is won by either player or drawn
int evaluateFunc() {
		if (isWin() && (player == "user"))	return 10;
		else 
		  if (isWin() && (player == "computer")) return -10;
		  else
		    if (isDraw()) return 0;
}

// returns the best optimal move com needs to take
Position optimalMove() {
  cout << "Entered optimalMove\n";
	Position bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	int posScore;
	int bestScore = -100;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
				board[i][j] = 'O';
				posScore = minmax(false);
				if (posScore > bestScore) {
					bestMove.row = i;
					bestMove.col = j;
					bestScore = posScore;
				}
				board[i][j] = ' ';
			}
		}
	}
	return bestMove;
}

// minmax function that returns all possible values of the board
int minmax(bool maximizer) {
  if (isDraw() || isWin()) return evaluateFunc();
  
  int bestScore;
  // if maximizer
  if (maximizer) {
    bestScore = -100;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == ' ') {
          board[i][j] = 'O';
          bestScore = min(bestScore, minmax(!maximizer));
          // undo the move
          board[i][j] = ' ';
        }
      }
    }
  }
  //if minimizer
  else {
    bestScore = 100;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == ' ') {
          board[i][j] = 'X';
          bestScore = max(bestScore, minmax(!maximizer));
          // undo the move
          board[i][j] = ' ';
        }
      }
    }
  }
  return bestScore;
}
