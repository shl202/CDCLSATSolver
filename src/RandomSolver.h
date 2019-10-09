// RandomSolver.h
#ifndef RandomSolver_H
#define RandomSolver_H

#include "Solver.h"

//#include "CNF.h"
//#include <string>
//#include <vector>
//#include <unordered_map>


class RandomSolver: public Solver
{
	//int numOfVariables_;
	int numOfAttempts_;
	std::unordered_map<int, bool> bookKeeper_;
	//std::unordered_map<int, bool> assignments_;
	int encode(std::unordered_map<int, bool> assignment);
	int randomAssignment();
public:
	RandomSolver();
	~RandomSolver();
	std::string solve(CNF cnf);
	int getNumAttempts();
	int getUniqueNumAttempts();

};

#endif
