// Clause.cpp
#include "Clause.h"
#include <sstream>
#include <iostream>

using namespace std;


Clause::Clause()
{
	numOfLiterals_ = 0;
}


Clause::Clause( vector<int> clause)
{
	numOfLiterals_ = 0;
	for( int i = 0; i < clause.size(); i++)
	{
		literals_.push_back(Literal(clause[i]));	
	}	
	numOfLiterals_ = clause.size();

	if(numOfLiterals_ == 1)
	{
		w1_ = literals_[0];
		//w2_ = nullptr;
	}
	else if(numOfLiterals_ >= 2)
	{
		w1_ = literals_[0];
		w2_ = literals_[1];
	}
	
}

bool Clause::contains(int var)
{
	for(int i = 0; i < numOfLiterals_; i++)
	{
		if( literals_[i].getVariable() == var )
		{
			return true;
		}
	}
	return false;
}

vector<Literal> Clause::getLiterals()
{
	return literals_;
}

vector<int> Clause::getVariables()
{
	vector<int> variables;
	for( int i = 0; i < literals_.size(); i++)
	{
		variables.push_back(literals_[i].getVariable());
	}
	return variables;
}

string Clause::toString()
{
	ostringstream os;
	for ( int i = 0; i < numOfLiterals_; i++ )
	{
		os << literals_[i].toString() << " ";
	}
	string s = os.str();
	return s;
}

bool Clause::eval(unordered_map<int, bool> assignments_)
{
	bool evaluation = false;
	for ( int i = 0; i < numOfLiterals_; i++ )
	{
		evaluation = evaluation || literals_[i].eval(assignments_);
	}
	return evaluation;
}

int Clause::size()
{
	return numOfLiterals_;
}

Literal Clause::getW1()
{
	return w1_;
}

Literal Clause::getW2()
{
	return w2_;
}

void Clause::setW1(Literal l)
{
	w1_ = l;
}

void Clause::setW2(Literal l)
{
	w2_ = l;
}
