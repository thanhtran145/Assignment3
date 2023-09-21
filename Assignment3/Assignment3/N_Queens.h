#pragma once
#include <vector>
#include <iostream>

using namespace std;

class N_Queens
{
private:
	int size;
	vector<vector<char>> board;
public:
	N_Queens(int new_size);

	bool is_safe(int row, int col) const;
	bool place_queen(int row, int col);

	bool remove_queen(int row, int col);
	bool is_solved() const;
   
	void reset_board();
	void displayBoard() const;
};

