#ifndef SAVE_COMMAND_H
#define SAVE_COMMAND
#include "Command.h"
class SaveCommand : public Command
{
private:
	std::string _fileName;

public:
	SaveCommand(std::string fileName = "default_save");
	~SaveCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Override
	void parseOptions(std::stringstream& ss);

	///Virtual OVerride
	void run(bool &exit);
};
#endif
