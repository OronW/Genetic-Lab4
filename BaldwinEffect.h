#ifndef BALDWIN
#define BALDWIN

#include "Alec.h"
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


#endif
#pragma once

string printSqequence(vector<int> gen);
bool checkIfEqual(vector<Alec*> all_pop);
void getGenStats(vector<Alec*> all_pop, double * res);
bool solveBaldwin(int samples = 1000, int itr = 1000, int lenght = 20, double set_rate = 0.50);


