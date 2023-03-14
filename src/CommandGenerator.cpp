#include "CommandGenerator.h"

Command* CommandGenerator::_command_list[] = {
	   new FightCommand(),
	   new HelpCommand(),
	   new RankingCommand(),
	   new ExitCommand(),
	   new SaveCommand(),
	   new LoadFromSaveCommand(),
	   new LoadFromNewCommand(),
	   new NewToJSONCommand(),
	   new TurnToJSONCommand()
};

CommandGenerator::CommandGenerator()
{
}


CommandGenerator::~CommandGenerator()
{
}

Command * CommandGenerator::parseCommand(std::string& line)
{
	int i = 0;
	Command* command = nullptr;
	std::stringstream ss(line);
	while(i < CommandGenerator::_COMMAND_NUMBER
		&&
		(command = CommandGenerator::_command_list[i]->parse(ss)) == nullptr)
	{
		ss = std::stringstream(line);
		++i;
	}
	return command;
}

std::vector<std::string> CommandGenerator::getHelp()
{
	std::vector<std::string> help;
	for (int i = 0; i < CommandGenerator::_COMMAND_NUMBER; ++i) {
		help.push_back(CommandGenerator::_command_list[i]->help());
	}
	return help;
}
