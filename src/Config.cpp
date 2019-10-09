// Config.cpp

#include "Config.h"
#include <limits>
#include <sstream>
#include <iostream>

using namespace std;

Config::Config()
{
	reset();
}

Config::Config(int timeLimit, bool verbose)
{
	if( timeLimit > 0)
	{
		timeLimit_ = timeLimit;
	}
	else
	{
		timeLimit_ = std::numeric_limits<int>::max();
	}
	verbose_ = verbose;
}

int Config::timeLimit()
{
	return timeLimit_;
}

bool Config::verbose()
{
	return verbose_;
}

void Config::reset()
{
	timeLimit_ = std::numeric_limits<int>::max();
	verbose_ = false;
}

string Config::toString()
{
	ostringstream os;
	os << "Time Limit: " << timeLimit_ << " (seconds)" << endl;
	os << "Verbose: " << verbose_ << endl;
	return os.str();
}
