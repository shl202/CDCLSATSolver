// CDCLSolver.h
#ifndef CDCLSolver_H
#define CDCLSolver_H

#include "Solver.h"
#include "ImplicationGraph.h"
#include <deque>

class CDCLSolver: public Solver
{
	//int numOfVariables_;
	//std::unordered_map<int, bool> bookKeeper_;
	//std::unordered_map<int, bool> assignments_;
	//int encode(std::unordered_map<int, bool> assignment);
	std::vector<std::pair<int, bool> > decisionStack_;
	std::vector<std::pair<int, bool> > assignmentStack_; // to easier backtract assignments
	std::vector<int> unassignedStack_;
	ImplicationGraph iGraph_;
	int decisionLevel_;
	

	Clause analyzeAndLearn(int &secondHighestDL);
	std::string assignmentStackToString();
	std::string satisfiableAssignmentToString();
	Clause constructLearnedClause(std::deque<Node> uip);
	int findSecondHighestDL(std::deque<Node> uip);
	void backtract(int decisionLevel);
	bool isAssigned(int var);
	std::pair<int, bool> makeDecision();	
	bool moveWatchedLiteral(Clause &c, int wn);
	Clause pickClause(std::vector<Clause> &interestingClauses, bool &isNull, bool &conflict, int &interestingVariable);
	void pureLiteralRule(CNF initcnf, CNF &simplestcnf);
	void singleton(CNF cnf, std::vector<Clause> &interestingClauses);
	std::pair<int, bool> unitRule(Clause c);
	void unitPropagation(CNF cnf, std::vector<Clause> &interestingClauses);	 
	void updateInterestingClauses(int var, CNF cnf, std::vector<Clause> &interestingClauses);
	
	
	
	
public:
	CDCLSolver();
	~CDCLSolver();
	std::string solve(CNF cnf, Config config);

};

#endif
