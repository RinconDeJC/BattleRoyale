#ifndef COMMAND_H
#define COMMAND_H

#include "Controller.h"
#include <string>
#include <sstream>

class Command
{
protected:
	std::string _name;
	std::string _help;
	char _short_code;
	Controller* _controller;

public:
	Command(std::string name, char sc, std::string help);
	~Command();

	virtual Command* parse(std::stringstream& ss) = 0;

	void parseOptions(std::stringstream& ss);

	std::string help();

	virtual void run(bool &exit) = 0;
};
#endif

