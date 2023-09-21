// Name: Thanh Tran
// Date: 09/14/2023
// Desciption: Chapter 3 - Assignments 3

//Credit:
//Joe Bryant& Erik Santana 
//Saul Merino & John Kim 
//Otoniel Torres Bernal
//Christian Hernandez

#include <iostream>
#include <iomanip>
#include "input.h"
#include "TicTacToe.h"
#include <chrono>
#include "N_Queens.h"
#include <map>

using namespace std;

// Function Prototypes
void Tic_Tac_Toe();
void player_move(char playerSymbol, TicTacToe& game, int& forfeit, int& move);
void computer_move(char playerSymbol, TicTacToe& game);
void game_statistics(int total_games, double fastTime, int fastTimeMoves, double longTime, int longTimeMoves, double sum);

void N_queens();
void game_statistics_queens(int total_games, double fastTime, int fastTimeMoves, double longTime, int longTimeMoves, double sum, int size);

void Tower();
void display_pegs(const vector<int>& pegA, const vector<int>& pegB, const vector<int>& pegC);

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
	// Variables Declarations
	char option;

	int rings;
	int moves;
	int max_discs = 64;

	vector<int> A_Peg;
	vector<int> B_Peg; 
	vector<int> C_Peg;


	char Peg1_choice;
	char Peg2_choice;

	// Maps to keep track of the game stats
	map<int, int> fast_time;
	map<int, int> slow_time; 
	map<int, int> total_games;
	map<int, int> fastest_moves_each_game;
	map<int, int> slowest_moves_each_game;


	clock_t start_time;
	clock_t	end_time;


	// INT_MAX(2147483647)

	for (int i = 1; i <= max_discs; ++i) 
	{
		fast_time[i] = INT_MAX;
		fastest_moves_each_game[i] = INT_MAX;
	}
	do 
	{
		system("cls");
		cout << "\n\tThe Tower of Hanoi also called the Tower of Brahma or Lucas' Tower is a mathematical game.";
		cout << "\n\tIt consists of three pegs and a number of rings of different sizes, which can slide onto";
		cout << "\n\tany peg.The game starts with the rings in a neat stack in ascending order of size on one";
		cout << "\n\tpeg, the smallest at the top, thus making a conical shape.";
		cout << "\n\n\tThe objective of the game is to move the entire stack from the starting peg - A to ending peg - B,";
		cout << "\n\tobeying the following simple rules:";
		cout << "\n\n\t\t1. Only one disk can be moved at a time.";
		cout << "\n\t\t2. Each move consists of taking the upper disk from one of the stacks and";
		cout << "\n\t\t   placing it on top of another stack or on an empty peg.";
		cout <<	"\n\t\t3. No larger disk may be placed on top of a smaller disk.\n";

		// Clear the elements 
		A_Peg.clear();
		B_Peg.clear();
		C_Peg.clear();
		moves = 0;

		rings = inputInteger("\n\tEnter the number of rings (1..64) to begin: ", 1, max_discs);

		// Start the time
		start_time = clock();

		// Store the rings in descending order for the A Peg
		for (int i = rings; i >= 1; i--) 
		{
			A_Peg.push_back(i);
		}

		display_pegs(A_Peg, B_Peg, C_Peg);

		// Flag to validate the move
		bool moved = false;

		do 
		{
			Peg1_choice = inputChar("\n\tSelect the top disk from the start peg (A, B, C, or Q-quit): ", (static_cast<string>("ABCQ")));
			Peg2_choice = inputChar("\tSelect the end peg (A, B, C, or Q-quit) to move the selected disk: ", (static_cast<string>("ABCQ")));
			switch (toupper(Peg1_choice)) 
			{
			case 'A': 
			{
				//check if A Peg is empty
				if (A_Peg.empty()) 
				{
					cout << "\n\tERROR: Cannot make the move. There is no disk in the selected peg-A.\n";
					cout << "\t\tPlease choose again.";

					display_pegs(A_Peg, B_Peg, C_Peg);
					break;
				}
				if (toupper(Peg2_choice) == 'B') 
				{
					if (B_Peg.empty() || A_Peg.back() < B_Peg.back()) 
					{
						// push elemnent from A peg to B peg
						B_Peg.push_back(A_Peg.back());

						// pop it from A peg  
						A_Peg.pop_back();
						cout << "\n\tTop disk from peg-A has moved to peg-B.";

						//display the Tower of Hanoi
						display_pegs(A_Peg, B_Peg, C_Peg);

						moved = true;
					}
					else 
					{
						cout << "\n\tERROR: Cannot make the move. Top disk(" << A_Peg.back() << ") of peg-A, is larger than top disk(" << B_Peg.back() << ") of peg-B.\n";
						cout << "\t\tPlease choose again.\n";
						display_pegs(A_Peg, B_Peg, C_Peg);
					}
				}
				else if (toupper(Peg2_choice) == 'C') 
				{
					if (C_Peg.empty() || A_Peg.back() < C_Peg.back())
					{
						// push elemnent from A peg to C peg
						C_Peg.push_back(A_Peg.back());
						A_Peg.pop_back();

						cout << "\n\tTop disk from peg-A has moved to peg-C.";

						// display the Tower of Hanoi
						display_pegs(A_Peg, B_Peg, C_Peg);
						moved = true;
					}
					else 
					{
						cout << "\n\tERROR: Cannot make the move. Top disk(" << A_Peg.back() << ") of peg-A, is larger than top disk(" << C_Peg.back() << ") of peg-C.\n";
						cout << "\t\tPlease choose again.\n";
						display_pegs(A_Peg, B_Peg, C_Peg);
					}
				}
				else if (toupper(Peg2_choice) == 'Q') 
				{
					return;
				}
			}
					break;
			case 'B': 
			{
				// Validation of B peg
				if (B_Peg.empty()) 
				{
					cout << "\n\tERROR: Cannot make the move. There is no disk in the selected peg-B.\n";
					cout << "\t\tPlease choose again.";

					display_pegs(A_Peg, B_Peg, C_Peg);
					break;
				}
				if (toupper(Peg2_choice) == 'A') 
				{
					if (A_Peg.empty() || B_Peg.back() < A_Peg.back()) 
					{
						// push elemnent from B peg to A peg
						A_Peg.push_back(B_Peg.back());
						B_Peg.pop_back();

						cout << "\n\tTop disk from peg-B has moved to peg-A.";

						// display the Tower of Ha Noi
						display_pegs(A_Peg, B_Peg, C_Peg);
						moved = true;
					}
					else
					{
						cout << "\n\tERROR: Cannot make the move. Top disk(" << B_Peg.back() << ") of peg-B, is larger than top disk(" << A_Peg.back() << ") of peg-A.\n";
						cout << "\t\tPlease choose again.\n";
						display_pegs(A_Peg, B_Peg, C_Peg);
					}
				}
				else if (toupper(Peg2_choice) == 'C') 
				{
					if (C_Peg.empty() || B_Peg.back() < C_Peg.back())
					{
						// push elemnent from B peg to C peg
						C_Peg.push_back(B_Peg.back());
						B_Peg.pop_back();

						cout << "\n\tTop disk from peg-B has moved to peg-C.";

						display_pegs(A_Peg, B_Peg, C_Peg);
						moved = true;
					}
					else 
					{
						cout << "\n\tERROR: Cannot make the move. Top disk(" << B_Peg.back() << ") of peg-B, is larger than top disk(" << C_Peg.back() << ") of peg-C.\n";
						cout << "\t\tPlease choose again.\n";

						display_pegs(A_Peg, B_Peg, C_Peg);
					}
				}
				else if (toupper(Peg2_choice) == 'Q') 
				{
					return;
				}

				break;
			}
			case 'C': 
			{
				// Validation for C Peg
				if (C_Peg.empty())
				{
					cout << "\n\tERROR: Cannot make the move. There is no disk in the selected peg-C.\n";
					cout << "\t\tPlease choose again.";

					display_pegs(A_Peg, B_Peg, C_Peg);
					break;
				}
				if (toupper(Peg2_choice) == 'A')
				{
					if (A_Peg.empty() || C_Peg.back() < A_Peg.back())
					{
						// push elemnent from C peg to A peg
						A_Peg.push_back(C_Peg.back());
						C_Peg.pop_back();

						cout << "\n\tTop disk from peg-C has moved to peg-A.";

						// display the tower of Ha Noi
						display_pegs(A_Peg, B_Peg, C_Peg);
						moved = true;
					}
					else
					{
						cout << "\n\tERROR: Cannot make the move. Top disk(" << C_Peg.back() << ") of peg-C, is larger than top disk(" << A_Peg.back() << ") of peg-A.\n";
						cout << "\t\tPlease choose again.\n";
						display_pegs(A_Peg, B_Peg, C_Peg);
					}
				}
				else if (toupper(Peg2_choice) == 'B')
				{
					if (B_Peg.empty() || C_Peg.back() < B_Peg.back())
					{
						// push elemnent from B peg to C peg
						B_Peg.push_back(C_Peg.back());
						C_Peg.pop_back();

						cout << "\n\tTop disk from peg-C has moved to peg-B.";

						display_pegs(A_Peg, B_Peg, C_Peg);
						moved = true;
					}
					else
					{
						cout << "\n\tERROR: Cannot make the move. Top disk(" << C_Peg.back() << ") of peg-C, is larger than top disk(" << B_Peg.back() << ") of peg-B.\n";
						cout << "\t\tPlease choose again.\n";
						display_pegs(A_Peg, B_Peg, C_Peg);
					}
				}
				else if (toupper(Peg2_choice) == 'Q')
				{
					return;
				}
				break;
			}
			case 'Q': 
			{
				if (toupper(Peg1_choice) == 'Q' || toupper(Peg2_choice) == 'Q')
				{
					return;
				}
			}
			}

			// Keep track of the moves
			if (moved != false) 
			{
				moves++;
			}

			// Reset the flag
			moved = false;
		} while (C_Peg.size() < rings);

		// Stop the clock
		end_time = clock();

		// Calculating the time
		int game_time = (end_time - start_time) / CLOCKS_PER_SEC;

		// Get the fastest time
		fast_time[rings] = min(fast_time[rings], game_time);

		// Get the slowest time
		slow_time[rings] = max(slow_time[rings], game_time);

		// Increment how many games have been played with the discs numbers 
		total_games[rings]++;

		// Set the key to the value which is the moves now, we getting each move for each game we play
		fastest_moves_each_game[rings] = min(fastest_moves_each_game[rings], moves);
		slowest_moves_each_game[rings] = max(slowest_moves_each_game[rings], moves);

		cout << "\n\tCongratulation! You have solved the game in " << moves << " moves.\n";
		option = inputChar("\n\tPlay again? (Y-yes or N-no): ", 'y', 'n');

	} while (toupper(option) == 'Y');

	double average_seconds;

	cout << "\n\tGame statistics:\n\n";
	for (auto& i : total_games) 
	{
		// The key and The value
		int discs_overall_used = i.first;
		int games = i.second;

		if (games == 1)
		{
			// The average seconds equals to them sum of fast time and slow time then divide by games played
			average_seconds = static_cast<double>(fast_time[discs_overall_used] + slow_time[discs_overall_used]) / 2.0;
			cout << "\t" << games << " game using " << discs_overall_used << " disks was played.\n";
		}
		else
		{
			// The average seconds equals to the sum of fast time and slow time then divide by games played
			average_seconds = static_cast<double>(fast_time[discs_overall_used] + slow_time[discs_overall_used]) / games;
			cout << "\t" << games << " games using " << discs_overall_used << " disks was played.\n";
		}
		cout << "\t\tThe fastest time was " << fast_time[discs_overall_used] << " seconds in " << fastest_moves_each_game[discs_overall_used] << " moves.\n";
		cout << "\t\tThe slowest time was " << slow_time[discs_overall_used] << " seconds in " << slowest_moves_each_game[discs_overall_used] << " moves.\n";
		cout << "\t\tThe average time was " << average_seconds << " second(s)\n";
	}
}

//Precondition: three const pegs vector parameter 
//Costcondition: Display the game
void display_pegs(const vector<int>& A_Peg, const vector<int>& B_peg, const vector<int>& C_Peg) 
{
	// The greatest size between the pegs
	int maxium_rings = max(A_Peg.size(), max(B_peg.size(), C_Peg.size()));

	cout << "\n\n\tTower of Hanoi\n\n";

	// Reverse for loops to start from greatest in the bottom, smaller on the top
	for (int i = maxium_rings; i >= 0; i--) 
	{
		// Display the A Peg
		cout << "\t";
		if (i < A_Peg.size()) 
		{
			int ring_size = A_Peg[i];

			//converting it to a string
			string ring_string = to_string(ring_size);
			for (int j = 0; j < ring_string.size(); j++) 
			{
				cout << ring_string[j] << "";
			}
		}
		else 
		{
			cout << string(1, char(186)) << "";
		}
		
		// Display the B Peg
		cout << "\t";
		if (i < B_peg.size()) 
		{
			int ring_size = B_peg[i];

			//converting it to a string
			string ring_string = to_string(ring_size);
			for (int j = 0; j < ring_string.size(); j++) 
			{
				cout << ring_string[j] << "";
			}
		}
		else 
		{
			cout << string(1, char(186)) << "";
		}

		// Display the C Peg
		cout << "\t";
		if (i < C_Peg.size()) 
		{
			int ring_size = C_Peg[i];
			//converting it to a string
			string ring_string = to_string(ring_size);
			for (int j = 0; j < ring_string.size(); j++) 
			{
				cout << ring_string[j] << "";
			}
		}
		else 
		{
			cout << "" << string(1, char(186)) << "";
		}
		cout << "\n";
	}
	cout << "\t" << string(1, char(186)) << "\t" << string(1, char(186)) << "\t" << string(1, char(186)) << "\n";
	cout << "     " << string(7, char(205)) << " " << string(7, char(205)) << " " << string(7, char(205));
	cout << "\n\tA\tB\tC\n\n";
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
