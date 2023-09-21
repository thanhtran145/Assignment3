#include "TicTacToe.h"

using namespace std;

//*********************************** Constructor ********************************//
// Default Constructor
TicTacToe::TicTacToe()
{
	row = 0;
	column = 0;
}

//*********************************** Accessor *********************************//
//Precondition: NA
//Postcondtion: return the row attribute
int TicTacToe::get_row() const
{
	return row;
}

//Precondition:NA
//Postcondtion: return the column attribute
int TicTacToe::get_column() const
{
	return column;
}

//Precondition: NA
//Postcondtion: return the board attribute
char TicTacToe::get_coordinate()
{
	return board[row][column];
}

//*********************************** Mutator ************************************//
//Precondition: an int from (1 to 3)
//Postcondtion: set the attribute row from (-1 to 2)
void TicTacToe::set_row(int newRow)
{
	int choice = 0;

	choice = newRow;

	switch (choice)
	{
	case 0: row = choice - 1;
		break;
	case 1: row = choice - 1;
		break;
	case 2: row = choice - 1;
		break;
	case 3: row = choice - 1;
	}
}

//Precondition: an int from (1 to 3)
//Postcondtion: set the attribute column from (-1 to 2)
void TicTacToe::set_column(int newColumn)
{
	int choice = 0;

	choice = newColumn;

	switch (choice)
	{
	case 0: column = choice - 1;
		break;
	case 1: column = choice - 1;
		break;
	case 2: column = choice - 1;
		break;
	case 3: column = choice - 1;
	}
}

//Precondition: a char 'x' or 'o'
//Postcondtion: set the board attribute to 'x' or 'o'
void TicTacToe::set_move(char move)
{
	board[row][column] = move;
}

//********************************** Public Methods ******************************//
//Precondition: NA
//Postcondtion: Display the tictactoe board
void TicTacToe::diplay_board()
{
	cout << "\n\n\t\t Tic-Tac-Toe";
	cout << "\n\t\t" << string(1, char(201)) << string(3, char(205)) << string(1, char(203)) << string(3, char(205)) << string(1, char(203)) << string(3, char(205)) << string(1, char(187));

	for (int i = 0; i < ROW_SIZE; i++) 
	{
		cout << "\n\t\t" << string(1, char(186));
		for (int j = 0; j < COL_SIZE; j++) 
		{
			cout << " " << board[i][j] << " " << string(1, char(186));
		}
		if (i == ROW_SIZE - 1)
		{
			cout << "\n\t\t" << string(1, char(200)) << string(3, char(205)) << string(1, char(202)) << string(3, char(205)) << string(1, char(202)) << string(3, char(205)) << string(1, char(188));
		}
		else
		{
			cout << "\n\t\t" << string(1, char(204)) << string(3, char(205)) << string(1, char(206)) << string(3, char(205)) << string(1, char(206)) << string(3, char(205)) << string(1, char(185));
		}
	}
	cout << "\n";
}

//Precondition: a char 'x' or 'o'
//Postcondtion: return true if wins, else return false
bool TicTacToe::winner_check(char playerSymbol)
{
	// Check rows, columns, and diagonals for a win
	for (int i = 0; i < ROW_SIZE; i++) 
	{
		if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) 
		{
			return true; // Row win
		}
		if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol) 
		{
			return true; // Column win
		}
	}

	if (board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) 
	{
		return true; // Diagonal win (top-left to bottom-right)
	}

	if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol) 
	{
		return true; // Diagonal win (top-right to bottom-left)
	}

	return false;
}

//Precondition: NA
//Postcondtion: reset the board attribute to ' '
void TicTacToe::reset_board()
{
	for (int i = 0; i < ROW_SIZE; i++) 
	{
		for (int j = 0; j < COL_SIZE; j++) 
		{
			board[i][j] = ' ';
		}
	}
}

//Precondition: NA
//Postcondtion: retunr true the game is draw, else return false
bool TicTacToe::check_draw()
{
	// Check if the board is full (a draw)
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++) 
		{
			if (board[i][j] == ' ') 
			{
				return false; // Empty cell found, the game is not a draw
			}
		}
	}

	return true; // All cells are occupied, it's a draw
}