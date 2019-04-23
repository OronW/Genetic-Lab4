#pragma once
//#ifndef GENETICS
//#define GENETICS

#include <vector>			
#include <string>
#include <iostream>	
#include <algorithm>				
#include <time.h>					
#include <math.h>



using namespace std;

struct QS
{
	string str;
	int fitness;
};

typedef vector<QS> QSVector;



//#endif


int conflictsHeuristic(QS &board);
int** gene2mat(string str);
void initBoards(QSVector &Boards, QSVector &buffer, int N);
bool solveQueensProb(int N, int itr = 500, int cross_type = 1, int mutate_type = 1);
int CountConflicts(QS &board, int i);
void queensFitness(QSVector &boards);
bool MinFitness(QS x, QS y);
bool MaxFitness(QS x, QS y);
inline void sortMinimum(QSVector &population);
inline void sortMaximum(QSVector &population);
void BoardMating(QSVector &boards, QSVector &buffer, double percentage, int cross_type = 1, int mutate_type = 1);
void printboard(QS &board, bool print_fitness);
string crossover(string s1, string s2, int opt);
string boardToString(string &board);
void bestBoardPrint(QSVector &Boards);
void minimumConflicts(QS &board, int ind);
int checkConflictedQueen(QS &board);
bool solveQueensConflict(int N, int itr);
int getBoardsDist(QS &first, QS &second, int N);
double getAverage(QSVector &boards, int N);
double getVariance(QSVector &boards, int N);
double getPopulationDist(QSVector &boards, int N);
double catchLocalOptima(QSVector &boards, int N);
int randomImmigrants(QSVector &boards, int N);
