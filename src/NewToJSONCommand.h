#ifndef NEW_TO_JSON_COMMAND_H
#define NEW_TO_JSON_COMMAND_H
#include "Command.h"
class NewToJSONCommand :
	public Command
{
private:
	std::string _fileName;

public:
	NewToJSONCommand(std::string _saveFile= "default_save");
	~NewToJSONCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Override
	void parseOptions(std::stringstream& ss);

	///Virtual OVerride
	void run(bool& exit);
};

#endif

