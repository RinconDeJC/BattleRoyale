#ifndef LOAD_FROM_NEW_COMMAND_H
#define LOAD_FROM_NEW_COMMAND
#include "Command.h"
class LoadFromNewCommand : public Command
{
private:
	std::string _fileName;

public:
	LoadFromNewCommand(std::string fileName = "default_load");
	~LoadFromNewCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Override
	void parseOptions(std::stringstream& ss);

	///Virtual OVerride
	void run(bool &exit);
};
#endif
