#include "Command.h"


Command::Command(std::string name, char sc, std::string help) :
	_name(name),
	_short_code(sc),
	_help(help)
{
	_controller = Controller::GetInstance();
}


Command::~Command()
{
}

void Command::parseOptions(std::stringstream& ss)
{
	char test;
	ss >> test;
	if (!ss.fail()) {
		throw std::domain_error("Este comando no requiere argumentos");
	}
}

std::string Command::help()
{
	return _help;
}
