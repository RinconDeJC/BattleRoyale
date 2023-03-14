#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H
//#define DEBUG
#define PREVENTION

///Dependencies
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

///The class includes
#include "Person.h"
#include "Event.h"
#include "TeamHolder.h"

/**
 *	PlayersList is the implementation of the logical componentes of the game.
 *	
 *	The class contains the following atributes
 *	
 *	_alive:			a vector of the Person alive in the game (sorted alphabetically)
 *	_eliminated:	a vector of the Person eliminated in the game (sorted by elimination order)
 *	_n_alive:		number of Person alive
 *	_n_eliminated:	number of Perosn eliminated
 *	_n_vulnearble:	number of Person that can be infected
 *	_n_infected:	number of Person that are infected
 *	_n_immune:		number of Person that have been vaccinated
 *	_n_docotrs:		number of DCOTOR alive
 *	_vaccine:		marcs whether a vaccine is available or not
 *	_events:		contains the queue of events (usually happends in one or several simulations)
 *
 */
class PlayersList {
protected:
	
	std::vector<Person> _alive;
	int _n_alive;
	std::vector<Person> _eliminated;
	int _n_eliminated;

	TeamHolder _teams;

	int _n_vulnerable;
	int _n_infected;
	int _n_immune;

	int _n_doctors;
	bool _vaccine;

	std::queue<Event> events;

	friend class Event;

public:
	/**
	 *	Default contructor and destructor
	 *
	 */
	PlayersList();
	~PlayersList();

	/**
	 *	Overload of = operator
	 *	
	 *	Unfinished, DO NOT USE, undefined behaviour
	 *
	 *	@exceptsafe no-throw
	 */
	PlayersList & operator=(PlayersList & other);


	/**
	 *	Reset the list
	 *
	 *	@exceptsafe no-throw
	 */
	void reset();

	/**
	 *	Reset the queue of events
	 *
	 *	@exceptsafe no-throw
	 */
	void resetEvents();

	/**
	 *	Returns the queue of events
	 *
	 *	@return the queue of events as a contant queue
	 *
	 *	@exceptsafe no-throw
	 */
	const std::queue<Event> turnEvents() const;

	/**
	 *	Returns the Person::Score of every Person alive
	 *
	 *	@return a vector with every Person::Score of the Person alive
	 *
	 *	@exceptsafe no-throw
	 */
	const std::vector<Person::Score> aliveScore() const;

	/**
	 *	Returns the Person::Score of every Person eliminated
	 *
	 *	@return a vector with every Person::Score of the Person eliminated
	 *
	 *	@exceptsafe no-throw
	 */
	const std::vector<Person::Score> eliminatedScore() const;

	int remaining() const;

	bool loadNew(std::istream & _in);

	void loadSave(std::istream & _in);

	bool finished() const;

	Person::Score winner() const;

	void simulate(int _time);

	void curePlayers(int _time);

	void checkInfections(int _time);

	void vaccinatePlayers(int _time);

	void findVaccine(int _time);

	std::vector<Person>::iterator eliminatePlayer(Person const& p);

	void serialize(std::ostream & output);

	// Pairs are <Profession,vector<name,team>>
	std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> profession();

	const std::unordered_map<std::string, std::vector<Person>>& team_list() const;

#ifdef DEBUG
	void writeAlive();

	void writeEliminated();
#endif

protected:

	std::vector<Person>::iterator eliminatePlayer(std::vector<Person>::iterator & it);

	void addPlayer(Person const& p);

	//After the 2 people who are to fight have been decided, a duel is carried
	//If the return value is true the duel has been fullfilled and one player is eliminated.
	//If the return value is false the duel has not taken place.
	bool duel(Person & p1, Person & p2, int time);

};

#endif
