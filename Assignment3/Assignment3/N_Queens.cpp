#include "N_Queens.h"
#include <vector>
#include <iostream>

//************************************** Constructor **********************************//
// Arg-constructor
//Precondition: a positive int size value
//Postcondtion: sets the size value to the attributes of the objects 
N_Queens::N_Queens(int new_size)
{
    size = new_size;
    board = vector<vector<char>>(new_size, vector<char>(new_size, '.'));
}

//************************************** Public Function ********************************//

//Precondition: positive int row and column parameters
//Postcondtion: return true if there is no Queens at the current coordinates otherwise return false
bool N_Queens::is_safe(int row, int column) const
{
    // Check row and column
    for (int i = 0; i < size; ++i) 
    {
        if (board[row][i] == 'Q' || board[i][column] == 'Q') 
        {
            return false;
        }
    }

    // Check diagonals
    for (int i = 0; i < size; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            if (board[i][j] == 'Q' && abs(i - row) == abs(j - column)) 
            {
                return false;
            }
        }
    }

    return true;
}

//Precondition: positive int row and column parameters
//Postcondtion: return true and set the Queen into the coordinate if its satisfy all conditions otherwise return false
bool N_Queens::place_queen(int row, int column)
{
    if (row < 0 || row >= size || column < 0 || column >= size || !is_safe(row, column)) 
    {
        return false;
    }

    board[row][column] = 'Q';
    return true;
}

//Precondition: positive int row and column parameters
//Postcondtion: return true and remove the Queen into the coordinate if its satisfy all conditions otherwise return false
bool N_Queens::remove_queen(int row, int column) 
{
    if (row < 0 || row >= size || column < 0 || column >= size || board[row][column] != 'Q') 
    {
        return false;
    }

    board[row][column] = '.';
    return true;
}

//Precondition: NA
//Postcondtion: return true if the puzzle is solved otherwise return false 
bool N_Queens::is_solved() const
{
    // Check if all queens have been placed
    int queens_placed = 0;
    for (int i = 0; i < size; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            if (board[i][j] == 'Q') 
            {
                queens_placed++;
            }
        }
    }

    // Check if all queens are safe
    if (queens_placed == size) 
    {
        return true;
    }
    else
        return false;
}

//Precondition: NA
//Postcondtion: reset the board value 
void N_Queens::reset_board()
{
    for (int i = 0; i < size; ++i) 
    {
        for (int j = 0; j < size; ++j) 
        {
            board[i][j] = '.';
        }
    }
}

//Precondition: NA
//Postcondtion: display the board
void N_Queens::displayBoard() const 
{
    cout << "\n";
    for (int i = 0; i < size; ++i) 
    {
        cout << "\t";
        for (int j = 0; j < size; ++j) 
        {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}