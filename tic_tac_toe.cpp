nclude <iostream>
using namespace std;

int board[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

string player;
// contains row and col of a position in the tic-tac-toe board
struct Position {
	int row, col;
};

// function declaraions
void makeMove(string player);
void userMove();
void computerMove();
bool isDraw();
bool isWin();
Position optimalMove();
int evaluateFunc(string player);

int main() {
	int score;
  	cout << "Who wants to make the first move? \n";
  	do{
    		cin >> player;
  	} while ((player != "user") || (player != "computer"));
  
 	while (!isDraw() && !isWin()) {
    		makeMove(player);
    		if (player == "user")
    		  player = "computer";
    		else
    		  player = "user";
  	}
  	return 0;
}

// calls userMove() and computerMove()
void makeMove(string player) {
  	cout << "Entered makeMove\n";
  	if (player == "user") {
    		cout << "User turn ...\n";
    		userMove();
  	}
  	else
    		computerMove();
}

// prompts the user for his move
void userMove() {
  	Position userMove;
  	cout << "Row: ";
  	cin >> userMove.row;
  	cout << "Column: ";
  	cin >> userMove.col;
  	if (board[userMove.row-1][userMove.col-1] == 0)
    		board[userMove.row-1][userMove.col-1] == 1;
  	else {
    		cout << "Someone already used it.\n";
    		userMove();
	}
}

// computers move
void computerMove() {
  	Position bestMove = optimalMove();
	board[bestMove.row][bestMove.col] = 2;
}

// returns true if the someone won the game, else returns false
bool isWin() {
	if (board[0][0] != 0) {
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
    		if (board[0][1] != 0)
      			if (board[0][1] == board[1][1])
        			if (board[0][1] == board[2][1]) {
          				return true;
        			}
  	else
    		if (board[1][0] != 0)
      			if (board[1][0] == board[1][1])
        			if (board[1][0] == board[1][2]) {
          				return true;
        			}
  	else
    		if (board[2][0] != 0)
      			if (board[2][0] == board[2][1])
        			if (board[2][0] == board[2][2]) {
          				return true;
        			}
  	else
    		if (board[0][2] != 0)
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
      			if (board[i][j] == 0)
        			return false;
    		}
  	}
	return true;
}

int evaluateFunc() {
		if (isWin() && (player == "user"))	return 10;
		else 
		  if (isWin() && (player == "computer")) return -10;
		  else
		    if (isDraw()) return 0;
}

// returns the best optimal move com needs to take
Position optimalMove() {
	Position bestMove;
	int posScore;
	int bestScore = -100;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				board[i][j] = 2;
				posScore = minmax(0, false);
				if (posScore > bestScore) {
					bestMove.row = i;
					bestMove.col = j;
					bestScore = posScore;
				}
				board[i][j] = 0;
			}
		}
	}
	return bestMove;
}

int minmax(int depth, bool player) {
  if (isDraw() || isWin()) return evaluateFunc();
  
}

