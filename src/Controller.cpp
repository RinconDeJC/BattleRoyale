#include "Controller.h"
#include "CommandGenerator.h"

//#define DEBUG

std::string Controller::_SAVE_SUFFIX = "_save";

Controller::Controller(Game game, Display display, JsonOutput json, std::string const& path) :
	_game(game),
	_display(display),
	_json_output(json),
	_path(path)
{
}


Controller::~Controller()
{
}


Controller* Controller::_instance = nullptr;

/**
 * Static methods should be defined outside the class.
 */
Controller* Controller::GetInstance(Game const& game, Display const& display, JsonOutput const& json, std::string const& path)
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (_instance == nullptr) {
		_instance = new Controller(game, display, json, path);
	}
	return _instance;
}

Controller* Controller::GetInstance()
{
	return _instance;
}

void Controller::newToJSON(std::string fileNamePrefix)
{
	// As this is to be used in a really specific way, we don't need to use
	// the command pattern the same way as in batchMode.


	bool aux = false;

	//First execute one command to open the game and save the starting list to json
	Command* command = new NewToJSONCommand(fileNamePrefix);
	command->run(aux);

	delete command;

	// Then execute a Save Command with same name
	command = new SaveCommand(fileNamePrefix);
	command->run(aux);

	delete command;
}

void Controller::oneTickToJSON(std::string fileNamePrefix)
{
	bool aux = false;

	// First load the game
	Command* command = new LoadFromSaveCommand(fileNamePrefix);
	command->run(aux);

	delete command;

	// Then execute one turn and save it to JSON
	command = new TurnToJSONCommand();
	command->run(aux);

	delete command;

	// Last thing is saving the game
	command = new SaveCommand(fileNamePrefix);
	command->run(aux);

	delete command;
}

void Controller::runBatchMode()
{
	Command* command;
	std::string line;
	bool exit = false;
#ifdef DEBUG

#endif

	while (!exit) {
		std::cout << "Command > ";
		getline(std::cin, line);
		try {
			command = CommandGenerator::parseCommand(line);
			if (command != nullptr) {
				command->run(exit);
				delete command;
			}
			else {
				_display.showError(line + " no es un comando valido");
			}
		}
		catch (std::exception &e) {
			_display.showError(e.what());
		}
	}
#ifdef DEBUG
	//Pause for end
	std::cin.get();
#endif
}

Game& Controller::game()
{
	return _game;
}

Display& Controller::display()
{
	return _display;
}

JsonOutput& Controller::JSONOutput()
{
	return _json_output;
}

std::string Controller::path()
{
	return _path;
}
