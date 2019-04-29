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
	solveBaldwin();
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


	//solveQueensConflict(1000, 20000);
		//			(popSize,  iteration)
	//for (int i = 0; i < 8; i++) {
	//	solveSack(i, 500, 1);
	//}
		//	(poblem_num ,iteration , cross)


	elapsedDuration = (clock() - startElapsed) / (double)CLOCKS_PER_SEC;

	system("pause");

	return 0;
}