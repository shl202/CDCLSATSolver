// Node.h
#ifndef Node_H
#define Node_H

#include <vector>
#include <string>
#include "Edge.h"


class Node
{
	bool isDecisionNode_;
	int variable_;
	bool value_;
	int decisionLevel_;
	std::vector<Edge> edges_;

public:
	Node();
	Node(
		bool isDecisionNode,
		int decisionLevel,
		int variable,
		bool value,
		std::vector<Edge> edges
	);
	//Assignment  getAssignment();
	int getDecisionLevel();
	bool getValue();
	int getVariable();
	bool isDecisionNode();
	std::vector<Edge>& getEdges();
	std::string toString();
};


#endif
