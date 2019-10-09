#include "DPLLSolver.h"
#include <random>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <iostream>

#define CONFLICTVARIABLE 0
#define POSITIVE 1
#define NEGATIVE -1

using namespace std;

int myrandom (int i) 
{ 
	return rand()%i;
}

DPLLSolver::DPLLSolver()
{
	srand ( unsigned ( time(0) ) );	
}


DPLLSolver::~DPLLSolver()
{
}


void DPLLSolver::backtract(int var, bool val)
{
	pair<int, bool> varAsmt;
	do
	{
		varAsmt = assignmentStack_.back();
		if(DEBUGMODE)
			cerr << "backtract: " << varAsmt.first << "<-" << varAsmt.second << endl; 
		if( varAsmt.first != CONFLICTVARIABLE)
			unassignedStack_.push_back(varAsmt.first);
		assignmentStack_.pop_back();
		assignments_.erase(varAsmt.first);
	} while( varAsmt.first != var );
	if(DEBUGMODE)
		cerr << "correction: " << var << "<-" << val << endl; 
	
	//decisionStack_.push_back(make_pair(var, val));
	assignmentStack_.push_back(make_pair(var, val));
	unassignedStack_.erase(std::remove(unassignedStack_.begin(), unassignedStack_.end(), var), unassignedStack_.end()); 
	assignments_.insert({var, val});
}


bool DPLLSolver::isAssigned(int var)
{
	if( assignments_.find(var) != assignments_.end() )
		return true;
	return false;
}


pair<int, bool> DPLLSolver::makeDecision()
{
	int var;
	do
	{
		var = unassignedStack_.back();
		unassignedStack_.pop_back();
	} while( isAssigned(var));
	if(DEBUGMODE)
		cerr << "decision: " << var << "<-" << true << endl;
	return make_pair(var, true);
}


bool DPLLSolver::moveWatchedLiteral(Clause &c, int wn)
{
	if( wn == 1 )
	{
		int l2 = c.getW2().getVariable();

		if( !isAssigned(l2) )
		{
			Literal  tmp = c.getW1();	
			c.setW1(c.getW2());
			c.setW2(tmp);
			return true;
		}
		else
		{
			vector<Literal> literals = c.getLiterals();
			for( int i = 0; i < literals.size(); i++)
			{
				int l1 = literals[i].getVariable();
				if( !isAssigned(l1) && (l1 != l2) )
				{
					c.setW1(literals[i]);
					return true;
				}
			}
			return false;
		}
	}
	else
	{
		int l1 = c.getW1().getVariable();
		vector<Literal> literals = c.getLiterals();
		for( int i = 0; i < literals.size(); i++)
		{
			int l2 = literals[i].getVariable();
			if( !isAssigned(l2) && (l1 != l2) )
			{
				c.setW2(literals[i]);
				return true;
			}
		}
		return false;
		
	}
}



Clause DPLLSolver::pickClause(vector<Clause> &interestingClauses, bool &isNull, bool &conflict)
{
	conflict = false;
	isNull = false;
	while( !(interestingClauses.empty()) )
	{
		Clause c = interestingClauses.back();
		interestingClauses.pop_back();

		//singletons
		if( c.size() == 1)
		{
			Literal  w = c.getW1();
			if( !isAssigned(w.getVariable()) )
			{
				return c;
			}
			else
			{
				if( w.eval(assignments_) )
				{
					continue;
				}
				else
				{
					conflict = true;
					return Clause();
				}
			}
		}


		Literal  w1 = c.getW1();
		Literal  w2 = c.getW2();
		if( ( isAssigned(w1.getVariable()) &&
			  (w1.eval(assignments_) == true) ) ||
			( isAssigned(w2.getVariable()) &&
			  (w2.eval(assignments_) == true) ) )
		{
			continue;
		}
		else if ( !isAssigned(w1.getVariable()) )
		{
			if( !isAssigned(w2.getVariable() ))
			{
				continue;	
			}
			else
			{
				//if( w2.eval(assignments_) == false) implied
				if( moveWatchedLiteral(c, 2) )
				{
					continue;
				}
				else
				{
					return c;
				}	
			}
		}
		else // w1.eval(assignments_) == false
		{
			if( moveWatchedLiteral(c, 1 ))
			{
				interestingClauses.push_back(c);
			}
			else
			{
				if( w2.eval(assignments_) == false)
				{
					conflict = true;
					return Clause();
				}
				else
				{
					return c;
				}
			}
		}
	}
	isNull = true;
	return Clause(); //dummy Clause, won't be used
} 

void DPLLSolver::pureLiteralRule(CNF initcnf, CNF &simplestcnf )
{
	int numOfVariables = initcnf.getNumOfVariables();
	bool positive[numOfVariables + 1];
	bool negative[numOfVariables + 1];
	for (int i = 0; i < numOfVariables + 1; i++)
	{
		positive[i] = false;
		negative[i] = false;
	}
	vector<Clause> clauses = initcnf.getClauses();
	CNF simplercnf = CNF();

	// find pure literals
	for (int i = 0; i < clauses.size(); i++)
	{
		std::vector<Literal> literals = clauses[i].getLiterals();
		for( int j = 0; j < literals.size(); j++ )
		{
			if( literals[j].getPolarity() == POSITIVE )
			{
				positive[literals[j].getVariable()] = true;
			}
			else
			{	
				negative[literals[j].getVariable()] = true;
			}
		}
	}

	/*  debug for marking pure literals
	for (int i = 0; i < numOfVariables + 1; i++)
	{
		cerr << i << ":" << (positive[i] && negative[i]) << endl;
	}
	*/

	// eliminate pure literals
	bool hasPureLiteral = false;
	int var = 0;
	for (int i = 0; i < clauses.size(); i++)
	{
		std::vector<Literal> literals = clauses[i].getLiterals();
		hasPureLiteral = false;
		for( int j = 0; j < literals.size(); j++ )
		{
			var = literals[j].getVariable();
			if( !(positive[var] && negative[var]) )
			{
				hasPureLiteral = true;
				break;
			}
			
		}
		if( !hasPureLiteral )
		{
			simplercnf.add(clauses[i]);
		}
		
	}

	// assign pure literals
	int numPureLiterals = 0;
	for( int k = 1; k < numOfVariables + 1; k++)
	{
		if( positive[k] != negative[k] )
		{
			bool value;
			numPureLiterals ++;
			if( negative[k] ){
				value = false;
			}
			else if ( positive[k] )
			{
				value = true;
			}
			
			assignments_.insert({k, false});
			assignmentStack_.push_back(make_pair(k, false));
			if(DEBUGMODE)
				cerr << "pure literal: " << k << "<-" << value << endl;
		}
	}
		
	if( DEBUGMODE )
		cerr << simplercnf.toString() << endl;

	// recursive call to PureLiteralRule again
	if( numPureLiterals > 0)
	{
		pureLiteralRule(simplercnf, simplestcnf);
	}
	else
	{
		vector<Clause> simplestClauses = simplercnf.getClauses();
		for( int l = 0; l < simplestClauses.size(); l++)
		{
			simplestcnf.add(simplestClauses[l]);
		}
	}
		
	
}

void DPLLSolver::singleton(CNF cnf, std::vector<Clause> &interestingClauses)
{
	vector<Clause> clauses = cnf.getClauses();
	for( int i = 0; i < clauses.size(); i++)
	{
		if( clauses[i].size() ==  1)
		{
			interestingClauses.push_back(clauses[i]);
		}
	}
}

int DPLLSolver::unitRule(Clause c)
{
	Literal w1 = c.getW1();
	Literal w2 = c.getW2();
	int var;
	bool value;
	if( !isAssigned(w1.getVariable()) )
	{
		var = w1.getVariable();	
		if( w1.getPolarity() == POSITIVE )
			value = true;
		else
			value = false;
	}
	else if(!isAssigned(w2.getVariable()) )
	{
		var = w2.getVariable();
		if( w2.getPolarity() == POSITIVE )
			value = true;
		else
			value = false;
	}
	else
	{
		cerr << "Huston, we have a problem" << endl;
		cout << c.toString() << endl;
		cout << w1.getVariable() << endl;
		cout << w2.getVariable() << endl;
	}
	assignments_.insert({var, value});
	assignmentStack_.push_back(make_pair(var, value));
	if(DEBUGMODE)
		cerr << "unitRule: " << var << "<-" << value << endl;
	return var;
}

void DPLLSolver::unitPropagation(CNF cnf, std::vector<Clause> &interestingClauses)
{
	while(true)
	{
		bool conflict = false;
		bool isNull = false;
		
		
		Clause c = pickClause(interestingClauses, isNull, conflict);

		if ( isNull )
		{
			return;
		}
		else if( conflict )
		{
			assignments_.insert({CONFLICTVARIABLE, true});		
			assignmentStack_.push_back(make_pair(CONFLICTVARIABLE, true));
			return;
		}
		else
		{
			int var = unitRule(c);
			updateInterestingClauses(var, cnf, interestingClauses);
		}
	}
}

void DPLLSolver::updateInterestingClauses(int var, CNF cnf, vector<Clause> &interestingClauses)
{
	vector<Clause> clauses = cnf.getClauses();
	for( int i = 0; i < clauses.size(); i++)
	{
		if( clauses[i].contains(var) )
		{
			interestingClauses.push_back(clauses[i]);
		}
	}	
}


string DPLLSolver::solve(CNF cnf)
{
	numOfVariables_ = cnf.getNumOfVariables();
	assignments_.clear();
	// clear vectors

	// preprocesses
	cout << "Preprocessing CNF" << endl;
	CNF purecnf = CNF(); 
	pureLiteralRule(cnf, purecnf);

	cout << purecnf.toString() << endl;
	cout << "done... " << endl;

	for( int i = 1; i < cnf.getNumOfVariables() +1; i++)
	{
		if( !isAssigned(i))
		{
			unassignedStack_.push_back(i);
		}
	}
	//random_shuffle ( unassignedStack_.begin(), unassignedStack_.end(), ::myrandom);

	vector<Clause> interestingClauses;
	singleton(purecnf, interestingClauses);
	
	

	cout << "Computing Satisfiability..." << endl; 
	while( true )
	{
		unitPropagation(purecnf, interestingClauses);
		
		if( !isAssigned(CONFLICTVARIABLE) )
		{
			if( numOfVariables_ == assignments_.size() )
			{
				return SAT;
			}
			else
			{
				pair<int, bool> varVal = makeDecision();
				assignments_.insert({varVal.first, varVal.second});
				assignmentStack_.push_back(varVal);
				//unassignedStack_.pop_back();
				decisionStack_.push_back(varVal);
				updateInterestingClauses(varVal.first, purecnf, interestingClauses);
			}
		}
		else
		{
			if( decisionStack_.empty() )
			{
				return UNSAT;
			}	
			else // has a conflict
			{
				pair<int, bool> varVal = decisionStack_.back();
				decisionStack_.pop_back();
				backtract(varVal.first, !(varVal.second));
				updateInterestingClauses(varVal.first, purecnf, interestingClauses);
			}
		}
	}
	return UNSAT;
}


