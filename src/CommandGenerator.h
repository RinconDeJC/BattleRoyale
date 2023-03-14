#ifndef COMMAND_GENERATOR_H
#define COMMNAD_GENERATOR_H

#include <string>
#include <sstream>

#include "Command.h"
#include "FightCommand.h"
#include "HelpCommand.h"
#include "RankingCommand.h"
#include "ExitCommand.h"
#include "LoadFromNewCommand.h"
#include "LoadFromSaveCommand.h"
#include "SaveCommand.h"
#include "NewToJSONCommand.h"
#include "TurnToJSONCommand.h"

class CommandGenerator
{
private:
	const static int _COMMAND_NUMBER = 9;
	static Command *_command_list[_COMMAND_NUMBER];
public:
	CommandGenerator();
	~CommandGenerator();
	static Command* parseCommand(std::string& line);

	static std::vector<std::string> getHelp();
};

#endif