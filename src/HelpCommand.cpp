#include "HelpCommand.h"
#include "CommandGenerator.h"

HelpCommand::HelpCommand() :
	Command("help", 'h', "[N] help/h .Muestra este mensaje")
{
}

HelpCommand::~HelpCommand()
{
}

Command * HelpCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new HelpCommand();
	}
	return nullptr;
}

void HelpCommand::run(bool &exit)
{
	_controller->display().showHelp(CommandGenerator::getHelp());
}
