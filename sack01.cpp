#include "sack01.h"
#include "OtherProb.h"

#define SACK_POPULATION 2048
#define SACK_ELITISIM 0.10f
#define SACK_MUTATION_RATE 25



void init_items(itemVector &items, Prob &p) {

	for (unsigned int i = 0; i < p.weights.size(); i++) {
		item it;
		it.weight = p.weights[i];
		it.value = p.val[i];
		items.push_back(it);
	}

}

void init_sack01(sackVector &sack01, itemVector &items, Prob &p) {

	init_items(items, p);

	for (int i = 0; i < SACK_POPULATION; i++) {
		sackStruct sack;
		generateSack(sack, items, p.capacity);
		sack01.push_back(sack);
	}
}

void generateSack(sackStruct &sack, itemVector &items, int C) {

	sack.avail = items.size();
	sack.capacity = C;

	for (int i = 0; i < sack.avail; i++) {
		sack.items += "0";
	}

	while (getWeight(sack, items) < sack.capacity) {
		int t = rand() % sack.avail;
		sack.items[t] = '1';
	}
	fixWeight(sack, items);
}

int getWeight(sackStruct &sack, itemVector &items)
{
	int sum = 0;
	for (int i = 0; i < sack.avail; i++)
	{
		if (sack.items[i] == '1')
			sum += items[i].weight;
	}
	return sum;
}

int firstIndexItem(sackStruct &sack) {
	int empty = -1;
	for (int i = 0; i < sack.avail; i++) {	//lowest index inside
		if (sack.items[i] == '1') {
			return i;
		}
	}
	return empty;
}


void fixWeight(sackStruct &sack, itemVector &items)
{
	while (getWeight(sack, items) > sack.capacity) {
		double ratio = 0;
		int index = firstIndexItem(sack);
		if (index == -1) {
			cout << "empty sack, check!";
			return;
		}
		int worse_item_index = getMaxRatioIndex(sack, items);
		sack.items[worse_item_index] = '0';
	}
}

int maxValueHueristic(sackStruct &sack, itemVector &items)
{
	int sum = 0;
	for (int i = 0; i < sack.avail; i++)
	{
		if (sack.items[i] == '1')
			sum += items[i].value;
	}
	return sum;
}

string crossoverSackstruct(string s1, string s2, int opt) {
	int N = s1.size();
	string output;

	if (opt == 1) {	//single point
		int t = rand() % N;
		output = s1.substr(0, t) + s2.substr(t, N - t);
	}

	else if (opt == 2) {	//uniform
		output = s1;
		for (int j = 0; j < N; j++) {
			int t = rand() % 2;
			if (t == 1)
				output[j] = s2[j];
		}
	}

	return output;
}

void mateSackStruct(sackVector &sacks, itemVector &items, int cross_type)
{

	int start = floor(SACK_ELITISIM * SACK_POPULATION) + 1;
	int end = SACK_POPULATION - start;
	int i1, i2;

	for (int i = start; i < end; i++) {
		i1 = rand() % (SACK_POPULATION / 2);
		i2 = rand() % (SACK_POPULATION / 2);

		
		string str = crossoverSackstruct(sacks[i1].items, sacks[i2].items, cross_type); //use crossover to update list
		sacks[i].items = str;

	
		if (rand() % 100 < SACK_MUTATION_RATE)
			mutateSack(sacks[i], items);

		
		sacks[i].fitness = 0;	
		fixWeight(sacks[i], items);	//make vector
	}
}

double getRatio(struct item item) {
	return item.weight / item.value;
}


int getMaxRatioIndex(sackStruct &sack, itemVector &items) {
	double ratio = 0;
	int index = firstIndexItem(sack);
	double tempRatio;

	for (int i = index; i < sack.avail; i++)
	{
		if (sack.items[i] == '1')
		{
			tempRatio = getRatio(items[i]);
			if (tempRatio > ratio)
			{
				ratio = tempRatio;
				index = i;
			}
		}
	}

	return index;
}


int getMinRatioIndex(sackStruct &sack, itemVector &items) {
	double ratio = INFINITY;
	int index = firstIndexItem(sack);
	double tempRatio;

	for (int i = index; i < sack.avail; i++)
	{
		if (sack.items[i] == '0')
		{
			tempRatio = getRatio(items[i]);
			if (tempRatio < ratio)
			{
				ratio = tempRatio;
				index = i;
			}
		}
	}

	return index;
}


void mutateSack(sackStruct &sack, itemVector &items) {
	int N = sack.items.size();{
		int worse_item_id = getMaxRatioIndex(sack, items);
		int best_item_id = getMinRatioIndex(sack, items);
		sack.items[worse_item_id] = '0';
		sack.items[best_item_id] = '1';
	}
}




void calcSackFits(sackVector &sacks, itemVector &items) {
	for (unsigned int i = 0; i < sacks.size(); i++) {
		sacks[i].fitness = maxValueHueristic(sacks[i], items);
	}
}


bool MinimumPrice(sackStruct x, sackStruct y) {
	return (x.fitness < y.fitness);
}

bool MaximumPrice(sackStruct x, sackStruct y) {
	return (x.fitness > y.fitness);
}

inline void sortMinimumPrice(sackVector &population) {
	sort(population.begin(), population.end(), MinimumPrice);
}

inline void sortMaximumPrice(sackVector &population) {
	sort(population.begin(), population.end(), MaximumPrice);
}


void sack2str(sackStruct &sack, string &output) {
	output = "<";
	int N = sack.items.size();
	for (int i = 0; i < N; i++) {
		output += sack.items[i];
		if (i < N - 1)
			output += " ";
		else
			output += ">";
	}
}


bool solveSack(int problem, int itr, int cross_type) {
	init_problems();
	if (problem > 8 || problem < 0) {
		cout << "Invalueid problem id, can be 0-7" << endl;
		return false;
	}
	cout << "Solving sackStructsack problem: " << problem << endl;

	sackVector sack01;
	itemVector items;
	int i;
	Prob p = getProbl(problem);
	int Opt = p.max_value;
	bool success = false;

	init_sack01(sack01, items, p);


	clock_t start = clock();

	for (i = 0; i < itr; i++) {
		calcSackFits(sack01, items);
		sortMaximumPrice(sack01);
		string best;
		sack2str(sack01[0], best);
		cout << "Best: " << best << "  valueue:  " << sack01[0].fitness << endl;


		if (sack01[0].fitness == Opt) {	//test if worked
			success = true;
			break;
		}

		mateSackStruct(sack01, items, cross_type);	//else...
	}

	double ticks = clock() - start;
	double time = (float)ticks / CLOCKS_PER_SEC;

	if (success)
		cout << "Success!" << endl;
	else
		cout << "Failed!" << endl;



	cout << "****Statistics for sackStructsack Problem " << problem << "****" << endl;
	cout << "Total Time: " << time << endl;
	cout << "Total CPU ticks: " << ticks << endl;
	cout << "Total iterations: " << i << endl;

	return success;

}