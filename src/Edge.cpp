#include "Edge.h"
#include <sstream>
#include <iostream>

using namespace std;

Edge::Edge(Clause c, int from, int to)
{
	clause_ = c;
	from_ = from;
	to_ = to;
}


Clause Edge::getClause()
{
	return clause_;
}

int Edge::getFromNode()
{
	return from_;
}

int Edge::getToNode()
{
	return to_;
}

string Edge::toString()
{
	ostringstream os;
	os << from_ << "->" << to_ << " | ";
	os << clause_.toString(); 
	string s = os.str();
	return s; 
}
