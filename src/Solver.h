// Solver.h
#ifndef Solver_H
#define Solver_H

#include "CNF.h"
#include "Clause.h"
#include "Config.h"
#include <string>
#include <vector>
#include <unordered_map>

#define SAT "sat"
#define UNSAT "unsat"
#define UNKNOWN "unknown"
#define DEBUGMODE false

class Solver
{
protected:
	int numOfVariables_;
	std::unordered_map<int, bool> assignments_;
	//std::vector<std::pair<Literal, bool> > assignmentstack_;

public:
	virtual ~Solver();
	virtual std::string solve(CNF cnf);

};

#endif
