// Parser.h
#ifndef Parser_H
#define Parser_H

#include "CNF.h"
#include <string>
#include <vector>

class Parser{

	
public:
	Parser();
	CNF parse(std::string filename);
};

#endif
