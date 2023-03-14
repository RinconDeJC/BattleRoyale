#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H
#include "Command.h"
class HelpCommand : public Command
{
public:
	HelpCommand();
	~HelpCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Virtual Override
	void run(bool &exit);
};
#endif

