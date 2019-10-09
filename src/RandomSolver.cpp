#include "RandomSolver.h"
#include <random>
#include <math.h>
#include <ctime>
#include <iostream>

using namespace std;

RandomSolver::RandomSolver()
{
	srand(time(NULL));
}

RandomSolver::~RandomSolver()
{
}

int RandomSolver::randomAssignment()
{
	int r = rand();
	if( r > (RAND_MAX /2) ){
		return true;
	}
	else{
		return false;
	} 
}

int RandomSolver::encode(unordered_map<int, bool> assignments_)
{
	int bin, dec = 0, rem, num, base = 1;
	
	
	for( int i = numOfVariables_; i >= 1; i-- ){
		if( assignments_[i])
		{
			dec += 1 * base;
		}
		base = base * 2;
	}
	return dec;
}

string RandomSolver::solve(CNF cnf)
{
	numOfVariables_ = cnf.getNumOfVariables();
	numOfAttempts_ = 0;
	assignments_.clear();
	bookKeeper_.clear();

	time_t start, end;
	double elapsed;
	start = time(NULL);
	int terminate = 1;
	while( terminate ) 
	{
		end = time(NULL);
		elapsed = difftime(end, start);
		if (elapsed >= 10.0 /* seconds */)
		{
			terminate = 0;
			continue;
		}

		for( int i = 1; i <= numOfVariables_; i++ ){
			assignments_.insert({i, randomAssignment()});
		}
		numOfAttempts_ ++;
		if( cnf.eval(assignments_) ){
			return SAT;
		}
		else{
			int key = encode(assignments_);
			if(bookKeeper_.find(key) == bookKeeper_.end()){
				if ( bookKeeper_.size() == pow(2, numOfVariables_) -1)
				{
					return UNSAT;
				} 
				bookKeeper_.insert({key, true});
			}
			assignments_.clear();
		}
	}
	return UNKNOWN; 
}


int RandomSolver::getNumAttempts()
{
	return numOfAttempts_;
}

int RandomSolver::getUniqueNumAttempts()
{
	return bookKeeper_.size() + 1;
}
