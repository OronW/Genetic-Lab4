#include "BaldwinEffect.h"
#include "Alec.h"


string printSqequence(vector<int> gen)
{
	if (gen.empty()) {
		return "";
	}
	string s = "";
	for (int i = 0; i < gen.size(); i++) {
		if (gen[i] == 2) {
			s.append("?");
		}
		else {
			s.append(to_string(gen[i]));
		}
	}
	return s;
}

bool checkIfEqual(vector<Alec*> all_pop)
{
	Alec * first = new Alec(*(all_pop[0]));
	for (vector<Alec*>::iterator a = all_pop.begin() +1 ; a != all_pop.end(); ++a) {
		if (!((*first) == (**a))) {
			return false;
		}
	}

	return true;
}

void getGenStats(vector<Alec*> all_pop, double * res)
{
	fill(res, res + sizeof(res)-1, 0);
	for (vector<Alec*>::iterator a = all_pop.begin(); a != all_pop.end(); ++a) {
		int * stats = calcStat((**a).getGen());
		res[0] += stats[0];
		res[1] += stats[1];
		res[2] += stats[2];
	}
	double sum = res[0] + res[1] + res[2];
	res[0] /= sum;
	res[1] /= sum;
	res[2] /= sum;
}

bool solveBaldwin(int samples, int itr, int lenght, double set_rate)
{
	vector<Alec*> all_pop;
	for (int i = 0; i < samples; i++) {
		all_pop.push_back(new Alec(i, lenght, set_rate));
	}

	int generation = 0;
	double statistics[3] = { 0 };
	getGenStats(all_pop, statistics);
	double timestamp = (double)clock();

	cout << "Timestamp: " << timestamp << endl;
	while (!checkIfEqual(all_pop)) {
		cout << "Generation #" << generation << ":\t0 -> " << statistics[0]*100 << "%\t1 -> " << statistics[1]*100 << "%\t? -> " << statistics[2]*100 << "%"<<endl;
		map <Alec*, double> map_btoFit;
		vector<Alec*> oFit;
		double sum_btoFit = 0.;

		for (vector<Alec*>::iterator a = all_pop.begin(); a != all_pop.end(); ++a) {
			double fitness = (**a).calcFitness();
			if (fitness > 1) {
				map_btoFit.insert(pair<Alec*,double>(*a, fitness));
				sum_btoFit += fitness;
			}
			else {
				oFit.push_back(*a);
			}
		}
		vector<Alec*> mix;
		for (int i = 0; i < samples; i++) {
			Alec * samp1 = sampleFunc(map_btoFit, oFit, sum_btoFit);

			Alec* samp2 = sampleFunc(map_btoFit, oFit, sum_btoFit);
			Alec* newSamp = mate(i, *samp1, *samp2);
			mix.push_back(newSamp);
		}
		all_pop = mix;

		getGenStats(all_pop,statistics);
		generation+=1;
	}
	cout << "Done!! Population is now fixated.\nFinal Gene - " << printSqequence((*all_pop[0]).getGen()) <<
		"\nStatistics:\t0 -> " << statistics[0] << "%\t1 -> " << statistics[1] << "%\t ? -> " << statistics[2] << "%"<<endl;
	return true;
}
