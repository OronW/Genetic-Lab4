#include <string>
#include "Genetic.h"

#define TARGET			std::string("Hello world!")
#define BULLSEYE			2 * TARGET.size() * TARGET.size()
#define MAXITER			16384		
#define ELITISIM_RATE	0.2f	
#define MUTATION_RATE	0.25f		
#define MUTATION			RAND_MAX * MUTATION_RATE
#define MAXK				20



vector<double> avg_fitness;
vector<double> std_fitness;
int GA_POPSIZE;


int getTotalFitness(ga_vector &all_pop) {
	int sum = 0;
	for (int i = 0; i < GA_POPSIZE; i++)
		sum += all_pop[i].fitness;

	return sum;
}


void tournament(ga_vector &pop, ga_vector &output, int n) {
	if (n > GA_POPSIZE) {
		cout << "tournament: n too large!" << endl;
		return;
	}
	output.clear();
	int k = rand() % (MAXK - 2) + 2;
	int index;
	int best = INFINITY;
	int choice = 0;
	ga_vector t;

	for (int i = 0; i < n; i++) {	
		
		for (int j = 0; j < k; j++) {	//randomize k values
			index = rand() % GA_POPSIZE;
			t.push_back(pop[index]);
		}

		
		for (int j = 0; j < t.size(); j++) {	// find the best one
			if (t[i].fitness < best) {
				best = t[i].fitness;
				choice = i;
			}
		}

		output.push_back(t[choice]);
	}

	SUSElitism(output, pop);
}


int fitnessSum(ga_vector &all_pop, int end) {
	int fitness_sum = 0;
	for (int i = 0; i <= end && i < all_pop.size(); i++)
		fitness_sum += all_pop[i].fitness;

	return fitness_sum;

}


int BEHeuristic(string source, string target) {
	int result = 0;
	int targetSize = target.size();


	for (int i = 0; i < targetSize; i++) {
		char sourceChar = source[i];
		if (sourceChar == target[i])
			result += 2*targetSize;

		else {
			for (int j = 0; j < targetSize; j++) {
				if ((sourceChar == target[j])&&(target[j]!=source[j])) {
					result = targetSize/2;
					break;
				}
			}
		}
	}

	return BULLSEYE - result;
}

void SUS(ga_vector &all_pop, ga_vector &output, int N) {

	int F = getTotalFitness(all_pop);
	int P = floor(F / N);
	int index;
	
	int start = rand() % P;		// start with random number between 0 and P
	vector<int> Points;
	for (int i = 1; i < N; i++) {
		index = start + i * P;
		Points.push_back(index);
	}
	RWS(all_pop, Points, output);

	SUSElitism(output, all_pop);
}

void SUSElitism(ga_vector &output, ga_vector &pop) {

	int i = output.size();
	int i1, i2, spos;
	int tsize = TARGET.size();
	string str;


	while (output.size() < GA_POPSIZE) {	//mate and add to output
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);
		spos = rand() % tsize;

		str = pop[i1].str.substr(0, spos) + pop[i2].str.substr(spos, tsize - spos);
		ga_struct citizen;
		citizen.fitness = 0;
		citizen.str = str;

		output.push_back(citizen);

		if (rand() < MUTATION)
			mutate(output[i]);

		i++;
	}

}

void RWS(ga_vector &all_pop, vector<int> &Points, ga_vector &Keep) {
	int numOfPoints = Points.size();
	int fitness_threshold, j;
	int last = 0;
	Keep.clear();
	for (int i = 0; i < numOfPoints; i++) { //find citizen with grater fitness
		fitness_threshold = Points[i];
		j = 0;
		while (fitnessSum(all_pop, j) < fitness_threshold) {
			j++;
		}

		if (j > GA_POPSIZE) {
			cout << "RWS: next pop index j out of bounds!" << endl;
			return;
		}

		ga_struct citizen;
		citizen.str = all_pop[j].str;
		citizen.fitness = all_pop[j].fitness;
		Keep.push_back(citizen);

	}
}




bool goalState(string source) {
	bool s = source.compare(TARGET);
	return (!s);
}

void BEFitness(ga_vector &all_pop)
{
	string target = TARGET;
	int tsize = target.size();
	unsigned int fitness;
	double avg = 0;
	double std = 0;

	for (int i = 0; i<GA_POPSIZE; i++) {
		fitness = BEHeuristic(all_pop[i].str, target);
		all_pop[i].fitness = fitness;
		avg += fitness;
	}

	avg = avg / GA_POPSIZE;
	avg_fitness.push_back(avg);

	for (int i = 0; i<GA_POPSIZE; i++) {
		std += pow(all_pop[i].fitness - avg, 2);
	}

	std = sqrt(std / GA_POPSIZE);
	std_fitness.push_back(std);
}


string uniform_cross(string source1, string source2) {
	int n = source1.size();
	string result = source1;

	for (int i = 0; i < n; i++) {
		if (rand() % 2 == 1)
			result[i] = source2[i];
	}

	return result;
}



string smartXbreed(string source1, string source2, int fitness1, int fitness2) {
	int n = source1.size();
	string result = source1;
	if (fitness1 == 0)
		return source1;
	if (fitness2 == 0)
		return source2;
	if (fitness2 == fitness1)
		return uniform_cross(source1, source2);

	
	double p1 = double(fitness2) / double(fitness1);
	double p2 = double(fitness1) / double(fitness2);

	
	if (p1 < p2)
		p2 = 1 - p1;
	else if (p2 < p1)
		p1 = 1 - p2;
	else {
		cout << "probabilities are out of bounds" << endl;
		return  uniform_cross(source1, source2);
	}

	//apply cross
	for (int i = 0; i < n; i++) {
		if (rand() < p2)
			result[i] = source2[i];
	}

	return result;
}



void initAllPop(ga_vector &all_pop, ga_vector &buffer)
{
	int tsize = TARGET.size();

	for (int i = 0; i<GA_POPSIZE; i++) {
		ga_struct citizen;

		citizen.fitness = 0;
		citizen.str.erase();

		for (int j = 0; j<tsize; j++)
			citizen.str += (rand() % 95) + 32;

		all_pop.push_back(citizen);
	}

	buffer.resize(GA_POPSIZE);
}

void calcFit(ga_vector &all_pop)
{
	string target = TARGET;
	int tsize = target.size();
	unsigned int fitness;
	double avg = 0;
	double std = 0;
	for (int i = 0; i<GA_POPSIZE; i++) {
		fitness = 0;
		for (int j = 0; j<tsize; j++) {
			fitness += abs(int(all_pop[i].str[j] - target[j]));
		}

		all_pop[i].fitness = fitness;
		avg += fitness;
	}

	avg = avg / GA_POPSIZE;
	avg_fitness.push_back(avg);

	for (int i = 0; i<GA_POPSIZE; i++) {
		std += pow(all_pop[i].fitness - avg, 2);
	}

	std = sqrt(std / GA_POPSIZE);
	std_fitness.push_back(std);
}

bool fitSort(ga_struct x, ga_struct y)
{
	return (x.fitness < y.fitness);
}

inline void sortAccToFit(ga_vector &all_pop)
{
	sort(all_pop.begin(), all_pop.end(), fitSort);
}

void elitism(ga_vector &all_pop,	ga_vector &buffer, int esize)
{
	for (int i = 0; i<esize; i++) {
		buffer[i].str = all_pop[i].str;
		buffer[i].fitness = all_pop[i].fitness;
	}
}

void mutate(ga_struct &member)
{
	int tsize = TARGET.size();
	int ipos = rand() % tsize;
	int delta = (rand() % 90) + 32;

	member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

void onePointCross(ga_vector &all_pop, ga_vector &buffer )
{
	int esize = GA_POPSIZE * ELITISIM_RATE;
	int tsize = TARGET.size(), spos, i1, i2;
	for (int i = esize; i < GA_POPSIZE; i++) {
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);
		spos = rand() % tsize;

		buffer[i].str = all_pop[i1].str.substr(0, spos) +
			all_pop[i2].str.substr(spos, tsize - spos);
	}
}

void mate(ga_vector &all_pop, ga_vector &buffer, int cross_type, double mutation_rate)
{
	int esize = GA_POPSIZE * ELITISIM_RATE;
	int tsize = TARGET.size(), spos, i1, i2;

	elitism(all_pop, buffer, esize);

	// Mate the rest
	for (int i = esize; i<GA_POPSIZE; i++) {
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);
		spos = rand() % tsize;

		if (cross_type==1)	//siungle point
			buffer[i].str = all_pop[i1].str.substr(0, spos) + all_pop[i2].str.substr(spos, tsize - spos);
		else if (cross_type==2)	// uniform
			buffer[i].str = uniform_cross(all_pop[i1].str, all_pop[i2].str);
		else if (cross_type == 3)	//smart
			buffer[i].str = smartXbreed(all_pop[i1].str, all_pop[i2].str, all_pop[i1].fitness, all_pop[i2].fitness);
		else
		{
			cout << "mate error: unknown cross type" << endl;
			return;
		}

		if (rand() < mutation_rate) mutate(buffer[i]);
	}
}


inline void printResOfBest(ga_vector &gav)
{
	cout << "Best: " << gav[0].str << " (" << gav[0].fitness << ")" << endl;
}

inline void printStatOf()
{
	cout << "Average Fitness: " << avg_fitness.back() << endl << "STD Fitness: " << std_fitness.back() << endl;
}

inline void swap(ga_vector *&all_pop,	ga_vector *&buffer)
{
	ga_vector *temp = all_pop; all_pop = buffer; buffer = temp;
}






bool solveUsingGen(int N, int itr, int h, int cross_type, double mutation_rate, int selection_type) {
	GA_POPSIZE = N;
	clock_t start = clock();
	bool success = false;
	ga_vector pop_alpha, pop_beta;
	ga_vector *all_pop, *buffer;

	initAllPop(pop_alpha, pop_beta);
	all_pop = &pop_alpha;
	buffer = &pop_beta;

	for (int i = 0; i<itr; i++) {

		if (h==1)
			calcFit(*all_pop);
		else if (h==2)
			BEFitness(*all_pop);
		else {
			cout << "solveUsingGen: unknown h type" << endl;
			return false;
		}

		sortAccToFit(*all_pop);	// sort them
		printResOfBest(*all_pop);		// print the best one
		printStatOf();

		if (goalState((*all_pop)[0].str)) {
			success = true;
			cout << "done" << endl;
			cout << "********" << endl;
			cout << "time data:" << endl;
			break;
		}

		if (selection_type==1)
			mate(*all_pop, *buffer, cross_type, mutation_rate);		// mate the all_pop together
		else if (selection_type == 2)
			SUS(*all_pop, *buffer, floor(10));
		else if (selection_type == 3)
			tournament(*all_pop, *buffer, 20);
		else {
			cout << "solve_pop: invalid selection type" << endl;
			return false;
		}


		swap(all_pop, buffer);		// swap buffers
	}

	double time = clock() - start;
	cout << "Total clicks: " << time << endl;
	cout << "Total Time: " << (float)time / CLOCKS_PER_SEC << endl;

	return success;
}
