// ImplicationGraph.h

#ifndef ImplicationGraph_H
#define ImplicationGraph_H

#include "Node.h"
#include "Edge.h"
#include <vector>
#include <deque>
#include <unordered_map>

class ImplicationGraph
{
	std::unordered_map<int, Node> nodelist_;
	int maxSize_;
	
	
public:
	ImplicationGraph();
	ImplicationGraph(int maxSize);
	~ImplicationGraph();
	void addNode(
		bool isDecisionNode,
		int decisionLevel, 
		int variable,
		bool value,
		std::vector<int> nodeIDs,
		Clause clause
	);
	int backtract(int decisionLevel);
	bool findNode(int nodeID, Node &node);
	std::deque<Node> findUIP(Node conflictNode);
	std::string toString();
	
};	

#endif
