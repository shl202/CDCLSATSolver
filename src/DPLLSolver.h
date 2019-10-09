// DPLLSolver.h
#ifndef DPLLSolver_H
#define DPLLSolver_H

#include "Solver.h"

class DPLLSolver: public Solver
{
	//int numOfVariables_;
	//std::unordered_map<int, bool> bookKeeper_;
	//std::unordered_map<int, bool> assignments_;
	//int encode(std::unordered_map<int, bool> assignment);
	std::vector<std::pair<int, bool> > decisionStack_;
	std::vector<std::pair<int, bool> > assignmentStack_; // to easier backtract assignments
	std::vector<int> unassignedStack_;

	void backtract(int var, bool val);
	bool isAssigned(int var);
	std::pair<int, bool> makeDecision();	
	bool moveWatchedLiteral(Clause &c, int wn);
	Clause pickClause(std::vector<Clause> &interestingClauses, bool &isNull, bool &conflict);
	void pureLiteralRule(CNF initcnf, CNF &simplestcnf);
	void singleton(CNF cnf, std::vector<Clause> &interestingClauses);
	int unitRule(Clause c);
	void unitPropagation(CNF cnf, std::vector<Clause> &interestingClauses);	 
	void updateInterestingClauses(int var, CNF cnf, std::vector<Clause> &interestingClauses);
	
	
	
	
public:
	DPLLSolver();
	~DPLLSolver();
	std::string solve(CNF cnf);

};

#endif
