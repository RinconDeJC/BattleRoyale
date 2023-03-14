#ifndef TURN_TO_JSON_COMMAND_H
#define TURN_TO_JSON_COMMAND_H
#include "Command.h"
class TurnToJSONCommand :
	public Command
{

public:
	TurnToJSONCommand();
	~TurnToJSONCommand();

	///Virtual Override
	Command* parse(std::stringstream& ss);

	///Virtual OVerride
	void run(bool& exit);
};

#endif