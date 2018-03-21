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
// bool isWin();
Position optimalMove();
// int evaluateFunc(string player);
int minmax(bool maximizer);
void displayBoard();
int evaluate();
bool canMove(); 

// prints the tic-tac-toe board with every moves players made 
void displayBoard() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      cout << board[i][j];
      cout << " | ";
    }
    cout << board[i][2] << endl;
    cout << "_________\n";
  }
  for (int j = 0; j < 2; j++) {
    cout << board[2][j];
    cout << " | ";
  }
  cout << board[2][2] << endl;
}

// calls userMove() and computerMove() depending who the player is
void makeMove(string player) {
    // calls userMove()
  	if (player == "user") {
    		cout << "User turn ...\n";
    		userMove();
  	}
  	// calls computerMove()
  	else {
  	    cout << "Computer turn ...\n";
    		computerMove();
  	}
}

// prompts the user for his move
// if the Positionis alraedy occupied, prompts user input once again
void userMove() {
  	int row, col;
  	cout << "Row: ";
  	cin >> row;
  	cout << "Column: ";
  	cin >> col;
  	// if the Position is empty
  	if (board[row-1][col-1] == ' ') {
    		board[row-1][col-1] = 'X';
    }
    // if someone already made a move in the Position
  	else {
    		cout << "Someone already used it.\n";
    		cout << "Please insert row and column once again\n";
    		userMove();
	  }
}

// computer makes the move
void computerMove() {
  // calls optimalMove() and stores the returning struct in bestMove
  Position bestMove = optimalMove();
  // updating the board with computer's move
	board[bestMove.row][bestMove.col] = 'O';
}

/*
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
*/

// returns true if there are any remaining move else false
bool canMove() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        return true;
      }
    }
  }
  return false;
}

// calculates the score of the board depending upon the moves made by players on the board
int evaluate() {
  // evaluating the win condition for rows
  for (int i=0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][2] == board[i][1]) {
      if (board[i][0] == 'X') {
        return -10;
      }
      else if (board[i][0] == 'O') {
        return 10;
      }
    }
  }
  // checking win condition for columns
  for (int i = 0; i < 3; i++) {
    if (board[0][i] == board[1][i] && board[2][i] == board[1][i]) {
      if (board[0][i] == 'X') {
        return -10;
      }
      else if (board[0][i] == 'O') {
        return 10;
      }
    }
  }
  // check win condition for diagonals
  // check win condition for top left to bottom right diagonal
  if (board[0][0] == board[1][1] && board[2][2] == board[2][2]) {
    if (board[0][0] == 'X') {
      return -10;
    }
    else if (board[0][0] == 'O') {
      return 10;
    }
  }
  // check win condition for top right to bottom left diagonal
  if (board[2][0] == board[0][2] && board[2][0] == board[1][1]) {
    if (board[2][0] == 'X') {
      return -10;
    }
    else if (board[2][0] == 'O') {
      return 10;
    }
  }
  // return 0 if no win condition is met
  return 0;
}

// returns true if the game is draw else false
bool isDraw() {
	for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  int evaluateScore = evaluate();
	if (evaluateScore == 10 || evaluateScore == -10) return false;
	return true;
}

/*
// evaluates the score if the game is won by either player or drawn
int evaluateFunc() {
    // cout << isWin() << endl;
		if (isWin() && (player == "user"))	return -10;
		if ((isWin()) && (player == "computer")) {
		  // cout << "Entering wrong place\n";
		  return 10;
		}
		if (isDraw()) return 0;
}
*/

// returns the best optimal move computer needs to move
Position optimalMove() {
	Position bestMove;
	int bestScore = -100;
	// goes through every position 
	// evaluates minmax function for every empty position
	// retruns the position with best value
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') {
			  // computer's move
				board[i][j] = 'O';
				// call minmax and assign the returned value to posScore
				int posScore = minmax(false);
				// undo computer's move
				board[i][j] = ' ';
				// update bestScore with posScore if posScore is greater than bestScore
				if (posScore > bestScore) {
					bestMove.row = i;
					bestMove.col = j;
					bestScore = posScore;
				}
			}
		}
	}
	return bestMove;
}

// minmax function that goes through all possible values of the board
// returns the value of the board
int minmax(bool maximizer) {
  // calls evaluateFunc() and stores the value in evaluateScore
  int evaluateScore = evaluate();
  // if the game is won
  if (evaluateScore == 10 || evaluateScore == -10)
    return evaluateScore;
  // if no moves left
  // game is draw
  if (!canMove()) return 0;
  
  int bestScore;
  // if maximizer (computer's move)
  if (maximizer) {
    bestScore = -100;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        // if noone has made a move
        if (board[i][j] == ' ') {
          // computer's move
          board[i][j] = 'O';
          // call minmax recursively
          // get the max value of bestScore and recursively called minmax's value
          // assign the max value to bestScore
          bestScore = max(bestScore, minmax(!maximizer));
          // undo computer's move move
          board[i][j] = ' ';
        }
      }
    }
  }
  //if minimizer (player's turn)
  else {
    bestScore = 100;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        // if the cell is empty
        if (board[i][j] == ' ') {
          // player's move
          board[i][j] = 'X';
          // call minmax recursively
          //get the min value of bestScore and recursively called minmax's value
          bestScore = min(bestScore, minmax(!maximizer));
          // undo player's move
          board[i][j] = ' ';
        }
      }
    }
  }
  return bestScore;
}

// driver fucntion
int main() {
  cout << "      TIC-TAC-TOE     \n";
  cout << "A game where the computer God.\n\n";
  // loop until the player inputs user or computer
  do {
    cout << "Who wants to make the first move?\n";
    cout << "[user/computer]\n=";
    cin >> player;
  } while (player != "user" && player != "computer");
  
  int evaluateScore;
  // loop until the game is not over
  do {
    makeMove(player);
    if (player == "user")
      player = "computer";
    else
    	player = "user";
    displayBoard();
    cout << "**************************\n";
    evaluateScore = evaluate();
  } while ((evaluateScore == 10 || evaluateScore == -10) || (isDraw() == false));
  cout << "     GAME OVER!     \n";
  if (isDraw())
  	cout << "It's a draw.";
  else
  	cout << player << " won the game! \n";
  return 0;
}