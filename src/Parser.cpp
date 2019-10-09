// Parser.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Parser.h"

#define SPACE ' '

using namespace std;

Parser::Parser()
{
}

CNF Parser::parse(string filename)
{
	ifstream myfile (filename.c_str());
	vector<vector<int> > dimacs ;
	int numOfVariables = 0;
	int numOfClauses = 0;
	
	string line;
	if (myfile.is_open())	{
		while ( getline(myfile, line))
		{
			if ( line.empty() )
			{	
				continue;
			}
			else if( line[0] == 'c')
			{
				continue;
			}
			if ( line[0] == 'c')
			{
				continue;
			}
			else if ( line[0] == '\n')
			{	
				continue;
			}
			else if ( line[0] == 'p')
			{
				stringstream ss(line);
				string item;
				getline(ss, item, SPACE);
				getline(ss, item, SPACE);
				getline(ss, item, SPACE);
				numOfVariables = atoi(item.c_str());
				getline(ss, item, SPACE);
				numOfClauses = atoi(item.c_str());
			}
			else
			{
				vector<int> clause;
				stringstream ss(line);
				string literal;
				while(getline(ss, literal, SPACE))
				{
					if( atoi(literal.c_str()) != 0) 
					{
						clause.push_back(atoi(literal.c_str()));
					}
				}
				dimacs.push_back(clause);
			}
		}

		myfile.close();
	}
	
	return CNF( numOfVariables, numOfClauses, dimacs );
}
