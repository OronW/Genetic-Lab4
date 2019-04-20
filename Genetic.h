#pragma once
#ifndef GENETIC
#define GENETIC


#include <vector>			
#include <string>
#include <iostream>	
#include <algorithm>				
#include <time.h>					
#include <math.h>					
#include <stdlib.h>
#include <bitset>

using namespace std;

struct ga_struct
{
	string str;
	int fitness;
};

typedef vector<ga_struct> ga_vector;


#endif

#pragma once



void mutate(ga_struct &member);
void SUSElitism(ga_vector &output, ga_vector &pop);
int getTotalFitness(ga_vector &Population);
void tournament(ga_vector &pop, ga_vector &output, int n);
int fitnessSum(ga_vector &Population, int end);
int BEHeuristic(string source, string target);
void RWS(ga_vector &Population, vector<int> &Points, ga_vector &Keep);
void SUSElitism(ga_vector &output, ga_vector &pop);
void SUS(ga_vector &Population, ga_vector &output, int N);
bool goalState(string source);
void BEFitness(ga_vector &population);
string uniform_cross(string source1, string source2);
void initAllPop(ga_vector &population, ga_vector &buffer);
void calcFit(ga_vector &population);
bool fitSort(ga_struct x, ga_struct y);
inline void sortAccToFit(ga_vector &population);
void elitism(ga_vector &population, ga_vector &buffer, int esize);
void mutate(ga_struct &member);
void onePointCross(ga_vector &population, ga_vector &buffer);
void mate(ga_vector &population, ga_vector &buffer, int cross_type, double mutation_rate);
inline void printResOfBest(ga_vector &gav);
inline void printStatOf();
inline void swap(ga_vector *&population, ga_vector *&buffer);
bool solveUsingGen(int N = 2048, int itr = 1000, int h = 1, int cross_type = 1, double mutation_rate = 0.25, int selection_type = 1);
string smartXbreed(string source1, string source2, int fitness1, int fitness2);
int getGenDist(ga_struct &first, ga_struct &second);
float getAverage(ga_vector &all_pop);
float getVariance(ga_vector &all_pop);
float getPopulationDist(ga_vector &all_pop);
int catchLocalOptima(ga_vector &all_pop);
