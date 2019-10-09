// Edge.h
#ifndef Edge_H
#define Edge_H

#include <vector>
#include <string>
#include "Clause.h"

class Edge
{
	Clause clause_;
	int from_, to_;

public:
	Edge(Clause c, int from, int to);
	Clause getClause();
	int getFromNode();
	int getToNode();
	std::string toString();
};


#endif
