// DPLLSolver.h
#ifndef Assignment_H
#define Assignment_H

class Assignment
{
	int variable_;
	bool value_;

public:
	Assignment(int var, bool val);
	int getVariable();
	bool getValue();
	void setVariable(int var);
	void setValue(bool val);
};


#endif
