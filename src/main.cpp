//#define DEBUG

#include <iostream>
#include <ctime>
#include <locale.h>
#include <iomanip>

#include "InputParser.h"
// Controller.h already includes Display.h, JsonOutput.h and Game.h
#include "Controller.h"
#define AT_LINUX

using namespace std;

int main(int argc, char** argv)
{
// DISCLAIMER:
// The code you are about to witness is pure garbage, proceed at your own risk
#ifdef DEBUG
	cout << "DEBUGGING\n\n";
#endif
	setlocale(LC_CTYPE, "Spanish");
	if (argc < 2) {
		//Explain how the porogram should be called
		const int _MARGIN = 30;
		cerr << "Usage: " << argv[0] << " NAME" << '\n';
		cerr << "Commands:\n";
		cerr << '\n';
		cerr << "Options:\n";
		cerr << setw(_MARGIN) << left << "  --mode <m>" << "mode can be <bacth> for bacthMode, <json> for a single turn to save in json\n";
		cerr << setw(_MARGIN) << left << " " << "which requires --save-file option, or <new> which requires --save-file option\n";
		cerr << setw(_MARGIN) << left << "  --save-file <f>" << "specifies the name of the save file, without the extension\n";
		cerr << setw(_MARGIN) << left << "  --path <p>" << "specifies the name of thepath to the filder where results are saved. By defualt it is the same folder\n";
		return 1;
	}
	//Parse arguments
	InputParser input(argc, argv);
	if (!input.cmdOptionExists("--mode")) {
		std::cerr << "--mode <m> option missing\n";
		return 2;
	}

	std::string mode = input.getCmdOption("--mode");
	std::string saveFile;
	if (mode == "new" || mode == "json") {
		if (!input.cmdOptionExists("--save-file")) {
			std::cerr << "--save-file <f> option missing\n";
			return 2;
		}
		else {
			saveFile = input.getCmdOption("--save-file");
			if (saveFile == "")
				saveFile = "default";
		}
	}
	std::string path = input.getCmdOption("--path");
	#ifdef AT_LINUX
	if (path != "" && path.at(path.length() - 1) != '/') {
		path = path + '/';
	}
	#else
	if (path != "" && path.at(path.length() - 1) != '\\') {
		path = path + '\\';
	}
	#endif
	// now that we have tested almost everything about commands we can start the game
	srand(time(NULL));
	Game game;
	Display display;
	JsonOutput json(saveFile, path);
	Controller* controller = Controller::GetInstance(game, display, json, path);
	if (mode == "batch") {
		controller->runBatchMode();
	}
	else if (mode == "new") {
		controller->newToJSON(saveFile);
	}
	else if (mode == "json") {
		controller->oneTickToJSON(saveFile);
	}
	else {
		// Last error
		cerr << "--mode " << mode << " is not a valid mode option\n";
		return 2;
	}
	
	return 0;
}