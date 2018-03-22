```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// either computer or user
string player;
// contains row and col of a position in the tic-tac-toe board
struct Position {
	int row, col;
};

// function declaraions3
void displayBoard(char board[3][3]);
void makeMove(char board[3][3]);
void userMove(char board[3][3]);
void computerMove(char board[3][3]);
bool canMove(char board[3][3]);
int evaluate(char board[3][3]); 
bool isDraw(char board[3][3]);
Position optimalMove(char board[3][3]);
int minmax(char board[3][3], bool maximizer);
void playGame(char board[3][3]);

// prints the tic-tac-toe board with every moves players made 
void displayBoard(char board[3][3]) {
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
void makeMove(char board[3][3]) {
    // calls userMove()
  	if (player == "user") {
    		cout << "User turn ...\n";
    		userMove(board);
  	}
  	// calls computerMove()
  	else {
  	    cout << "Computer turn ...\n";
    		computerMove(board);
  	}
}

// prompts the user for his move
// if the Positionis alraedy occupied, prompts user input once again
void userMove(char board[3][3]) {
  	int row, col;
  	cout << "Row[1-3]: ";
  	cin >> row;
  	cout << "Column[1-3]: ";
  	cin >> col;
  	// if the Position is empty
  	if (board[row-1][col-1] == ' ') {
    		board[row-1][col-1] = 'X';
    }
    // if someone already made a move in the Position
  	else {
    		cout << "Someone already used it.\n";
    		cout << "Please insert row and column once again\n";
    		userMove(board);
	  }
}

// computer makes the move
void computerMove(char board[3][3]) {
  // calls optimalMove() and stores the returning struct in bestMove
  Position bestMove = optimalMove(board);
  // updating the board with computer's move
	board[bestMove.row][bestMove.col] = 'O';
}

// returns true if there are any remaining move else false
bool canMove(char board[3][3]) {
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
int evaluate(char board[3][3]) {
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
  if (board[0][0] == board[1][1] && board[2][2] == board[1][1]) {
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
bool isDraw(char board[3][3]) {
	for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == ' ') {
        return false;
      }
    }
  }
  int evaluateScore = evaluate(board);
	if (evaluateScore == 10 || evaluateScore == -10) return false;
	return true;
}

// returns the best optimal move computer needs to move
Position optimalMove(char board[3][3]) {
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
				int posScore = minmax(board, false);
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
int minmax(char board[3][3], bool maximizer) {
  // calls evaluateFunc() and stores the value in evaluateScore
  int evaluateScore = evaluate(board);
  // if the game is won
  if (evaluateScore == 10 || evaluateScore == -10)
    return evaluateScore;
  // if no moves left
  // game is draw
  if (!canMove(board)) return 0;
  
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
          bestScore = max(bestScore, minmax(board, !maximizer));
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
          bestScore = min(bestScore, minmax(board, !maximizer));
          // undo player's move
          board[i][j] = ' ';
        }
      }
    }
  }
  return bestScore;
}

// plays the game
void playGame(char board[3][3]) {
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
    // calls makeMove that forwards which player should make the move
    makeMove(board);
    // changes the player turn 
    if (player == "user")
      player = "computer";
    else
    	player = "user";
    displayBoard(board);
    cout << "**************************\n";
    // calls evaluate() and stores the result in evaluateScore
    evaluateScore = evaluate(board);
  } while ((evaluateScore != 10 && evaluateScore != -10) && (isDraw(board) == false));
  
  cout << "     GAME OVER!     \n";
  // if the game is drawn
  if (isDraw(board))
  	cout << "It's a draw.";
  // if the game is won
  else {
    if (player == "user")
      player = "computer";
    else
    	player = "user";
  	cout << player << " won the game! \n";
  }
}

// driver fucntion
int main() {
  // declaring tic-tac-toe board
  char board[3][3];
  char playAgain;
  // loop until the user wants to stop playing the game
  do {
    // initializing each characters of the global array with ' '
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = ' ';
      }
    }
    // call playGame that actually makes the game functional
    playGame(board);
    // loop until the user enters the right character
    do {
      cout << "Wanna play again? [Y/N]";
      cin >> playAgain;
    } while (playAgain != 'Y' && playAgain != 'N');
    cout << "\n\n\n";
  } while (playAgain != 'N');
  return 0;
}
```
