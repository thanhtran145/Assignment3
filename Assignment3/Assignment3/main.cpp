// Name: Thanh Tran
// Date: 09/14/2023
// Desciption: Chapter 3 - Assignments 3

//Credit:
//Joe Bryant& Erik Santana 
//Saul Merino & John Kim 
//Otoniel Torres Bernal

#include <iostream>
#include <iomanip>
#include "input.h"
#include "TicTacToe.h"
#include <chrono>
#include "N_Queens.h"

using namespace std;

// Function Prototypes
void Tic_Tac_Toe();
void player_move(char playerSymbol, TicTacToe& game, int& forfeit, int& move);
void computer_move(char playerSymbol, TicTacToe& game);
void game_statistics(int total_games, double fastTime, int fastTimeMoves, double longTime, int longTimeMoves, double sum);

void N_queens();
void game_statistics_queens(int total_games, double fastTime, int fastTimeMoves, double longTime, int longTimeMoves, double sum, int size);

void Tower();

// Main Function
int main()
{
	// Main Menu and Options
	do
	{
		system("cls");
		cout << "\n\tCMPR131 Chapter 3 - Games Applications using Container by Thanh Tran (09/14/2023)";
		cout << "\n\t" + string(90, char(205));
		cout << "\n\t\t1> Tic-Tac-Toe";
		cout << "\n\t\t2> Tower of Hanoi";
		cout << "\n\t\t3> n-Queens";

		cout << "\n\t" + string(90, char(196));
		cout << "\n\t\t0. exit";
		cout << "\n\t" + string(90, char(205));

		switch (toupper(inputChar("\n\t\tOption: ", static_cast<string>("1230"))))
		{
		case '0': exit(1); break;
		case '1': system("cls"); Tic_Tac_Toe(); break;
		case '2': system("cls"); Tower(); break;
		case '3': system("cls"); N_queens(); break;
		default: cout << "\t\tERROR - Invalid option."; break;
		}
		cout << "\n";
		system("pause");
	} while (true);

	return EXIT_SUCCESS;
}

//********************************* Option 1 ****************************************//
void Tic_Tac_Toe()
{
	// initialize variables
	TicTacToe game;

	char player = 'X';
	char option = ' ';

	int forfeit = 0;
	int total_games = 0;


	double gameDuration = 0;
	double fastTime = 0;
	double longTime = 0;

	int longTimeMoves = 0;
	int fastTimeMoves = 0;

	double sum = 0;
	int moves = 0;

	// timer
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;

	cout << "\n\tTic-tac-toe (also known as Noughts and crosses or Xs and Os) is a game for two";
	cout << "\n\tplayers, X and O, who take turns marking the spaces in a 3x3 grid.The player who";
	cout << "\n\tsucceeds in placing three of their marks in a horizontal, vertical, or diagonal";
	cout << "\n\trow wins the game.";
	cout << "\n\tThis tic-tac-toe program plays against the computer. Human player, X, will always";
	cout << "\n\tfirst. Time will be recorded for the fastest and the slowest game. Average time will";
	cout << "\n\tthen be calculated and displayed.\n";
	cout << "\n\tGame begins ...\n";

	// the game logic
	do
	{
		game.diplay_board();

		moves = 0;

		start = chrono::steady_clock::now();

		while (true)
		{
			if (player == 'X')
			{
				player_move(player, game, forfeit, moves);

				if (forfeit == -1)
				{
					cout << "\n\tYou forfeited the game. Therefore, Dumb AI has won.\n\n";
					total_games++;
					break;
				}
				else
					game.diplay_board();
			}
			else
			{
				cout << "\n\tDumb AI moves...";
				computer_move(player, game);
				game.diplay_board();
			}

			// Check for win or draw conditions
			if (game.winner_check(player))
			{
				cout << "\n\t" << (player == 'X' ? "Human" : "Dumb AI") << " has actually won.!" << "\n";
				game.reset_board();
				total_games++;

				cout << "\n";
				break;
			}
			else if (game.check_draw())
			{
				cout << "\n\tIt's a draw!" << "\n";
				game.reset_board();
				total_games++;

				cout << "\n";
				break;
			}

			 //Check for win or draw conditions
			 //Switch players for the next turn
			player = (player == 'X') ? 'O' : 'X';
		}

		end = chrono::steady_clock::now();

		chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(end - start);
		gameDuration = duration.count();

		sum += gameDuration;

		if (total_games == 1)
		{
			fastTime = gameDuration;
			longTime = gameDuration;
			fastTimeMoves = moves;
			longTimeMoves = moves;
		}
		else if (gameDuration < fastTime)
		{
			fastTime = gameDuration;
			fastTimeMoves = moves;

		}
		else if (gameDuration > longTime)
		{
			longTime = gameDuration;
			longTimeMoves = moves;
		}

		option = toupper(inputChar("\tPlay again ? (Y - yes or N - no) ", 'Y', 'N'));

	} while (option == 'Y');

	game_statistics(total_games ,fastTime, fastTimeMoves, longTime, longTimeMoves, sum);
}

//Precondition: char player symbol (x, or o), TicTacToe object, and int move accumulator
//Postcondtion: get players moves
void player_move(char playerSymbol,TicTacToe &game, int &forfeit, int &move)
{
	cout << "\n\tHUMAN moves...\n\n";

	bool validMove = false;

	while (!validMove)
	{
		game.set_row(inputInteger("\t\tEnter the board's row # (1..3) or 0 to forfeit: ", 0, 3));

		// Take player input for row and column
		if (game.get_row() == -1)
		{
			forfeit = game.get_row();
			break;
		}

		game.set_column(inputInteger("\t\tEnter the board's column # (1..3) or 0 to forfeit: ", 0, 3));

		if (game.get_column() == -1)
		{
			forfeit = game.get_column();
			break;
		}

		// Check if the selected position is already occupied
		if (game.get_coordinate() == ' ') 
		{
			// Update the board with the player's symbol
			game.set_move(playerSymbol);
			validMove = true;
			move++;
		}
		else 
		{
			cout << "\n\n\tERROR: Illegal move. The square has already owned. Please re-specify.\n";
		}
	}
}

//Precondition:  char player symbol (x, or o), TicTacToe object
//Postcondtion: generate computer moves for the game
void computer_move(char playerSymbol, TicTacToe& game)
{
	unsigned seed = time(0);
	srand(seed);

	do 
	{
		// Generate random row and column
		
		game.set_row((rand() % 3) +1);
		game.set_column((rand() % 3) +1);

	} while (game.get_coordinate() != ' '); // Keep generating until an empty spot is found

	game.set_move(playerSymbol);
}

//Precondition: game statistic variables
//Postcondtion: display the game stats
void game_statistics(int total_games,double fastTime, int fastTimeMoves, double longTime, int longTimeMoves, double sum)
{
	double mean = 0;

	if (total_games != 0)
	{
		mean = sum / (double)total_games;
	}
	
	// Print the number of games played
	cout << "\n\tGame statistics: \n\n\t";
	cout << total_games << " games using of Tic-Tac-Toe were played.\n";
	cout << fixed << setprecision(0) << "\n\t\tThe fastest time was " << fastTime << " seconds in " << fastTimeMoves << " moves.";
	cout << fixed << setprecision(0) << "\n\t\tThe slowest time was " << longTime << " seconds in " << longTimeMoves << " moves.";
	cout << fixed << setprecision(0) << "\n\t\tThe average time was " << mean << " second(s).\n\n";
}


//********************************** Option 2 ***************************************//
void Tower()
{
}


//********************************** Option 3 ***************************************//
void N_queens()
{
	int row = 0;
	int column = 0;
	int moves = 0;
	int size = 0;

	char choice = ' ';
	char option = 'Y';

	double gameDuration = 0;
	double fastTime = 0;
	double longTime = 0;

	int longTimeMoves = 0;
	int fastTimeMoves = 0;
	int total_games = 0;

	double sum = 0;

	vector<vector<double>> game_stats;
	vector <double> columns;

	// timer
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;

	cout << "\n\tThe n - queens puzzle is the problem of placing n chess queens on a nxn chessboard";
	cout << "\n\tso that no two queens threaten each other; thus, a solution requires that no two";
	cout << "\n\tqueens share the same row, column, or diagonal.Solutions exist for all natural";
	cout << "\n\tnumbers n with the exception of n = 2 and n = 3.";

	do
	{
		size = inputInteger("\n\n\tEnter the board dimension nxn: ", 1, 64);

		N_Queens game(size);
		cout << "\n\t" << size << "-Queens";

		start = chrono::steady_clock::now();

		while(true)
		{
			game.displayBoard();

			cout << "\n\tGame Options";
			cout << "\n\t" + string(50, char(205));
			cout << "\n\tA> Place a queen";
			cout << "\n\tB> Remove an existing queen";
			cout << "\n\t" + string(50, char(196));
			cout << "\n\t0> return";
			cout << "\n\t" + string(50, char(205));

			choice = toupper(inputChar("\n\tOption: ", static_cast<string>("AB0)")));

			if (choice == 'A')
			{
				row = inputInteger("\n\tPosition a queen in the row (1.." + to_string(size) + "): ", 1, size);
				column = inputInteger("\tPosition a queen in the column (1.." + to_string(size) + "): ", 1, size);

				if (game.place_queen(row - 1, column - 1))
				{
					cout << "\n\tQueen placed successfully!\n\n";

					moves++;

					if (game.is_solved())
					{
						cout << "\n\tCongratulation!You have solved " + to_string(size) + "-Queens in " + to_string(moves) + " moves\n";
						game.displayBoard();

						total_games++;
						break;
					}
				}
				else
				{
					cout << "\n\tERROR: Invalid move.Try again.\n\n";
				}
			}
			else if (choice == 'B')
			{
				row = inputInteger("\n\tEnter an existing queen from the row(1.." + to_string(size) + "): ", 1, size);
				column = inputInteger("\tEnter an existing queen from the column (1.." + to_string(size) + "): ", 1, size);

				if (game.remove_queen(row - 1, column - 1))
				{
					cout << "\n\tQueen removed successfully!\n\n";
				}
				else
				{
					cout << "\n\tERROR: No such queen existed.\n";
				}
			}
			else if (choice == '0') 
			{
				break;
			}
			else 
			{
				cout << "Invalid choice. Please try again." << "\n";
			}
		}

		end = chrono::steady_clock::now();

		chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(end - start);
		gameDuration = duration.count();

		sum += gameDuration;

		if (total_games == 1)
		{
			fastTime = gameDuration;
			longTime = gameDuration;
			fastTimeMoves = moves;
			longTimeMoves = moves;
		}
		else if (gameDuration < fastTime)
		{
			fastTime = gameDuration;
			fastTimeMoves = moves;

		}
		else if (gameDuration > longTime)
		{
			longTime = gameDuration;
			longTimeMoves = moves;
		}

		option = toupper(inputChar("\n\tPlay again ? (Y - yes or N - no) ", 'Y', 'N'));

		game.reset_board();

	} while (option == 'Y');

	game_statistics_queens(total_games, fastTime, fastTimeMoves, longTime, longTimeMoves, sum, size);
}


//Precondition: game statistic variables
//Postcondtion: display the game stats
void game_statistics_queens(int total_games, double fastTime, int fastTimeMoves, double longTime, int longTimeMoves, double sum, int size)
{
	double mean = 0;

	if (total_games != 0)
	{
		mean = sum / (double)total_games;
	}

	if (total_games == 0)
	{
		cout << "\n\tNo game statistic collected.\n";
	}
	else
	{
		// Print the number of games played
		cout << "\n\tGame statistics: \n\n\t";
		cout << total_games << " game(s) N-queens were played.\n";
		cout << fixed << setprecision(0) << "\n\t\tThe fastest time was " << fastTime << " seconds in " << fastTimeMoves << " moves.";
		cout << fixed << setprecision(0) << "\n\t\tThe slowest time was " << longTime << " seconds in " << longTimeMoves << " moves.";
		cout << fixed << setprecision(0) << "\n\t\tThe average time was " << mean << " second(s).\n\n";
	}
}
