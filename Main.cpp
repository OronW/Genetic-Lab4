#ifdef CHECK

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	return 0;
}

#endif

#pragma warning(disable:4786)		// disable debug warning

#include "Genetic.h"
#include "QueenProblem.h"
#include "OtherProb.h"
#include "sack01.h"
#include "BaldwinEffect.h"
#include "Alec.h"
#include <ctime>

void init_gen() {
	int N;
	int h;
	int cross;
	double mutate;
	int selection;

	cout << "Please enter the following data - " << endl;
	cout << "Population:";
	cin >> N;
	cout << "Heuristic - " << endl;
	cout << "1 Distance" << endl;
	cout << "2 BE" << endl;
	cin >> h;
	cout << "Cross -" << endl;
	cout << "1 Single point" << endl;
	cout << "2 Uniform" << endl;
	cin >> cross;
	cout << "Mutation rate (between 0 and 1) -";
	cin >> mutate;
	cout << "Selection -" << endl;
	cout << "1 Elitism" << endl;
	cout << "2 SUS" << endl;
	cout << "3 Tournament" << endl;
	cin >> selection;

	solveUsingGen(N, 1000, cross, h, mutate, selection);
		//			(popSize,	iterations	,crossbreed		,Heuristic,		muatation,	selection)
		//									1-single,		1-Manhattan,	rate,		1-eltism	
		//									2-Unifrm,		2-BE						2-SUS
		//									3-smrt										3-Tour

}

void init_queens() {
	int N;
	int selection;
	int cross;
	int mutate;

	cout << "Please enter the following data - " << endl;
	cout << "Board size -";
	cin >> N;
	cout << "Cross-" << endl;
	cout << "1 Single Point" << endl;
	cout << "2 Uniform" << endl;
	cin >> cross;
	cout << "Mutation type -" << endl;
	cout << "1 Randomly change position" << endl;
	cout << "2 Choose randomly minimal conflict" << endl;
	cin >> mutate;

	solveQueensProb(N, 500, cross, mutate);
		//		(board_size		,iterations,	crossbreed,		muatation)
		//										1-single,		type	
		//										2-Unifrm						

}

void init_sack() {
	int N;
	int cross;

	cout << "Please enter the following data - " << endl;
	cout << "Problem number (0-7) -";
	cin >> N;
	cout << "Cross -" << endl;
	cout << "1 Single Point" << endl;
	cout << "2 Uniform" << endl;
	cin >> cross;

	solveSack(N, 500, cross);
	//	(poblem_num ,iteration , cross)
}

void init_qls() {
	int N;

	cout << "Please enter the following data - " << endl;
	cout << "Board size:";
	cin >> N;

	solveQueensConflict(N, 10000);
	//			(board_size,  iteration)
}

void choose_prob() {
	int input;
	cout << "Please choose:" << endl;
	cout << "1 Genetics" << endl;
	cout << "2 N queens" << endl;
	cout << "3 N queens - local search" << endl;
	cout << "4 Sack" << endl;
	cout << "5 Baldwin" << endl;
	cin >> input;
	if (input == 1)
		init_gen();
	else if (input == 2)
		init_queens();

	else if (input == 3)
		init_qls();

	else if (input == 4)
		init_sack();
	else if (input == 5) {
		cout << "Running the configurations as requested in the assignment: " << endl;
		cout << "1000 samples" << endl;
		cout << "1000 iterations" << endl;
		cout << "20 lenght" << endl;
		cout << "25% - 1 , 25% - 0 , 50% - ?" << endl;
		solveBaldwin();
	}
	else {
		cout << "Invalid option" << endl;
		return;
	}
}

void testQueensGA(int epoch, int N, int cross_type = 1, int mutatation_type = 2) {
	double time;
	int success = 0;
	clock_t t = clock();
	for (int i = 0; i < epoch; i++) {
		if (solveQueensProb(N, 500, cross_type, mutatation_type))
			success++;
	}
	time = double((clock() - t) / CLOCKS_PER_SEC);
	double avg_time = time / epoch;
	double rate = double(success) / epoch;

	cout << endl << endl;
	cout << "******************************************************" << endl;
	cout << "AVERAGE TOTALS FOR " << N << " QUEENS PROBLEM (Genetic Algorithm):" << endl;
	cout << "Success rate: " << rate << endl;
	cout << "Average time: " << avg_time << endl;
}

void testPop(int epoch, int N = 2048, int itr = 1000, int h = 2, int cross_type = 1, double mutation_rate = 0.25, int selection_type = 1) {
	double time;
	int success = 0;
	cout << "mutation_rate = " << mutation_rate << endl;
	clock_t t = clock();
	for (int i = 0; i < epoch; i++) {
		if (solveUsingGen(N, itr, h, cross_type, mutation_rate, selection_type)) {
			//(solve_genetics(2000, 500, 1,2,0.250)
			//int N, int itr, int h, int cross_type, int mutation_rate
			cout << "Success!" << endl;
			success++;
		}
	}
	time = double((clock() - t) / CLOCKS_PER_SEC);
	double avg_time = time / epoch;
	double rate = double(success) / epoch;

	cout << endl << endl;
	cout << "******************************************************" << endl;
	cout << "AVERAGE TOTALS FOR " << N << " POPULATION PROBLEM:" << endl;
	cout << "Success rate: " << rate << endl;
	cout << "Average time: " << avg_time << endl;
}

int main()
{
	srand(unsigned(time(NULL)));
	
	clock_t startElapsed;
	double elapsedDuration;
	
	startElapsed = clock();
	choose_prob();
	//solveBaldwin();
	//testQueensGA(5, 20, 1, 1);

	//testPop(1, 2048, 1000, 1, 1, 0.25, 1);
	//solveUsingGen(2048, 1000, 1, 2, 0.25, 1);
		//			(popSize,	iterations	,crossbreed		,Heuristic,		muatation,	selection)
		//									1-single,		1-Manhattan,	rate,		1-eltism	
		//									2-Unifrm,		2-BE						2-SUS
		//									3-smrt										3-Tour
		
	//solveQueensProb(8, 500, 1, 2);
		//		(board_size		,iterations,	crossbreed,		muatation)
		//										1-single,		type	
		//										2-Unifrm						


	//solveQueensConflict(8, 20000);
		//			(board_size,  iteration)
	//for (int i = 0; i < 8; i++) {
	//	solveSack(i, 500, 1);
	//}
		//	(poblem_num ,iteration , cross)


	elapsedDuration = (clock() - startElapsed) / (double)CLOCKS_PER_SEC;

	system("pause");

	return 0;
}