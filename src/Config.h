// Config.h

#ifndef Config_H
#define Config_H

#include <string>

class Config
{
	int timeLimit_;
	bool verbose_;

public:
	Config();
	Config(int timeLimit, bool verbose);
	int timeLimit();
	bool verbose();
	void reset();
	std::string toString();

};


#endif
