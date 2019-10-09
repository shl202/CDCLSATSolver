// Literal.cpp
#include "Literal.h"
#include <sstream>
#include <iostream>

#define POSITIVE 1
#define NEGATIVE -1

using namespace std;

Literal::Literal()
{

}

Literal::Literal(int literal)
{
	if( literal > 0 )
	{
		polarity_ = POSITIVE;
	}
	else
	{
		polarity_ = NEGATIVE;
	}

	name_ = literal * polarity_;
	assignment_ = UNASSIGNED;
}


void Literal::assign(int x)
{
	if(x == 0 || x == 1)
	{
		assignment_ = x;
	}
	else
	{
		std::cerr << "Literal assignments must be {0, 1}" << std::endl;
	}
}


void Literal::flipAssignment()
{
	if( assignment_ == 0 || assignment_ == 1 )
	{
		assignment_ = 1 - assignment_;
	}
	else
	{
		std::cerr << "Cannot flip an unassigned literal" << std::endl;
	}
}


int Literal::getAssignment()
{
	return assignment_;
}


int Literal::getLiteral()
{
	return name_ * polarity_;
}

int Literal::getPolarity()
{
	return polarity_;
}

int Literal::getVariable()
{
	return name_;
}

void Literal::resetAssignment()
{
	assignment_ = UNASSIGNED;
}

string Literal::toString()
{
	ostringstream os;
	os << getLiteral();
	return os.str();
}

bool Literal::eval(unordered_map<int, bool> assignments)
{
	bool evaluation = assignments[name_];
	
	if( polarity_ == POSITIVE )
	{
		return evaluation;
	}
	else
	{
		return !(evaluation);
	}
}
