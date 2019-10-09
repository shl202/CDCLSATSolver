#include <iostream>
#include <vector>
#include "CNF.h"
#include "RandomSolver.h"
#include "DPLLSolver.h"
#include "CDCLSolver.h"
#include "Parser.h"


using namespace std;

int main(int argc, char* argv[])
{
	
	int timeLimit = -1;
	bool verbose = false;
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] 
			 << " ./Path/File.txt " 
			 << "[--time i] " 
			 << "[--verbose]" << endl;
		return 1;
	}
	
	// TODO check if file exist 
	string filename = argv[1];
	for( int i = 2; i < argc; i++)
	{
		string argvi(argv[i]);
		if ( argvi  == "--time" )
		{
			string argvj(argv[i+1]);
			timeLimit = stoi(argvj);  
			i++;
		}
		else if ( argvi == "--verbose" )
		{
			verbose = true;
		}
		else
		{
			cerr << "Usage: " << argv[0] 
				<< " ./Path/File.txt " 
				<< "[--time i] " 
				<< "[--verbose]" << endl;
			return 1;
		}
	}

	Config config(timeLimit, verbose);
	cout << config.toString() << endl;

	Parser parser;
	CNF cnf = parser.parse(filename);
	//cout << cnf.toString() << endl;


	/*
	RandomSolver rs = RandomSolver();
	string output = rs.solve(cnf);
	cout << output << endl;
	cout << "Number of Assignments Attempted: " << rs.getNumAttempts() << endl;
	cout << "Number of Unique Assignments Attempted: " << rs.getUniqueNumAttempts() << endl;
	*/


	/*
	DPLLSolver ds = DPLLSolver();
	string output = ds.solve(cnf);
	cout << output << endl;
	*/


	CDCLSolver cs = CDCLSolver();
	string output = cs.solve(cnf, config);
	cout << output << endl;
	
	return 0;
}
