// CNF.h
#ifndef CNF_H
#define CNF_H

#include "Clause.h"
#include <string>
#include <vector>
#include <unordered_map>

class CNF{
	int numOfVariables_;
	int numOfClauses_;
	std::vector<Clause> clauses_;

public:

	CNF();
	CNF( int numOfVariables, int numOfClauses, std::vector<std::vector<int> > dimacs );
	void add(Clause c);
	bool eval(std::unordered_map<int, bool> assignments_);
	std::vector<Clause>& getClauses();
	int getNumOfVariables();
	int getNumOfClauses();
	std::string toString();
};

#endif
