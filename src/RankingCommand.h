#ifndef RANKING_COMMAND_H
#define RANKING_COMMAND_H
#include "Command.h"
class RankingCommand : public Command
{
public:
	RankingCommand();
	~RankingCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Virtual Override
	void run(bool &exit);
};
#endif
