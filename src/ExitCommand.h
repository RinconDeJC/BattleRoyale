#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H
#include "Command.h"
class ExitCommand : public Command
{
public:
	ExitCommand();
	~ExitCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Virtual Override
	void run(bool &exit);
};
#endif

