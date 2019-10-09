// Literal.h
#ifndef Literal_H
#define Literal_H

#include <string>
#include <unordered_map>

#define ASSIGNED0 0
#define ASSIGNED1 1
#define UNASSIGNED -1

class Literal
{
	int name_;
	int polarity_;
        int assignment_;

public:
	Literal();
	Literal(int literal);
	void assign(int x);
	void flipAssignment();
        int getAssignment();
	int getLiteral();
	int getVariable();
	int getPolarity();
	void resetAssignment();
	std::string toString();
	bool eval(std::unordered_map<int, bool> assignments);

};

#endif
