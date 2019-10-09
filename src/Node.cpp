
#include "Node.h"
#include <sstream>
#include <iostream>

using namespace std;

Node::Node()
{

}

Node::Node(
	bool isDecisionNode, 
	int decisionLevel, 
	int variable,
	bool value,
	vector<Edge> edges
)
{
	isDecisionNode_ = isDecisionNode;
	decisionLevel_ = decisionLevel;
	variable_ = variable;
	value_ = value;
	edges_ = edges;
}

int Node::getDecisionLevel()
{
	return decisionLevel_;
}

bool Node::getValue()
{
	return value_;
}

int Node::getVariable()
{
	return variable_;
}

bool Node::isDecisionNode()
{
	return isDecisionNode_;
}

std::vector<Edge>& Node::getEdges()
{
	return edges_;
} 

string Node::toString()
{
	ostringstream os;
	os << variable_ << " = ";
	os << value_ << " @ ";
	os << decisionLevel_ << endl;
	/*
	for( int i = 0; i < edges_.size(); i++)
	{
		os << edges_[i].toString() << endl;
	}
	*/
	string s = os.str();
	return s;
}


