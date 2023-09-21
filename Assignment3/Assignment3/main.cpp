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
void printPegs(const vector<int>& pegA, const vector<int>& pegB, const vector<int>& pegC);

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
	char playAgain;
	int ringsNumber;
	int moves, discsTotalNumber = 64;
	//using vector STL for my all 3 pegs of the disc
	vector<int> pegA, pegB, pegC;
	char choicePeg1, choicePeg2;
	//going to use map STL to keep track of each moves and how fast they go, and total moves, and the game counts as well
	map<int, int> fastTime, slowTime, gameCount, movesEachGameFast, movesEachGameSlow;
	clock_t startTime, endTime;
	//turning the fastestTime to int max which is (2147483647)
	for (int i = 1; i <= discsTotalNumber; ++i) {
		fastTime[i] = INT_MAX;
		movesEachGameFast[i] = INT_MAX;
	}
	do {
		system("cls");
		cout << "\n\tThe Tower of Hanoi also called the Tower of Brahma or Lucas' Tower is a mathematical game.\n"
			"\tIt consists of three pegs and a number of rings of different sizes, which can slide onto\n"
			"\tany peg.The game starts with the rings in a neat stack in ascending order of size on one\n"
			"\tpeg, the smallest at the top, thus making a conical shape.\n"
			"\n\tThe objective of the game is to move the entire stack from the starting peg - A to ending peg - B,\n"
			"\tobeying the following simple rules:\n"
			"\n\t\t1. Only one disk can be moved at a time.\n"
			"\t\t2. Each move consists of taking the upper disk from one of the stacks and\n"
			"\t\t   placing it on top of another stack or on an empty peg.\n"
			"\t\t3. No larger disk may be placed on top of a smaller disk.\n";
		//clear the elements so it does not keep adding them 
		pegA.clear();
		pegB.clear();
		pegC.clear();
		moves = 0;

		ringsNumber = inputInteger("\n\tEnter the number of rings (1..64) to begin: ", 1, 64);
		//getting the time start, start here
		startTime = clock();
		//get the pegs to go in A but will print the greatest number in the bottom and smallest in the top, start with ring number then decrement
		for (int i = ringsNumber; i >= 1; i--) {
			//push the elements to pegA, from descending: Ex ringsNumber=4; 4 3 2 1
			pegA.push_back(i);
		}
		printPegs(pegA, pegB, pegC);
		//checking if the move was valid or not
		bool moved = false;
		do {
			choicePeg1 = inputChar("\n\tSelect the top disk from the start peg (A, B, C, or Q-quit): ", (static_cast<string>("ABCQ")));
			choicePeg2 = inputChar("\tSelect the end peg (A, B, C, or Q-quit) to move the selected disk: ", (static_cast<string>("ABCQ")));
			switch (toupper(choicePeg1)) {
			case 'A': {
				//check if pegA is empty
				if (pegA.empty()) {
					cout << "\n\tERROR: Cannot make the move. There is no disk in the selected peg-A.\n";
					cout << "\t\tPlease choose again.";
					printPegs(pegA, pegB, pegC);
					break;
				}
				if (toupper(choicePeg2) == 'B') {
					//if pegB has no disc OR pegA is less than pegB run this
					if (pegB.empty() || pegA.back() < pegB.back()) {
						//get pegA from the back(last element) and push it to pegB
						pegB.push_back(pegA.back());
						//now pop it from pegA since we dont want it there no more (in pegA)
						pegA.pop_back();
						cout << "\n\tTop disk from peg-A has moved to peg-B.";
						//print the Tower of Hanoi
						printPegs(pegA, pegB, pegC);
						//flag it to true to show that the move was valid (do it for the other cases)
						moved = true;
					}
					else {
						cout << "\n\tERROR: Cannot make the move. Top disk(" << pegA.back() << ") of peg-A, is larger than top disk(" << pegB.back() << ") of peg-B.\n";
						cout << "\t\tPlease choose again.\n";
						printPegs(pegA, pegB, pegC);
					}
				}
				else if (toupper(choicePeg2) == 'C') {
					if (pegC.empty() || pegA.back() < pegC.back()) {
						//get pegA from the back(last element) now push to pegC
						pegC.push_back(pegA.back());
						pegA.pop_back();
						cout << "\n\tTop disk from peg-A has moved to peg-C.";
						//print the Tower of Hanoi
						printPegs(pegA, pegB, pegC);
						moved = true;
					}
					else {
						cout << "\n\tERROR: Cannot make the move. Top disk(" << pegA.back() << ") of peg-A, is larger than top disk(" << pegC.back() << ") of peg-C.\n";
						cout << "\t\tPlease choose again.\n";
						printPegs(pegA, pegB, pegC);
					}
				}
				else if (toupper(choicePeg2) == 'Q') {
					return;
				}
			}
					break;
			case 'B': {
				//check if pegB is empty
				if (pegB.empty()) {
					cout << "\n\tERROR: Cannot make the move. There is no disk in the selected peg-B.\n";
					cout << "\t\tPlease choose again.";
					printPegs(pegA, pegB, pegC);
					break;
				}
				if (toupper(choicePeg2) == 'A') {
					//if pegA has no disc OR pegB is less than pegA run this
					if (pegA.empty() || pegB.back() < pegA.back()) {
						//get pegB from the back(last element) now push to pegA
						pegA.push_back(pegB.back());
						//now pop it from pegB since we dont want it there no more (in pegB)
						pegB.pop_back();
						cout << "\n\tTop disk from peg-B has moved to peg-A.";
						printPegs(pegA, pegB, pegC);
						moved = true;
					}
					else {
						cout << "\n\tERROR: Cannot make the move. Top disk(" << pegB.back() << ") of peg-B, is larger than top disk(" << pegA.back() << ") of peg-A.\n";
						cout << "\t\tPlease choose again.\n";
						printPegs(pegA, pegB, pegC);
					}
				}
				else if (toupper(choicePeg2) == 'C') {
					if (pegC.empty() || pegB.back() < pegC.back()) {
						//get pegB from the back(last element) now push to pegC
						pegC.push_back(pegB.back());
						pegB.pop_back();
						cout << "\n\tTop disk from peg-B has moved to peg-C.";
						printPegs(pegA, pegB, pegC);
						moved = true;
					}
					else {
						cout << "\n\tERROR: Cannot make the move. Top disk(" << pegB.back() << ") of peg-B, is larger than top disk(" << pegC.back() << ") of peg-C.\n";
						cout << "\t\tPlease choose again.\n";
						printPegs(pegA, pegB, pegC);
					}
				}
				else if (toupper(choicePeg2) == 'Q') {
					return;
				}
			}
					break;
			case 'C': {
				//check if pegC is empty
				if (pegC.empty()) {
					cout << "\n\tERROR: Cannot make the move. There is no disk in the selected peg-C.\n";
					cout << "\t\tPlease choose again.";
					printPegs(pegA, pegB, pegC);
					break;
				}
				if (toupper(choicePeg2) == 'A') {
					if (pegA.empty() || pegC.back() < pegA.back()) {
						//get pegC from the back(last element) now push to pegA
						pegA.push_back(pegC.back());
						//now pop it from pegC since we dont want it there no more (in pegC)
						pegC.pop_back();
						cout << "\n\tTop disk from peg-C has moved to peg-A.";
						printPegs(pegA, pegB, pegC);
						moved = true;
					}
					else {
						cout << "\n\tERROR: Cannot make the move. Top disk(" << pegC.back() << ") of peg-C, is larger than top disk(" << pegA.back() << ") of peg-A.\n";
						cout << "\t\tPlease choose again.\n";
						printPegs(pegA, pegB, pegC);
					}
				}
				else if (toupper(choicePeg2) == 'B') {
					if (pegB.empty() || pegC.back() < pegB.back()) {
						//get pegC from the back(last element) now push to pegB
						pegB.push_back(pegC.back());
						pegC.pop_back();
						cout << "\n\tTop disk from peg-C has moved to peg-B.";
						printPegs(pegA, pegB, pegC);
						moved = true;
					}
					else {
						cout << "\n\tERROR: Cannot make the move. Top disk(" << pegC.back() << ") of peg-C, is larger than top disk(" << pegB.back() << ") of peg-B.\n";
						cout << "\t\tPlease choose again.\n";
						printPegs(pegA, pegB, pegC);
					}
				}
				else if (toupper(choicePeg2) == 'Q') {
					return;
				}
			}
					break;
			case 'Q': {
				if (toupper(choicePeg1) == 'Q' || toupper(choicePeg2) == 'Q') {
					return;
				}
			}
			}
			//if the moved was valid then increment, keep track how many moves we do
			if (moved != false) {
				moves++;
			}
			//flag it back to false, to then check again if the move was valid
			moved = false;
		} while (pegC.size() < ringsNumber);
		//getting the end start, use clock() function after pegC has all the discs
		endTime = clock();
		//calculating the time, subtract the end time to the start time
		int gameTimeInSeconds = (endTime - startTime) / CLOCKS_PER_SEC;
		//set the ringsNumber(key) = to the min of the value (ringsNumber-> fastTime)
		fastTime[ringsNumber] = min(fastTime[ringsNumber], gameTimeInSeconds);
		//getting the max, meaning the time that is the longest
		slowTime[ringsNumber] = max(slowTime[ringsNumber], gameTimeInSeconds);
		//increment how many games have been played with the discs numbers (ringnumbers)
		gameCount[ringsNumber]++;

		//set the key(ringNumbers) to the value which is the moves now, we getting each move for each game we play
		movesEachGameFast[ringsNumber] = min(movesEachGameFast[ringsNumber], moves);
		movesEachGameSlow[ringsNumber] = max(movesEachGameSlow[ringsNumber], moves);

		cout << "\n\tCongratulation! You have solved the game in " << moves << " moves.\n";
		playAgain = inputChar("\n\tPlay again? (Y-yes or N-no): ", 'y', 'n');
	} while (toupper(playAgain) == 'Y');
	double averageSeconds;
	cout << "\n\tGame statistics:\n\n";
	for (auto& i : gameCount) {
		//get the key and the second is the value
		int discsOverallUsed = i.first;
		int games = i.second;
		//if 1 then there are only 1 game being played
		if (games == 1) {
			//getting the average seconds, have to add fast time + slow time then divide by games played
			averageSeconds = static_cast<double>(fastTime[discsOverallUsed] + slowTime[discsOverallUsed]) / 2.0;
			cout << "\t" << games << " game using " << discsOverallUsed << " disks was played.\n";
		}
		else {
			//getting the average seconds, have to add fast time + slow time then divide by games played
			averageSeconds = static_cast<double>(fastTime[discsOverallUsed] + slowTime[discsOverallUsed]) / games;
			cout << "\t" << games << " games using " << discsOverallUsed << " disks was played.\n";
		}
		cout << "\t\tThe fastest time was " << fastTime[discsOverallUsed] << " seconds in " << movesEachGameFast[discsOverallUsed] << " moves.\n";
		cout << "\t\tThe slowest time was " << slowTime[discsOverallUsed] << " seconds in " << movesEachGameSlow[discsOverallUsed] << " moves.\n";
		cout << "\t\tThe average time was " << averageSeconds << " second(s)\n";
	}
}

//precondition: function is going to have 3 vector as parameters (argu)
//postcondition: function is going to update the pegs in order of how they are moving
void printPegs(const vector<int>& pegA, const vector<int>& pegB, const vector<int>& pegC) 
{
	//get the greatest size between pegA, pegB, and pegC to check how many discs can it print out
	int maxRings = max(pegA.size(), max(pegB.size(), pegC.size()));
	cout << "\n\n\tTower of Hanoi\n\n";
	//reverse the numbers, starting from greatest in the bottom, smaller on the top (displaying wise)
	for (int i = maxRings; i >= 0; i--) {
		//print peg A
		cout << "\t";
		//check if the maxRings is less than the size in pegA
		if (i < pegA.size()) {
			int ringSize = pegA[i];
			//converting it to a string
			string ringString = to_string(ringSize);
			for (int j = 0; j < ringString.size(); j++) {
				cout << ringString[j] << "";
			}
		}
		else {
			cout << string(1, char(186)) << "";
		}
		//print peg B
		cout << "\t";
		//check if the maxRings is less than the size in pegB
		if (i < pegB.size()) {
			int ringSize = pegB[i];
			//converting it to a string
			string ringString = to_string(ringSize);
			for (int j = 0; j < ringString.size(); j++) {
				cout << ringString[j] << "";
			}
		}
		else {
			cout << string(1, char(186)) << "";
		}
		//print peg C
		cout << "\t";
		//check if the maxRings is less than the size in pegC
		if (i < pegC.size()) {
			int ringSize = pegC[i];
			//converting it to a string
			string ringString = to_string(ringSize);
			for (int j = 0; j < ringString.size(); j++) {
				cout << ringString[j] << "";
			}
		}
		else {
			cout << "" << string(1, char(186)) << "";
		}
		cout << endl;
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
