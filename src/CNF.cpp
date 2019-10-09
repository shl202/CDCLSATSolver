// CNF.cpp
#include "CNF.h"
#include <sstream>
#include <iostream>

using namespace std;

CNF::CNF( )
{
	numOfVariables_ = 0;
	numOfClauses_ = 0;
}

CNF::CNF( int numOfVariables, int numOfClauses, vector<vector<int> > cnf )
{
	numOfVariables_ = numOfVariables;
	numOfClauses_ = numOfClauses;
	for( vector<vector<int> >::iterator it = cnf.begin(); it != cnf.end(); ++it )
	{
		clauses_.push_back(Clause(*it));	
	}	
} 


void CNF::add(Clause c)
{
	
	vector<Literal> literals = c.getLiterals();
	for( int i = 0; i < literals.size(); i ++)
	{
		int var = literals[i].getVariable();
		if( var > numOfVariables_ )
		{
			numOfVariables_ = var;	
		}
	}
	//numOfVariables_ += c.getLiterals().size();
	
	numOfClauses_ ++;
	clauses_.push_back(c);
}


bool CNF::eval(unordered_map<int, bool> assignments_)
{
	bool evaluation = true;
	for ( int i = 0; i < numOfClauses_; i++ )
	{
		evaluation = evaluation && clauses_[i].eval(assignments_);
	}
	return evaluation;
}

std::vector<Clause>& CNF::getClauses()
{
	return clauses_;
}


int CNF::getNumOfVariables()
{
	return numOfVariables_;
}

int CNF::getNumOfClauses()
{
	return numOfClauses_;
}



string CNF::toString()
{
	ostringstream os;
	for ( int i = 0; i < numOfClauses_; i++ )
	{
		os << clauses_[i].toString() << "0" << endl;
	}
	string s = os.str();
	return s;
}

