#include "Alec.h"
#define REWARD 19


vector<int> Alec::getGen() const
{
	return gen;
}

Alec::Alec(Alec & other)
{
	name = other.name;
	attempts = other.attempts;
	gen = other.gen;
}

Alec::Alec(int _name, vector<int> _gen)
{
	name = _name;
	gen = _gen;
}

Alec::Alec(int _name, int _len, double _set_rate)
{
	int i = 0;
	name = _name;
	for (; i < _len * _set_rate; ++i) {
		gen.push_back(2);
	}
	for (; i < _len; ++i) {
		int value = rand() % 2;
		gen.push_back(value);
	}
	random_shuffle(gen.begin(), gen.end());
}


double Alec::calcFitness()
{
	int gsize = gen.size();
	int* stats = calcStat(gen);
	if (stats[1] == gsize) {
		return 1 + REWARD;
	}
	else if (stats[0] > 0) {
		return 1;
	}
	else {
		vector<int> sequence = gen;
		vector<int> pos_to_change;
		for (int i = 0; i < gsize; i++) {
			if (sequence[i] == 2) {
				pos_to_change.push_back(i);
			}
		}
		for (int a = 1; a <= attempts; a++) {
			for (int i = 0; i < pos_to_change.size(); i++) {
				sequence[pos_to_change[i]] = rand() % 2;
			}
			if (calcStat(sequence)[1] == gsize) {
				return ((attempts - a) / 1000.) * REWARD + 1;
			}
		}
		return 1;
	}
}

Alec::~Alec()
{
}

bool operator==(Alec const & _a1, Alec const & _a2)
{

	int gsize = _a1.getGen().size();
	vector<int> a1 = _a1.getGen();
	vector<int> a2 = _a2.getGen();
	for (int i = 0; i < gsize; ++i) {
		if (a1[i] != a2[i]) {
			return false;
		}
	}
	return true;
}

int * calcStat(vector<int> gen)
{
	int gsize = gen.size();
	int stats[3] = { 0 };
	for (int i = 0; i < gsize; ++i) {
		stats[gen[i]]++;
	}
	return stats;
}

Alec* sampleFunc(map<Alec*, double> map_btoFit, vector<Alec*> oFit, double sum_btoFit)
{
	double all_fit = oFit.size() + sum_btoFit;
	double random = (double)rand() / ((double)RAND_MAX + 1);
	if (random < oFit.size() / all_fit) {
		return oFit[rand() % oFit.size()];
	}
	else {
		double threshold = ((double)rand() / ((double)RAND_MAX + 1)) * sum_btoFit;
		cout << "threshold is " << threshold << endl;
		double sumFit = 0.;
		map< Alec*, double >::iterator res = map_btoFit.begin();

		while (res != map_btoFit.end()) {
			sumFit += res->second;
			if (sumFit >= threshold) {
				break;
			}
		}
		return (res->first);
	}
}

Alec* mate(int _name, Alec &first, Alec &second)
{
	int gsize = first.getGen().size();
	int change_position = 1 + (rand() % gsize);
	int i = 0;
	vector<int> gen_new;

	for (; i < change_position; i++) {
		gen_new.push_back(first.getGen()[i]);
	}
	for (; i < gsize; i++) {
		gen_new.push_back(second.getGen()[i]);
	}

	random_shuffle(gen_new.begin(), gen_new.end());
	return new Alec(_name, gen_new);
}
