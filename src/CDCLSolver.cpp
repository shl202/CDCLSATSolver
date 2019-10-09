#include "CDCLSolver.h"
#include <random>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <deque>

#define CONFLICTVARIABLE 0
#define POSITIVE 1
#define NEGATIVE -1

using namespace std;

CDCLSolver::CDCLSolver()
{
}


CDCLSolver::~CDCLSolver()
{
}

Clause CDCLSolver::analyzeAndLearn(int &secondHighestDL)
{
	Node conflictNode;
	if(!iGraph_.findNode(CONFLICTVARIABLE, conflictNode))
	{
		cout << "ERROR: Cannot find Conflict Node" << endl;
	}
	//cout << iGraph_.toString() << endl;

	if( DEBUGMODE )
		cout << "Conflict Decision Level: " << conflictNode.getDecisionLevel() << endl;
	

	deque<Node> uip = iGraph_.findUIP(conflictNode);
	if( DEBUGMODE)
	{
		for( auto it = uip.begin(); it != uip.end(); ++it)
		{
			cout << it->toString();
		}
	}
	secondHighestDL = findSecondHighestDL(uip);	
	
	if( DEBUGMODE )
	{
		cout << "Second Highest Decision Level: " << secondHighestDL << endl;
	}
	
	/* construct the clause to return */
	return constructLearnedClause(uip);
}


string CDCLSolver::satisfiableAssignmentToString()
{
	if (assignments_.size() != numOfVariables_)
	{
		cerr << "This function should only be call after a valid solution is found" << endl;
		return "";
	}
	ostringstream os;
	for( int i = 1; i < numOfVariables_; i++)
	{
		os << i
		   << " <- " 
		   << assignments_[i] << endl;
	}
	return os.str();
}

string CDCLSolver::assignmentStackToString()
{
	ostringstream os;
	for(int i = 0; i < assignmentStack_.size(); i++)
	{
		os << assignmentStack_[i].first 
		   << " <- " 
           << assignmentStack_[i].second << endl;
	}
	return os.str();	
}

Clause CDCLSolver::constructLearnedClause(deque<Node> uip)
{
	vector<int> clause;
	for( auto it = uip.begin(); it != uip.end(); ++it)
	{
		int var = it->getVariable();
		bool val = it->getValue();
		int literal;

		// taking the negation of the literal
		if( val )
		{
			literal = -1 * var;
		}
		else
		{
			literal = var;
		}
		clause.push_back(literal);
	}
	return Clause(clause);
}

int CDCLSolver::findSecondHighestDL(deque<Node> uip)
{
	int highestLevel = -1;
	int secondHighestLevel = -1;
	bool hasMoreThanOneLevel = false;
	int levelA = -1;
	
	for( auto it = uip.begin(); it != uip.end(); ++it)
	{
		int decisionLevel = it->getDecisionLevel();
		//cout << it->getVariable() << endl;
		//cout << decisionLevel << endl;
		if( !hasMoreThanOneLevel )
		{
			if( levelA == -1 )
			{
				levelA = decisionLevel;
			}
			else
			{
				if( decisionLevel != levelA )
				{
					hasMoreThanOneLevel = true;	
				}
			}
		}
		if( decisionLevel > highestLevel)
		{
			secondHighestLevel = highestLevel;
			highestLevel = decisionLevel;
		}
		else
		{
			if( decisionLevel > secondHighestLevel)
			{
				secondHighestLevel = decisionLevel;
			}
		}
	}
	if(hasMoreThanOneLevel)
	{
		return secondHighestLevel;
	}
	else
	{
		if(highestLevel != 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
}

void CDCLSolver::backtract(int decisionLevel)
{
	int decisionVariable = iGraph_.backtract(decisionLevel);
	
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
	} while( (varAsmt.first != decisionVariable) && (!assignmentStack_.empty()) );
	decisionLevel_ = decisionLevel -1;

	if( decisionLevel_ < 0)
	{
		decisionLevel_ = 0;
	}
}


bool CDCLSolver::isAssigned(int var)
{
	if( assignments_.find(var) != assignments_.end() )
		return true;
	return false;
}


pair<int, bool> CDCLSolver::makeDecision()
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


bool CDCLSolver::moveWatchedLiteral(Clause &c, int wn)
{
	if( wn == 1 )
	{
		int l2 = c.getW2().getVariable();
		if( !isAssigned(l2) )
		{
			Literal tmp = c.getW1();	
			c.setW1(c.getW2());
			c.setW2(tmp);
			return true;
		}

		//int l2 = c.getW2()->getVariable();
		else{
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


Clause CDCLSolver::pickClause(vector<Clause> &interestingClauses, bool &isNull, bool &conflict, int &interestingVariable)
{
	conflict = false;
	isNull = false;
	interestingVariable = 0;
	while( !(interestingClauses.empty()) )
	{
		Clause c = interestingClauses.back();
		interestingClauses.pop_back();

		//singletons
		if( c.size() == 1)
		{
			Literal w = c.getW1();
			if( !isAssigned(w.getVariable()) )
			{
				interestingVariable = w.getVariable();	
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
					return c;
				}
			}
		}


		Literal w1 = c.getW1();
		Literal w2 = c.getW2();

		//cout << c.toString() << endl;
		//cout << "w1: " << w1.getVariable() << endl;
		//cout << "w2: " << w2.getVariable() << endl;
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
					interestingVariable = w1.getVariable();
					return c;
				}	
			}
		}
		else // w1 eval(assignments_) == false implied
		{
			if( moveWatchedLiteral(c, 1 ))
			{
				interestingClauses.push_back(c);
				continue;
			}
			else
			{
				if( w2.eval(assignments_) == false)
				{
					// when both watch literals are false
					if( c.eval(assignments_) == false )
					{
						conflict = true;
						return c;
					}
					else
					{
						continue;
					}
				}
				else
				{
					interestingVariable = w2.getVariable();
					return c;
				}
			}
		}
	}
	isNull = true;
	return Clause(); //dummy Clause, won't be used
} 

void CDCLSolver::pureLiteralRule(CNF initcnf, CNF &simplestcnf )
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

	/* debug for marking pure literals
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

void CDCLSolver::singleton(CNF cnf, std::vector<Clause> &interestingClauses)
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

pair<int, bool> CDCLSolver::unitRule(Clause c)
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
	}
	assignments_.insert({var, value});
	assignmentStack_.push_back(make_pair(var, value));
	if(DEBUGMODE)
		cerr << "unitRule: " << var << "<-" << value << endl;
	return make_pair(var, value);
}

void CDCLSolver::unitPropagation(CNF cnf, std::vector<Clause> &interestingClauses)
{
	while(true)
	{
		bool conflict = false;
		bool isNull = false;
		int interestingVariable = 0;
		
		
		Clause c = pickClause(interestingClauses, isNull, conflict, interestingVariable);

		
		/*
		if( interestingVariable == 1)
		{
				cout << "W1" << c.getW1().getVariable() << endl;
				cout << "W2" << c.getW2().getVariable() << endl;
		}
		
		cout << c.toString() << endl;
		cout << interestingVariable << endl;
		*/

		if ( isNull )
		{
			return;
		}
		else if( conflict )
		{
			vector<int> nodeIDs = c.getVariables();
			iGraph_.addNode(
				false,
				decisionLevel_,
				CONFLICTVARIABLE,
				true,
				nodeIDs,
				c
			);
				
			assignments_.insert({CONFLICTVARIABLE, true});		
			assignmentStack_.push_back(make_pair(CONFLICTVARIABLE, true));
			return;
		}
		else
		{
			pair<int, bool> varVal = unitRule(c);

			vector<int> nodeIDs = c.getVariables();
			nodeIDs.erase(std::remove(nodeIDs.begin(), nodeIDs.end(), interestingVariable), nodeIDs.end()); 
			
			iGraph_.addNode(
				false,
				decisionLevel_,
				varVal.first,
				varVal.second,
				nodeIDs,
				c
			);
			
			updateInterestingClauses(varVal.first, cnf, interestingClauses);
		}
	}
}

void CDCLSolver::updateInterestingClauses(int var, CNF cnf, vector<Clause> &interestingClauses)
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


string CDCLSolver::solve(CNF cnf, Config config)
{
	numOfVariables_ = cnf.getNumOfVariables();
	
	// initialize assignments and implication graph
	assignments_.clear();
	iGraph_ = ImplicationGraph(numOfVariables_); 

	// preprocesses
	if( DEBUGMODE )
		cout << "Preprocessing CNF" << endl;

	CNF purecnf = CNF(); 
	pureLiteralRule(cnf, purecnf);

	if( DEBUGMODE )
	{
		cout << purecnf.toString() << endl;
		cout << "done... " << endl;
	}

	for( int i = cnf.getNumOfVariables() + 1; i >= 1 ; i--)
	{
		if( !isAssigned(i))
		{
			unassignedStack_.push_back(i);
		}
	}

	vector<Clause> interestingClauses;
	singleton(purecnf, interestingClauses);
	decisionLevel_ = 0;
	
	vector<int> dummyints;
	Clause dummyClause = Clause();
	//for( int i = 0; i < 20; i ++)
	//{
	//	iGraph_.addNode(false, i, i, true, dummyints, dummyClause);
	//}
	//cout << iGraph_.toString() << endl;

	
	//return UNSAT;
	

	if( DEBUGMODE )
		cout << "Computing Satisfiability..." << endl; 

	time_t start, end;
	double elapsed;
	start = time(NULL);

	while( elapsed < config.timeLimit() )
	{
		end = time(NULL);
		elapsed = difftime(end, start);

		unitPropagation(purecnf, interestingClauses);
		
		if( !isAssigned(CONFLICTVARIABLE) )
		{
			if( numOfVariables_ == assignments_.size() )
			{
				if( config.verbose() )
				{
					ostringstream os;
					os << SAT << endl
					   << "Satisfiable Assignment:" << endl
					   << satisfiableAssignmentToString();
					return os.str();
				}
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
				decisionLevel_ ++;
				iGraph_.addNode(
					true,
					decisionLevel_,
					varVal.first,
					varVal.second,
					dummyints,
					dummyClause
				);
	
			}
		}
		else
		{
			int decisionLevel;
			Clause learnedClause = analyzeAndLearn(decisionLevel);
			//cout << learnedClause.toString();
			//return "Terminated...";
			if( decisionLevel < 0 )
			{
				if( config.verbose() )
				{
					ostringstream os;
					os << UNSAT << endl
					   << "Last Learned CLause:" << endl
					   << learnedClause.toString();
					return os.str();
				}
				return UNSAT;
			}	
			else // has a conflict
			{
				//pair<int, bool> varVal = decisionStack_.back();
				//decisionStack_.pop_back();
				backtract(decisionLevel);
				//updateInterestingClauses(varVal.first, purecnf, interestingClauses);
				//interestingClauses.push_back(learnedClause);
				purecnf.add(learnedClause);
				singleton(purecnf, interestingClauses);
				if( DEBUGMODE) 
					cout << "Learned new clause: " << learnedClause.toString() << endl;
			}
		}
	}
	if( config.verbose() )
	{
		ostringstream os;
		os << UNKNOWN << endl
		   << "Current Assignments:" << endl
		   << assignmentStackToString();
		return os.str();
	}
	return UNKNOWN;
}
