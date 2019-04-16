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
#include <ctime>


int main()
{
	srand(unsigned(time(NULL)));
	
	clock_t startElapsed;
	double elapsedDuration;
	
	startElapsed = clock();

	solveUsingGen(5000, 500, 1, 1, 0.1, 3);
		//			(popSize,  ,crossbreed , Heuristic, muatation, selection)
		//						1-eltism,	1-Manhattan,	rate,	1-single	
		//						2-SUS,		2-BE					2-Unifrm
		//						3-Tour								3-smrt
		
	//solveQueensProb(1000, 1000, 1, 0.2);
		//		(popSize,  crossbreed,  muatation)
		//					1-eltism,		rate	
		//					2-SUS,						
		//					3-Tour				


	//solveQueensConflict(1000, 20000);
		//			(popSize,  iteration)

	//solveSack(1000, 2000, 1);
		//	(popSize ,iteration , cross)


	elapsedDuration = (clock() - startElapsed) / (double)CLOCKS_PER_SEC;

	system("pause");

	return 0;
}