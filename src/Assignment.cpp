#include "Assignment.h"

Assignment::Assignment(int var, bool val)
{
	variable_ = var;
	value_ = val;
}

int Assignment::getVariable()
{
	return variable_;	
}

bool Assignment::getValue()
{	
	return value_;
}

void Assignment::setVariable(int var)
{
	variable_ = var;
}

void Assignment::setValue(bool val)
{
	value_ = val;
}
