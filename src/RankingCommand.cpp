#include "RankingCommand.h"


RankingCommand::RankingCommand() :
	Command("ranking", 'r', "[N] ranking/r .Muestra la clasificacion")
{
}

RankingCommand::~RankingCommand()
{
}

Command * RankingCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new RankingCommand();
	}
	return nullptr;
}

void RankingCommand::run(bool &exit)
{
	_controller->display().showRanking(_controller->game().clasification());
}
