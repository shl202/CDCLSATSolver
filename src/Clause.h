// Clause.h
#ifndef Clause_H
#define Clause_H

#define CONFLICT true;

#include "Literal.h"
#include <string>
#include <vector>
#include <unordered_map>

class Clause {
	std::vector<Literal> literals_;
	int numOfLiterals_;
	//vector<Literal*> watchedLiterals_;
	Literal w1_;
	Literal w2_;

public:

	Clause( std::vector<int> clause );
	Clause();
	bool contains(int var);
	std::vector<Literal> getLiterals();
	std::vector<int> getVariables();
	std::string toString();
	bool eval(std::unordered_map<int, bool> assignments_);
	int size();

	Literal getW1();
	Literal getW2();
	void setW1(Literal l);
	void setW2(Literal l);
};

#endif
