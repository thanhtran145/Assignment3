#pragma once
#include<iostream>

using namespace std;

const int ROW_SIZE = 3;
const int COL_SIZE = 3;

class TicTacToe
{
private:

	char board[ROW_SIZE][COL_SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
	int row;
	int column;

public:
	TicTacToe();

	int get_row() const;
	int get_column() const;

	void set_row(int newRow);
	void set_column(int newColumn);

	char get_coordinate();
	void set_move(char move);

	void diplay_board();
	bool winner_check(char playerSymbol);
	void reset_board();
	bool check_draw();
};

