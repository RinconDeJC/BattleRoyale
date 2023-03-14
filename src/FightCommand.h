#ifndef FIGHT_COMMAND_H
#define FIGHT_COMMAND_H
#include "Command.h"
class FightCommand : public Command
{
private:
	int _ticks;
public:
	FightCommand(int ticks = 1);
	~FightCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Override
	void parseOptions(std::stringstream& ss);

	///Virtual Override
	void run(bool &exit);
};
#endif
