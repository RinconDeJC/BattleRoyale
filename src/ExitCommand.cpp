#include "ExitCommand.h"

ExitCommand::ExitCommand() :
	Command("exit", 'e', "[N] exit/e .Sale del juego")
{
}

ExitCommand::~ExitCommand()
{
}

Command * ExitCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new ExitCommand();
	}
	return nullptr;
}

void ExitCommand::run(bool &exit)
{
	_controller->display().byeBye();
	exit = true;
}
