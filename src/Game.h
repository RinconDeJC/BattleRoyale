#ifndef GAME_H
#define GAME_H
//#define DEBUG

#include "PlayersList.h"
#include <fstream>

class Game final {

//Game Constants
public:
	static const int INITIAL_INFECTED = 10;
	
	//Rules
	static const int ONLY_DUELS = 3;

private:
	int _time;
	PlayersList _players;
	std::string _game_name;	

public:
	Game();
	~Game();

	std::queue<Event> loadNew(std::istream & _in);

	std::queue<Event> loadSave(std::istream & in);

	std::queue<Event> run(int _ticks = 1);

	bool finished() const;

	Event winner() const;

	int remaining() const;

	std::pair<std::vector<Person::Score>, std::vector<Person::Score>> clasification() const;

	// Pairs are <Profession,vector<name,team>>
	std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> profession();

	const std::unordered_map<std::string, std::vector<Person>>& team_list() const;

	void serialize(std::ostream & output);

	std::string gameName();

	void setName(std::string name);

};
#endif

