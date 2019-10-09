#include "ImplicationGraph.h"

#include <sstream>
#include <iostream>

using namespace std;

ImplicationGraph::ImplicationGraph()
{
	maxSize_ = 0;
}

ImplicationGraph::ImplicationGraph(int maxSize)
{
	maxSize_ = maxSize;
}

ImplicationGraph::~ImplicationGraph()
{

}


void ImplicationGraph::addNode(
	bool isDecisionNode,
	int decisionLevel,
	int variable,
	bool value,
	vector<int> nodeIDs,
	Clause clause
)
{
	vector<Edge> edges;
	if(!isDecisionNode)
	{
		for( int i = 0; i < nodeIDs.size(); i++)
		{
			Edge e = Edge(clause, nodeIDs[i], variable);
			edges.push_back(e);
		} 
	}
	Node node = Node(
		isDecisionNode,
		decisionLevel,
		variable,
		value,
		edges
	);
	nodelist_.insert({variable, node});
	//cout << "Adding New Node :" << variable << endl;
	//cout << node.toString() << endl;
}

int ImplicationGraph::backtract(int decisionLevel)
{
	int decisionVariable = -1;
	vector<int> toErase;
	for( auto it = nodelist_.begin(); it != nodelist_.end(); ++it)
	{
		Node node = it->second;
		if( node.getDecisionLevel() >= decisionLevel )
		{
			if( (node.getDecisionLevel() == decisionLevel) && node.isDecisionNode() )
			{
				if( decisionVariable != -1)
				{
					cout << "ERROR Setting Decision Variable Multiple Time in IGraph Backtract" << endl;
				}
				decisionVariable = node.getVariable();
			}
			toErase.push_back(it->first);
		}
	}
	for( int i = 0; i < toErase.size(); i++)
	{
		nodelist_.erase(toErase[i]);
	}
	return decisionVariable;

}

bool ImplicationGraph::findNode(int nodeID, Node &node)
{
	unordered_map<int, Node>::const_iterator got = nodelist_.find(nodeID);
	if( got == nodelist_.end() )
	{
		return false;
	}
	else
	{
		node = got->second;
		return true;
	}
}


deque<Node> ImplicationGraph::findUIP(Node conflictNode)
{
	int highestLevelCount = 0;
	int highestLevel = conflictNode.getDecisionLevel();
	bool visited[maxSize_+1];
	for( int i = 0; i < maxSize_+1; i++ )
	{
		visited[i] = false;	
	}
	
	deque<Node> solution;
	deque<Node> qN;
	visited[conflictNode.getVariable()] = true;
	qN.push_back(conflictNode);
	highestLevelCount++;
	do{
		Node currentNode = qN.front();
		qN.pop_front();
		//visited[currentNode.getVariable()] = true;
		if( currentNode.getDecisionLevel() != highestLevel )
		{
			solution.push_back(currentNode);
			continue;
		}
		if( currentNode.isDecisionNode() )
		{
			solution.push_back(currentNode);
			continue;
		}
		highestLevelCount--;
		vector<Edge> edges = currentNode.getEdges();
		for( int i = 0; i < edges.size(); i++)
		{
			unordered_map<int, Node>::const_iterator it = nodelist_.find(edges[i].getFromNode());
			Node node = it -> second;
			if( !visited[node.getVariable()])
			{
				if( node.getDecisionLevel() == highestLevel )
				{
					highestLevelCount++;
				}
				qN.push_back(node);
				visited[node.getVariable()] = true;
			}
		}
	} while( highestLevelCount > 1);
	
	for( int i = 0; i < qN.size(); i++)
	{
		solution.push_back(qN[i]);
	}
	
	return solution;
}


string ImplicationGraph::toString()
{
	ostringstream os;
	for( auto it = nodelist_.begin(); it != nodelist_.end(); ++it)
	{
		os << it->second.toString();	
	}
	string s = os.str();
	return s;
}
