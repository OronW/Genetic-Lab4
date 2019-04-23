#include "QueenProblem.h"


#define BOARDS		1000
#define ELITE 0.1f
#define MUTATION_FOR_QUEEN 20		// mutation rate
#define QLOST	3
#define QSHIMSHON 0.2
#define QYOVAV 2

int QScount;
int QYcount;


bool MinFitness(QS x, QS y) {
	return (x.fitness < y.fitness);
}

bool MaxFitness(QS x, QS y) {
	return (x.fitness > y.fitness);
}

inline void sortMinimum(QSVector &population) {
	sort(population.begin(), population.end(), MinFitness);
}

inline void sortMaximum(QSVector &population) {
	sort(population.begin(), population.end(), MaxFitness);
}


void initBoards(QSVector &Boards, QSVector &buffer, int N) {


	for (int i = 0; i < BOARDS; i++) {
		QS board;
		int square;
		board.fitness = 0;
		board.str.erase();

		for (int j = 0; j < N; j++) {
			square = rand() % N;
			board.str += square;
		}

		Boards.push_back(board);
	}
	buffer.resize(BOARDS);
}


int** gene2mat(string str) {
	int n = str.size();
	int rows = n; int cols = n;
	int** matrix = new int*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//TODO WHAT???
		}
	}

	return matrix;
}


int CountConflicts(QS &board, int i) {
	//counts the number of conflicts for queen in index i
	int N = board.str.size();
	int result = 0;

	//check queens in same column
	for (int j = 0; j < N; j++) {
		if (board.str[j] == board.str[i] && j != i)
			result++;
	}

	//check queens in same diagonal
	for (int j = 0; j < N; j++) {
		int index_diff = abs(i - j);
		int queens_diff = abs(board.str[i] - board.str[j]);
		if (index_diff > 0 && index_diff == queens_diff)
			result++;
	}

	return result;

}


int conflictsHeuristic(QS &board) {
	//gene to matrix
	int result = 0;
	int N = board.str.length();

	for (int i = 0; i < N; i++) {
		result += CountConflicts(board, i);
	}

	return result;
}


string crossover(string s1, string s2, int opt) {
	//opt 1 = single point
	//opt 2 = uniform
	int N = s1.size();
	string output;

	if (opt == 1) {
		int t = rand() % N;
		output = s1.substr(0, t) + s2.substr(t, N - t);
	}

	else if (opt == 2) {
		output = s1;
		for (int j = 0; j < N; j++) {
			int t = rand() % 2;
			if (t == 1)
				output[j] = s2[j];
		}
	}

	return output;
}


void mutate_board(QS &board, int mutate_type) {
	//type = 1 : random queen changes location
	//type = 2 : random threatened queen changes to a position that minimizes conflicts
	int N = board.str.size();

	if (mutate_type == 1 && rand() % 100 < MUTATION_FOR_QUEEN) {

		int s = rand() % N;
		int t = rand() % N;
		board.str[s] = t;
	}

	else if (mutate_type == 2) {
		int queen_ind = checkConflictedQueen(board);
		minimumConflicts(board, queen_ind);
	}
}


int checkConflictedQueen(QS &board) {
	int N = board.str.size();
	vector <int> index;

	for (int i = 0; i < N; i++) {
		if (CountConflicts(board, i) > 0) {
			index.push_back(i);
		}
	}
	if (index.size() == 0) {
		//cout << "checkConflictedQueens : no conflicted queens" << endl;
		return 0;
	}
	int t = rand() % index.size();
	return index[t];
}


void minimumConflicts(QS &board, int ind) {
	//moves queen in index [ind] to the square which minimizes conflicts (in the same column)

	int N = board.str.size();
	int original = board.str[ind];
	int min = N + 1;
	int conflicts;
	int best_location = 0;

	for (int i = 0; i < N; i++) {
		if (i != board.str[ind]) {
			board.str[ind] = i;
			//found a better position
			conflicts = CountConflicts(board, ind);
			if (conflicts < min) {
				min = conflicts;
				best_location = i;
			}
			board.str[ind] = original;
		}
	}

	board.str[ind] = best_location;
}

void BoardMating(QSVector &boards, QSVector &buffer, double percentage, int cross_type, int mutate_type) {
	// we keep all elements below start, and replace all elements after start by the next generation
	int start = floor(BOARDS * percentage) + 1;
	int end = BOARDS - start;
	int i1, i2;

	for (int i = start; i < end; i++) {
		i1 = rand() % (BOARDS / 2);
		i2 = rand() % (BOARDS / 2);

		boards[i].str = crossover(boards[i1].str, boards[i2].str, cross_type);
		boards[i].fitness = 0;

		// MUTATE
		mutate_board(boards[i], mutate_type);
	}
}


void printboard(QS &board, bool print_fitness) {
	int N = board.str.size();
	int fitness = conflictsHeuristic(board);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board.str[i] == j)
				cout << " X ";
			else
				cout << " * ";
		}
		cout << endl;
	}

	if (print_fitness)
		cout << endl << "Fitness: " << conflictsHeuristic(board) << endl;
}

void queensFitness(QSVector &boards) {
	for (int i = 0; i < BOARDS; i++) {
		boards[i].fitness = conflictsHeuristic(boards[i]);
	}
}


string boardToString(string &board) {
	string output = "<";
	for (unsigned int i = 0; i < board.size(); i++) {
		output += to_string(board[i]);
		if (i < board.size() - 1)
			output += ",";
		else
			output += ">";
	}
	return output;
}


void bestBoardPrint(QSVector &Boards) {
	string board = boardToString(Boards[0].str);
	cout << board << endl;
	cout << "Fitness: " << Boards[0].fitness << endl;

}

bool solveQueensProb(int N, int itr, int cross_type, int mutate_type) {
	QSVector Boards;
	QSVector buffer;
	initBoards(Boards, buffer, N);
	double ticks;
	double time;
	bool success = false;
	int i;
	QScount=5;
	QYcount=5;

	clock_t start = clock();

	for (i = 0; i < itr; i++) {
		queensFitness(Boards);
		sortMinimum(Boards);
		bestBoardPrint(Boards);

		//check goal state
		if (Boards[0].fitness == 0) {
			ticks = clock() - start;
			time = (float)ticks / CLOCKS_PER_SEC;
			cout << "Solution found!" << endl;
			printboard(Boards[0], false);
			success = true;
			break;
		}

		//if ((Boards)[0].fitness < QLOST) {
		//	if (catchLocalOptima(Boards,N)) {
		//		break;
		//	}
		//}

		//Problem not solved.
		BoardMating(Boards, buffer, ELITE, cross_type, mutate_type);

	}

	if (success)
		cout << "Success!" << endl;
	else {
		ticks = clock() - start;
		time = (float)ticks / CLOCKS_PER_SEC;
		cout << "Failure!" << endl;
	}

	cout << "****Statistics for N=" << N << " Queens Problem****" << endl;
	cout << "Total Time: " << time << endl;
	cout << "Total CPU ticks: " << ticks << endl;
	cout << "Total iterations: " << i << endl;

	return success;

}

bool solveQueensConflict(int N, int itr) {

	//generate random board
	QS board;
	board.fitness = 0;
	board.str.erase();
	bool success = false;

	for (int j = 0; j < N; j++) {
		int square = rand() % N;
		board.str += square;
	}

	clock_t start = clock();
	int i = 0;
	while (conflictsHeuristic(board) && i < itr) {
		int queen_ind = checkConflictedQueen(board);
		minimumConflicts(board, queen_ind);
		cout << boardToString(board.str);
		cout << "   Conflicts: " << conflictsHeuristic(board) << endl;
		i++;
	}

	if (conflictsHeuristic(board) == 0)
		success = true;

	//finished loop
	double ticks = clock() - start;
	double time = (float)ticks / CLOCKS_PER_SEC;

	if (success)
		cout << "Success!" << endl;
	else
		cout << "Failure!" << endl;

	cout << "****Statistics for N=" << N << " Queens Problem****" << endl;
	cout << "Total Time: " << time << endl;
	cout << "Total CPU ticks: " << ticks << endl;
	cout << "Total iterations: " << i << endl;
	printboard(board, false);

	return success;
}

int getBoardsDist(QS & first, QS & second, int N)
{
	string str1 = first.str;
	string str2 = second.str;
	int i = 0, count = 0;
	while (i < N) {
		if (str1[i] != str2[i]) {
			count++;
		}
		i++;
	}
	return count;
}

double getAverage(QSVector & boards, int N)
{
	double average = 0.0;
	for (int i = 0; i < N; i++) {
		average += boards[i].fitness;
	}
	average = average / N;
	return average;
}

double getVariance(QSVector & boards, int N)
{
	double average = getAverage(boards,N);
	double variance = 0.0;
	for (int i = 0; i < N; i++) {
		variance += (boards[i].fitness - average)*(boards[i].fitness - average);
	}
	variance = variance / N;
	return variance;
}

double getPopulationDist(QSVector & boards, int N)
{
	double pop_dist = 0.0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			pop_dist += getBoardsDist(boards[i], boards[j],N);
		}
	}
	pop_dist = pop_dist / (N * N);
	return pop_dist;
}

double catchLocalOptima(QSVector & boards, int N)
{
	double res = getVariance(boards, N);
	cout << "-D- var indicator :\n" << res << "\n" << endl;
	cout << "ahello " << QScount << " - " << QSHIMSHON << endl;
	if (res < QSHIMSHON) {
		cout << "hello " << QScount<<" - " << QSHIMSHON << endl;
		if (QScount == 0) {
			cout << "-E- LOCAL OPTIMA SIGNAL DETECTED (by variance)" << endl;
			return 1;
		}
		--QScount;
	}
	res = getPopulationDist(boards, N);
	cout << "-D- Dist indicator :\n" << res << "\n" << endl;
	if (res < QYOVAV) {
		cout << "bhello " << QYcount << " - " << QYOVAV << endl;
		if (QYcount == 0) {
			cout << "-E- LOCAL OPTIMA SIGNAL DETECTED (by stupid hamming distance)" << endl;
			return 1;
		}
		--QYcount;
	}
	return 0.0;
}

int randomImmigrants(QSVector & boards, int N)
{
	//int immigration_rate = (rand() % 50);
	int immigration_rate = 80;
	int square;
	cout << "-D- number of immigration rate is - " << immigration_rate << endl;
	int immigrates = floor((immigration_rate * boards.size()) / 100);
	cout << "-D- number of immigrations is - " << immigrates << endl;
	for (int i = 0; i < immigrates; ++i) {
		int kidnap = rand() % boards.size();
		//cout << "-D- kidnap is - " << kidnap << endl;
		string shabah = "";

		for (int j = 0; j < N; j++) {
			square = rand() % N;
			board.str += square;
		}

		all_pop[kidnap].str = shabah;
	}
	return 0;
}
