#pragma once
#ifndef GENETIC
#define GENETIC

#include <vector>			
#include <string>
#include <iostream>	
#include <algorithm>				
#include <time.h>					
#include <math.h>



using namespace std;

#endif


struct sackStruct
{
	int capacity; 
	int avail;
	string items;
	int fitness;	
};

struct item
{
	int value;
	int weight;
};




typedef vector<sackStruct> sackVector;
typedef vector<item> itemVector;




void generateSack(sackStruct &sack, itemVector &items, int C);
int getWeight(sackStruct &sack, itemVector &items);
void fixWeight(sackStruct &sack, itemVector &items);
int maxValueHueristic(sackStruct &sack, itemVector &items);
string crossoverSackstruct(string s1, string s2, int opt);
void mateSackStruct(sackVector &sacks, itemVector &items, int cross_type);
double getRatio(struct item item);
void mutateSack(sackStruct &sack, itemVector &items);
void calcSackFits(sackVector &sacks, itemVector &items);
bool MinimumPrice(sackStruct x, sackStruct y);
bool MaximumPrice(sackStruct x, sackStruct y);
inline void sortMinimumPrice(sackVector &population);
inline void sortMaximumPrice(sackVector &population);
bool solveSack(int problem, int itr, int cross_type = 1);
void sack2str(sackStruct &sack, string &output);
int getMaxRatioIndex(sackStruct &sack, itemVector &items);
int getMinRatioIndex(sackStruct &sack, itemVector &items);
