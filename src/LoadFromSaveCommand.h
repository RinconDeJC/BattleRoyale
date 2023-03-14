#ifndef LOAD_FROM_SAVE_COMMAND_H
#define LOAD_FROM_SAVE_COMMAND
#include "Command.h"
class LoadFromSaveCommand : public Command
{
private:
	std::string _fileName;

public:
	LoadFromSaveCommand(std::string fileName = "deafault_load");
	~LoadFromSaveCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Override
	void parseOptions(std::stringstream& ss);

	///Virtual OVerride
	void run(bool &exit);
};
#endif
