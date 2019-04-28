#include <vector>			
#include <string>
#include <iostream>	
#include <algorithm>				
#include <time.h>					
#include <math.h>					
#include <stdlib.h>
#include <map>
#include <iterator>

using namespace std;

#pragma once
class Alec
{
private:
	int name;
	vector<int> gen;
	int attempts = 1000;
public:
	vector<int> getGen() const;
	Alec(Alec &other);
	Alec(int _name, vector<int> _gen);
	Alec(int _name, int _len, double _set_rate);
	double calcFitness();
	~Alec();

};

bool operator == (Alec const &a1, Alec const &a2);
int* calcStat(vector<int> gen);
Alec* sampleFunc(map<Alec*, double> map_btoFit, vector<Alec*> oFit, double sum_btoFit);
Alec* mate(int _name, Alec & first, Alec &second);
