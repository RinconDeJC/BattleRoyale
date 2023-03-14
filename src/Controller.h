#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <fstream>

#include "Game.h"
#include "Display.h"
#include "JsonOutput.h"

// This class follows the Singleton pattern, whose C++ implementation is from:
// https://refactoring.guru/design-patterns/singleton/cpp/example#example-0
// on its naive version, i.e. not thread-safe

class Controller
{
protected:
	Game _game;
	Display _display;
	JsonOutput _json_output;
    std::string _path;

    static Controller* _instance;

	Controller(Game game, Display display, JsonOutput json, std::string const& path);
	~Controller();
public:
    static std::string _SAVE_SUFFIX;
    /// NOT THREAD SAFE


    // Singletons should not be cloneable.
     
    Controller(Controller& other) = delete;
    
    // Singletons should not be assignable.
    
    void operator=(const Controller&) = delete;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static Controller* GetInstance(Game const& game, Display const& display, JsonOutput const& json, std::string const& path);
    
    //This static method won't create an instance if it is nullptr, just return the one that there is at the time
    static Controller* GetInstance();


	void newToJSON(std::string fileNamePrefix);
	void oneTickToJSON(std::string fileNamePrefix);
	void runBatchMode();

	Game& game();
	Display& display();
	JsonOutput& JSONOutput();
    std::string path();
};

#endif

